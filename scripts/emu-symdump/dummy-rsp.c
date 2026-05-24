/* Task-completing no-op RSP plugin for headless symbol-dump runs.
 *
 * The core calls DoRspCycles unconditionally each frame; with no RSP plugin it
 * null-derefs, and rsp-hle segfaults when attached via ctypes. This stub just
 * marks every submitted task done so the CPU keeps running (we never need real
 * graphics/audio ucode results -- we only want bootup.uso loaded into RDRAM).
 * Build: -DM64PLUGIN_RSP=1 (or include m64p_plugin.h which defines it).
 *   gcc -shared -fPIC -I<core/api> -o dummy-RSP.so dummy-rsp.c
 */
#include "m64p_types.h"
#include "m64p_plugin.h"
#define EXPORT __attribute__((visibility("default")))
#define CALL
static RSP_INFO g;
EXPORT m64p_error CALL PluginStartup(m64p_dynlib_handle h, void *ctx, void (*dbg)(void*,int,const char*)){return M64ERR_SUCCESS;}
EXPORT m64p_error CALL PluginShutdown(void){return M64ERR_SUCCESS;}
EXPORT m64p_error CALL PluginGetVersion(m64p_plugin_type *t,int *v,int *a,const char **n,int *c){
  if(t)*t=M64PLUGIN_RSP; if(v)*v=0x010000; if(a)*a=0x020000; if(n)*n="dummyrsp"; if(c)*c=0; return M64ERR_SUCCESS;}
EXPORT void CALL InitiateRSP(RSP_INFO ri, unsigned int *cc){ g=ri; }
EXPORT unsigned int CALL DoRspCycles(unsigned int cycles){
  if(g.SP_STATUS_REG) *g.SP_STATUS_REG |= 0x3;   /* HALT | BROKE -> task done */
  if(g.MI_INTR_REG)   *g.MI_INTR_REG   |= 0x1;   /* MI_INTR_SP */
  if(g.CheckInterrupts) g.CheckInterrupts();
  return cycles;
}
EXPORT int CALL RomOpen(void){return 1;}
EXPORT void CALL RomClosed(void){}
