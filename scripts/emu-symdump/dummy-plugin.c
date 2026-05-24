/* No-op mupen64plus gfx/audio/input plugin for HEADLESS symbol-dump runs.
 *
 * The core calls into gfx/audio/input every frame; with no display we just need
 * stubs that succeed and do nothing (no GL, no SDL, no Xvfb required). One source
 * builds all three plugins via -DPLUGIN_TYPE / -DPLUGIN_API (see README.md):
 *   gfx  : -DPLUGIN_TYPE=2 -DPLUGIN_API=0x020200
 *   audio: -DPLUGIN_TYPE=3 -DPLUGIN_API=0x020000
 *   input: -DPLUGIN_TYPE=4 -DPLUGIN_API=0x020100
 * Needs the mupen64plus-core headers (m64p_types.h, m64p_plugin.h) on -I.
 */
#include <stdio.h>
#include "m64p_types.h"
#include "m64p_plugin.h"
#define EXPORT __attribute__((visibility("default")))
#define CALL
/* common */
EXPORT m64p_error CALL PluginStartup(m64p_dynlib_handle h, void *ctx, void (*dbg)(void*,int,const char*)){return M64ERR_SUCCESS;}
EXPORT m64p_error CALL PluginShutdown(void){return M64ERR_SUCCESS;}
EXPORT m64p_error CALL PluginGetVersion(m64p_plugin_type *type,int *ver,int *api,const char **name,int *caps){
  if(type)*type=PLUGIN_TYPE; if(ver)*ver=0x020600; if(api)*api=PLUGIN_API; if(name)*name="dummy"; if(caps)*caps=0;
  return M64ERR_SUCCESS;}
/* gfx */
EXPORT int CALL InitiateGFX(GFX_INFO g){return 1;}
EXPORT int CALL RomOpen(void){return 1;}
EXPORT void CALL RomClosed(void){}
EXPORT void CALL ChangeWindow(void){}
EXPORT void CALL MoveScreen(int x,int y){}
EXPORT void CALL ProcessDList(void){}
EXPORT void CALL ProcessRDPList(void){}
EXPORT void CALL ShowCFB(void){}
EXPORT void CALL UpdateScreen(void){}
EXPORT void CALL ViStatusChanged(void){}
EXPORT void CALL ViWidthChanged(void){}
EXPORT void CALL ReadScreen2(void*a,int*b,int*c,int d){}
EXPORT void CALL SetRenderingCallback(void(*cb)(int)){}
EXPORT void CALL FBRead(unsigned int a){}
EXPORT void CALL FBWrite(unsigned int a,unsigned int b){}
EXPORT void CALL FBGetFrameBufferInfo(void*p){}
EXPORT m64p_error CALL ResizeVideoOutput(int w,int h){return M64ERR_SUCCESS;}
EXPORT void CALL FullSync(void){}
/* audio */
EXPORT int CALL InitiateAudio(AUDIO_INFO a){return 1;}
EXPORT void CALL AiDacrateChanged(int t){}
EXPORT void CALL AiLenChanged(void){}
EXPORT void CALL ProcessAList(void){}
EXPORT void CALL SetSpeedFactor(int p){}
EXPORT void CALL VolumeUp(void){}
EXPORT void CALL VolumeDown(void){}
EXPORT int CALL VolumeGetLevel(void){return 0;}
EXPORT void CALL VolumeSetLevel(int l){}
EXPORT void CALL VolumeMute(void){}
EXPORT const char* CALL VolumeGetString(void){return "0%";}
/* input */
EXPORT void CALL InitiateControllers(CONTROL_INFO c){}
EXPORT void CALL GetKeys(int n,BUTTONS*k){if(k)k->Value=0;}
EXPORT void CALL ControllerCommand(int n,unsigned char*d){}
EXPORT void CALL ReadController(int n,unsigned char*d){}
EXPORT void CALL SDL_KeyDown(int m,int s){}
EXPORT void CALL SDL_KeyUp(int m,int s){}
EXPORT void CALL RenderCallback(void){}
EXPORT void CALL SetMicState(int s){}
