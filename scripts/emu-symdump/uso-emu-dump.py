#!/usr/bin/env python3
"""Boot the 1080 ROM headless in mupen64plus and dump RDRAM after a USO module
is loaded + relocated, so its resolved symbol table can be recovered.

WHY: the Kyoto-USO on-disk Sym name table can't be parsed statically (the loader
resolves names->values in-place at load; no separate parser exists in the kernel
cluster). So we run the real loader inside an emulator and read the result out of
RDRAM, then correlate (uso-correlate.py).

HOW it locates the module: USO .text/.rodata is relocated in place, but most words
are NOT relocated. We build a signature from a run of consecutive NON-reloc text
words straight from the ROM, then scan the byteswapped RDRAM dump for it. The
signature offset back-computes the loaded Text base.

CRITICAL GOTCHAS (each cost hours):
  * RDRAM byte-order: DebugMemGetPointer(M64P_DBG_PTR_RDRAM) returns memory
    byte-swapped per 32-bit word (host LE storage). Byteswap every 4 bytes to get
    big-endian N64 memory, else NOTHING matches. (array.array('I').byteswap())
  * Plugins must be attached AFTER M64CMD_ROM_OPEN, not before (else INVALID_STATE).
  * The core calls DoRspCycles unconditionally -> needs an RSP plugin or it
    null-derefs; rsp-hle segfaults via ctypes. Use the task-completing dummy-RSP.
  * Use the interpreter (R4300Emulator=1) so the debugger memory API is live.
  * No display needed: the dummy gfx/audio/input plugins are pure no-ops.

Setup (one-time): see README.md -- download a mupen64plus bundle, build the three
dummy plugins + dummy-RSP from dummy-plugin.c / dummy-rsp.c.

Usage:
  uso-emu-dump.py --bundle <dir> --rom baserom.z64 --module 0xD9FE28 \\
      --plugins <dir-with-dummy-*.so> --out /tmp/rdram.bin
"""
import argparse, ctypes as C, json, struct, sys, threading, time

def u32(d,o): return struct.unpack_from('>I',d,o)[0]

def walk_dir(d, mod):
    """Return {sectype: (data_off, size)} for the USO module at ROM offset `mod`."""
    SEC={0,1,2,3,4,5,6,7,8,9}
    if u32(d,mod)!=0x12345678: sys.exit(f'no USO magic at {mod:#x}')
    o=mod+0xC; secs={}
    for _ in range(64):
        typ,size=u32(d,o+4),u32(d,o+8)
        if typ in (10,11) or typ not in SEC: break
        secs.setdefault(typ,(o+12,size))
        o += 12 + (0 if typ==8 else ((size+3)&~3))
    return secs

