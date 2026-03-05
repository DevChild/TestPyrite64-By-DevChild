#include "script/userScript.h"
#include "scene/sceneManager.h"

#include "globals.h"
#include "script/userScript.h"
#include "Basics/context.h"
#include "scene/sceneManager.h"
#include <scene/components/nodeGraph.h>

#include "../p64/sceneTable.h"

namespace
{
  constexpr int SCREEN_EDGE = 20.01f;
}

namespace P64::Script::C88BFB0A32963FDF
{
  P64_DATA(
    [[P64::Name("Image")]]
    AssetRef<sprite_t> img;

    rspq_block_t *dplImg;
  );


  void initDelete(Object& obj, Data *data, bool isDelete)
  {
    if(isDelete) {
      rspq_block_free(data->dplImg);
      return;
    }
    const auto &conf = SceneManager::getCurrent().getConf();
    int posX = conf.screenWidth/2-data->img.get()->width/2;
    int posY = conf.screenHeight/2 - data->img.get()->height/2 - 80;

    rspq_block_begin();
        // Inicia el modo de renderizado (RDPQ)
      rdpq_mode_begin();
          // Configura el mezclador para multiplicar colores (útil para efectos de transparencia)
        rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
          // Compara el canal alfa para decidir si dibujar el píxel (2 = solo píxeles con alfa > 0)
        rdpq_mode_alphacompare(2);
          // Usa el combinador de texturas (solo la textura)
        rdpq_mode_combiner(RDPQ_COMBINER_TEX);
      rdpq_mode_end();

        // Parámetros para dibujar el sprite (por defecto, sin escalado)
      rdpq_blitparms_t p{};
      //p.scale_y = p.scale_x = 0.75f;
        // Dibuja el sprite de la moneda en la posición indicada
      rdpq_sprite_blit(data->img.get(), posX, posY+10.0f, &p);

        // Cambia el mezclador a modo normal
      rdpq_mode_blender(0);
    data->dplImg = rspq_block_end();
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    auto pressed = joypad_get_buttons_pressed(JOYPAD_PORT_1);
    auto graphComp = obj.getComponent<Comp::NodeGraph>();
    if(graphComp->isRunning()) return;
    if(pressed.a) {
      graphComp->run();
    }
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    int baseX = SCREEN_EDGE;
    int baseY = SCREEN_EDGE;
    //Dibujar texto
    float posY = 20.0f; // conf.screenHeight - SCREEN_EDGE - 20.0f;
    rdpq_textparms_t TEXT_CENTER{
      .width = (int16_t)rdpq_get_attached()->width,
      .align = ALIGN_CENTER,
      .disable_aa_fix = true
    };

    DrawLayer::use2D();
    
    rspq_block_run(data->dplImg);
      rdpq_text_printf(&TEXT_CENTER, User::FONT_TEXT, 0, 220.0f,
        "Press A to Start");

    DrawLayer::useDefault();
  }

  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {
  }

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
  }
}
