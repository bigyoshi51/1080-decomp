/* Scripted INPUT plugin for mupen64plus — drives 1080's menus to start a race so
 * GAMEPLAY USOs (timproc/h2hproc/mgrproc) load, for the USO-reloc symbol dump.
 *
 * The dummy INPUT plugin (a) never marks a controller Present, so the game reads
 * no pad, and (b) GetKeys returns 0. This one marks controller 0 present and
 * returns a programmed button schedule (frame-counted): idle through boot/title,
 * pulse START to leave the title, then mash A to confirm through the mode / board
 * / character / course menus (defaults are pre-selected) into a race, then idle so
 * the race runs (START would pause it).
 *
 * Pulsing (press a few frames, release several) is required — a held button
 * registers as ONE press; menus need distinct presses.
 *
 * Tune the phase boundaries via env vars (frames, controller-0 GetKeys calls):
 *   SI_IDLE   (default 150)  idle until here
 *   SI_START  (default 320)  pulse START [SI_IDLE, SI_START)
 *   SI_MASH   (default 1600) pulse A     [SI_START, SI_MASH); idle after
 * Build: cc -shared -fPIC -DPLUGIN_TYPE=4 -DPLUGIN_API=0x020100 -I<api> -o scripted-INPUT.so scripted-input.c
 */
#include <stdlib.h>
#include "m64p_types.h"
#include "m64p_plugin.h"
#define EXPORT __attribute__((visibility("default")))
#define CALL

#define BTN_START 0x0010u
#define BTN_A     0x0080u
#define BTN_B     0x0040u   /* B_BUTTON = bit6 (back out of a menu) */
#define BTN_DDOWN 0x0004u   /* D_DPAD = bit2 */

static int g_frame = 0;
static int g_idle, g_start, g_down, g_mash, g_downs, g_explore;

static int envi(const char *k, int d){ const char *v=getenv(k); return v?atoi(v):d; }

EXPORT m64p_error CALL PluginStartup(m64p_dynlib_handle h, void *ctx, void (*dbg)(void*,int,const char*)){
  g_idle =envi("SI_IDLE",150); g_start=envi("SI_START",280);
  g_down =envi("SI_DOWN",360); g_mash =envi("SI_MASH",1600);
  g_downs=envi("SI_DOWNS",1);     /* # of DPAD-down presses to select a non-top menu item (Time Attack=1) */
  g_explore=envi("SI_EXPLORE",0); /* 1 = sight-free menu sweep (try each main-menu position in turn) */
  return M64ERR_SUCCESS;
}
EXPORT m64p_error CALL PluginShutdown(void){return M64ERR_SUCCESS;}
EXPORT m64p_error CALL PluginGetVersion(m64p_plugin_type *type,int *ver,int *api,const char **name,int *caps){
  if(type)*type=PLUGIN_TYPE; if(ver)*ver=0x020600; if(api)*api=PLUGIN_API;
  if(name)*name="scripted-input"; if(caps)*caps=0; return M64ERR_SUCCESS;}

EXPORT void CALL InitiateControllers(CONTROL_INFO c){
  if(c.Controls){ c.Controls[0].Present=1; c.Controls[0].Plugin=PLUGIN_NONE;
                  c.Controls[0].RawData=0; c.Controls[0].Type=CONT_TYPE_STANDARD;
    for(int i=1;i<4;i++) c.Controls[i].Present=0; }
}
EXPORT void CALL GetKeys(int n, BUTTONS *k){
  if(!k) return;
  k->Value=0;
  if(n!=0){ return; }
  int f=g_frame++;
  int pulse = ((f % 16) < 5);                      /* on 5 of every 16 frames */
  if(f<g_idle) return;                              /* idle through boot */
  if(f<g_start){ if(pulse) k->Value=BTN_START; return; }  /* title -> main menu */

  if(g_explore){
    /* Sight-free menu sweep: we can't see the screen (screenshots fail headless,
     * VI regs read 0), so cycle through main-menu positions. Each cycle: back out
     * to the main menu (B), move the cursor down `cyc` times, then mash A to enter
     * + confirm sub-screens. cyc increments each cycle, so successive cycles try
     * Match Race(0)/Time Attack(1)/Trick(2)/2P(3)/Training(4)/... The harness
     * snapshots every 20s + checks residency, catching whichever cycle loads the
     * target proc. CYCLE = the per-cycle frame budget. */
    int CYC=envi("SI_CYCLE",260);
    int g=f-g_start, cyc=g/CYC, ph=g%CYC;
    if(ph<48){ if(pulse) k->Value=BTN_B; }                 /* back out (~3 presses) */
    else if(ph<48+16*(cyc%6)){ if(pulse){ k->Value=BTN_DDOWN; k->Y_AXIS=-80; } } /* down cyc%6 times */
    else { if(pulse) k->Value=BTN_A; }                     /* enter + confirm */
    return;
  }
  /* fixed mode: SI_DOWNS downs then A-mash */
  if(f<g_down){ int idx=(f-g_start)/16; if(pulse && idx<g_downs){ k->Value=BTN_DDOWN; k->Y_AXIS=-80; } return; }
  if(f<g_mash){ if(pulse) k->Value=BTN_A; }
  /* else idle (0) */
}
EXPORT void CALL ControllerCommand(int n,unsigned char*d){}
EXPORT void CALL ReadController(int n,unsigned char*d){}
EXPORT void CALL SDL_KeyDown(int m,int s){}
EXPORT void CALL SDL_KeyUp(int m,int s){}
EXPORT void CALL RenderCallback(void){}
EXPORT void CALL SetMicState(int s){}
EXPORT int CALL RomOpen(void){return 1;}
EXPORT void CALL RomClosed(void){}