def build_signature(d, secs, nwords=12):
    """A run of `nwords` consecutive NON-reloc Text words = a unique fingerprint.
    Text section data has a leading 0x20000001 marker word, so project offset 0 is
    at section-data + 4. Reloc offsets are project offsets."""
    tdat,tsz=secs[5]; trdat,trsz=secs[2]
    reloc=set()
    o=trdat
    while o+12<=trdat+trsz:
        reloc.add(u32(d,o+8)); o+=12
    base=tdat+4  # skip marker word
    poff=0x80    # start a bit in (past the first function prologue churn)
    while poff < tsz-4*nwords:
        if all((poff+4*k) not in reloc for k in range(nwords)):
            sig=d[base+poff:base+poff+4*nwords]
            return sig, poff
        poff+=4
    sys.exit('no non-reloc run found for signature')

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--bundle', required=True, help='mupen64plus bundle dir (has libmupen64plus.so.2*)')
    ap.add_argument('--rom', default='baserom.z64')
    ap.add_argument('--module', type=lambda x:int(x,0), required=True, help='ROM offset of USO module (magic 0x12345678)')
    ap.add_argument('--plugins', required=True, help='dir with dummy-GFX.so dummy-AUDIO.so dummy-INPUT.so dummy-RSP.so')
    ap.add_argument('--out', default='/tmp/rdram.bin')
    ap.add_argument('--found', default='/tmp/found.json')
    ap.add_argument('--deadline', type=int, default=200, help='max seconds to wait for the module to appear')
    ap.add_argument('--real-render', action='store_true', help='use real GFX(video-rice)+RSP(rsp-hle) so the game reaches gameplay (needs Xvfb+DISPLAY); for GAMEPLAY USOs (timproc/game_uso). Dummy default = boot USOs only.')
    a=ap.parse_args()

    rom=open(a.rom,'rb').read()
    secs=walk_dir(rom,a.module)
    sig,sig_poff=build_signature(rom,secs)
    print(f'signature: {len(sig)} bytes at project offset {sig_poff:#x}', flush=True)

    import glob, os
    corelib=glob.glob(os.path.join(a.bundle,'libmupen64plus.so.2*'))[0]
    core=C.CDLL(corelib, mode=C.RTLD_GLOBAL); core.DebugMemGetPointer.restype=C.c_void_p
    DBG=C.CFUNCTYPE(None, C.c_void_p, C.c_int, C.c_char_p); dbgcb=DBG(lambda c,l,m:None)
    STATE=C.CFUNCTYPE(None, C.c_void_p, C.c_int, C.c_int); statecb=STATE(lambda x,y,z:None)
    if core.CoreStartup(0x020001, b'/tmp/m64pcfg', a.bundle.encode(), None, dbgcb, None, statecb)!=0:
        sys.exit('CoreStartup failed')
    sec=C.c_void_p(); core.ConfigOpenSection(b'Core', C.byref(sec)); iv=C.c_int(1)  # 1=interpreter
    core.ConfigSetParameter(sec, b'R4300Emulator', 1, C.byref(iv))
    buf=C.create_string_buffer(rom,len(rom))
    if core.CoreDoCommand(1,len(rom),buf)!=0: sys.exit('ROM_OPEN failed')   # M64CMD_ROM_OPEN
    # --real-render: use the bundle's real video-rice (GFX) + rsp-hle (RSP) so the
    # game advances PAST boot into the attract demo / menu and loads GAMEPLAY USOs
    # (timproc/game_uso/...). Needs a display (Xvfb :N + DISPLAY=:N) + software GL.
    # Boot-loaded USOs (bootup/game_libs) work with the dummy default.
    if a.real_render:
        plist=[(a.bundle+'/mupen64plus-video-rice.so',2),(os.path.join(a.plugins,'dummy-AUDIO.so'),3),
               (os.path.join(a.plugins,'dummy-INPUT.so'),4),(a.bundle+'/mupen64plus-rsp-hle.so',1)]
    else:
        plist=[(os.path.join(a.plugins,'dummy-GFX.so'),2),(os.path.join(a.plugins,'dummy-AUDIO.so'),3),
               (os.path.join(a.plugins,'dummy-INPUT.so'),4),(os.path.join(a.plugins,'dummy-RSP.so'),1)]
    for fn,t in plist:
        h=C.CDLL(fn, mode=C.RTLD_GLOBAL)
        # CRITICAL: the FRONTEND must call the plugin's PluginStartup (so the plugin
        # resolves the core's functions, incl. VidExt) BEFORE CoreAttachPlugin. The
        # dummy plugins have a no-op PluginStartup so the old code worked; REAL plugins
        # crash in InitiateGFX on a NULL VidExt ptr without it. (gdb-confirmed.)
        try: h.PluginStartup(core._handle, None, dbgcb)
        except AttributeError: pass
        if core.CoreAttachPlugin(t,h._handle)!=0: sys.exit(f'attach {os.path.basename(fn)} failed (after ROM_OPEN?)')
    print('plugins attached; executing', flush=True)
    threading.Thread(target=lambda: core.CoreDoCommand(5,0,None), daemon=True).start()  # M64CMD_EXECUTE

    start=time.time(); found=False
    while time.time()-start < a.deadline:
        time.sleep(3)
        ptr=core.DebugMemGetPointer(1)   # M64P_DBG_PTR_RDRAM
        if not ptr: continue
        raw=bytes((C.c_ubyte*0x800000).from_address(ptr))
        be=bytearray(raw); arr=memoryview(be).cast('I'); a2=__import__('array').array('I',arr); a2.byteswap()
        be=a2.tobytes()                   # big-endian N64 memory
        idx=be.find(sig)
        if idx>=0:
            tbase=idx-4-sig_poff          # phys base of Text section data (marker word @ tbase)
            open(a.out,'wb').write(be)
            json.dump({'textbase':tbase,'sig_idx':idx,'sig_poff':sig_poff}, open(a.found,'w'))
            print(f'FOUND: textbase phys {tbase:#x}; wrote {a.out} + {a.found}', flush=True)
            found=True; break
        print(f't+{int(time.time()-start)}s: not yet', flush=True)
    core.CoreDoCommand(6,0,None)          # M64CMD_STOP
    print('stopped; found=',found, flush=True)
    sys.exit(0 if found else 2)

if __name__=='__main__':
    main()
