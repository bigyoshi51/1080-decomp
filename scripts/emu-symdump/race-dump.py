#!/usr/bin/env python3
"""Drive 1080 into a RACE with the scripted INPUT plugin so GAMEPLAY USOs
(timproc/h2hproc/mgrproc) load, snapshotting RDRAM periodically for the USO-reloc
symbol dump. Unlike uso-emu-dump.py (stops on the first signature), this runs
through the menus and keeps the LATEST RDRAM snapshot in --out, since we don't
know in advance which frame the target proc loads.

Needs: real video-rice (GFX) + rsp-hle (RSP) under a virtual display, the
scripted-INPUT.so plugin (build: see scripted-input.c), and dummy-AUDIO.so.

  tools/mupen64plus/xvfb-extract/usr/bin/Xvfb :99 -screen 0 640x480x24 &
  LD_LIBRARY_PATH=<bundle> DISPLAY=:99 python3 race-dump.py --dur 400 --out /tmp/race_rdram.bin

Then probe the snapshot for the target proc's decompressed CODE block (>=64-byte
probe — see README "Verify residency") and dump via game-uso-reloc-diff.py (the
procs are compressed) or uso-correlate.py (uncompressed). Tune the scripted-input
phase env vars (SI_IDLE/SI_START/SI_MASH) if the mash doesn't reach a race.
"""
import argparse, ctypes as C, glob, os, threading, time, array

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--bundle', default=os.environ.get('LD_LIBRARY_PATH',''))
    ap.add_argument('--plugins', default='tools/dummyplugins')
    ap.add_argument('--rom', default='baserom.z64')
    ap.add_argument('--dur', type=float, default=400)
    ap.add_argument('--interval', type=float, default=20)
    ap.add_argument('--out', default='/tmp/race_rdram.bin')
    ap.add_argument('--target-asm', default=None, help='raw .s; stop+save the snapshot when this fn is resident')
    a=ap.parse_args()
    import re as _re,struct as _st
    tpat=None
    if a.target_asm:
        w=[]
        for l in open(a.target_asm):
            m=_re.search(r'/\* [0-9A-Fa-f]+ [0-9A-Fa-f]+ ([0-9A-Fa-f]{8}) \*/',l)
            if m: w.append(int(m.group(1),16))
        tpat=b''.join(_st.pack('>I',x) for x in w[:6])
    rom=open(a.rom,'rb').read()
    core=C.CDLL(glob.glob(a.bundle+'/libmupen64plus.so.2*')[0], mode=C.RTLD_GLOBAL)
    core.DebugMemGetPointer.restype=C.c_void_p
    DBG=C.CFUNCTYPE(None,C.c_void_p,C.c_int,C.c_char_p); dbg=DBG(lambda c,l,m:None)
    ST=C.CFUNCTYPE(None,C.c_void_p,C.c_int,C.c_int); st=ST(lambda x,y,z:None)
    assert core.CoreStartup(0x020001,b'/tmp/m64pcfg',a.bundle.encode(),None,dbg,None,st)==0
    sec=C.c_void_p(); core.ConfigOpenSection(b'Core',C.byref(sec)); iv=C.c_int(1)
    core.ConfigSetParameter(sec,b'R4300Emulator',1,C.byref(iv))
    buf=C.create_string_buffer(rom,len(rom)); assert core.CoreDoCommand(1,len(rom),buf)==0
    plist=[(a.bundle+'/mupen64plus-video-rice.so',2),(a.plugins+'/dummy-AUDIO.so',3),
           (a.plugins+'/scripted-INPUT.so',4),(a.bundle+'/mupen64plus-rsp-hle.so',1)]
    for fn,t in plist:
        h=C.CDLL(fn,mode=C.RTLD_GLOBAL)
        try: h.PluginStartup(core._handle,None,dbg)
        except AttributeError: pass
        assert core.CoreAttachPlugin(t,h._handle)==0, fn
    print('executing race run (scripted input)',flush=True)
    threading.Thread(target=lambda: core.CoreDoCommand(5,0,None),daemon=True).start()
    start=time.time()
    while time.time()-start<a.dur:
        time.sleep(a.interval)
        ptr=core.DebugMemGetPointer(1)
        if not ptr: continue
        raw=bytes((C.c_ubyte*0x800000).from_address(ptr))
        a2=array.array('I',raw); a2.byteswap(); be=a2.tobytes(); open(a.out,'wb').write(be)
        hit = (tpat is not None and be.find(tpat)>=0)
        print(f't+{int(time.time()-start)}s: snapshot -> {a.out}'+(' TARGET RESIDENT!' if hit else ''),flush=True)
        if hit:
            open(a.out+'.hit','wb').write(be); print('saved '+a.out+'.hit; stopping',flush=True); break
    core.CoreDoCommand(6,0,None); print('race run done',flush=True)

if __name__=='__main__':
    main()
