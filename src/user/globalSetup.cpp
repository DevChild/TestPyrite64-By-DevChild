/*
Global setup que estare configurando mas tarde, por ahora solo es para inicializar el contexto global 
que se va a usar en varios scripts, como el de la camara de debug y el lookat, para compartir 
informacion entre ellos, como la posicion de la camara, el id del objeto controlado, etc.
*/
#include "script/globalScript.h"
#include "script/userScript.h"

#include <libdragon.h>
#include <vi/swapChain.h>

#include "globals.h"
#include "Basics/context.h"
#include "Basics/dialog.h"
#include "script/nodeGraph.h"


namespace P64::User
{
  constinit Context ctx{};
}


namespace P64::GlobalScript::C4F4D286D6CBAAAA
{
  void onGameInit()
  {
    User::ctx = {};
    User::ctx.controlledId = 1;

    NodeGraph::registerFunction("ShowMessage"_crc32, User::Dialog::showMessage);
  }

  void onScenePreLoad()
  {
    User::Dialog::init();
  }

  void onScenePostLoad()
  {
    
  }

  void onScenePostUnload()
  {
    User::Dialog::destroy();
  }

  void onSceneUpdate()
  {
    /*auto held = joypad_get_buttons_held(JOYPAD_PORT_1);
    for(uint32_t y = 0; y < ditherDim; ++y)
    {
      for(uint32_t x = 0; x < ditherDim; ++x)
      {
        uint32_t index = 0;
        for(uint32_t bit = 0; bit < 4; ++bit)
        {
          index |= ((x >> (3 - bit)) & 1) << (bit * 2 + 1);
          index |= ((y >> (3 - bit)) & 1) << (bit * 2 + 0);
        }
        uint16_t ditherVal = (ditherScale * index) / ditherScaleSteps;
        buffDither[y*ditherDim + x] = baseDepth - ditherVal;
      }
    }*/
    
    User::ctx.isCutscene = false;
    ++User::ctx.frame;

    if(User::Dialog::update())User::ctx.isCutscene = true;
  }

  void onScenePreDraw()
  {

  }

  void onScenePostDraw3D()
  {

  }



  void onSceneDraw2D()
  {
    //User::Marker::draw();
    User::Dialog::draw();
    // frame pacing debug
/*
    rdpq_sync_pipe();
    rdpq_set_mode_fill(col[colIdx]);
    rdpq_fill_rectangle(32, 32+(colIdx*4), 32+8, 32+8+(colIdx*4));
    colIdx = (colIdx + 1) % 3;
    */

  }
}