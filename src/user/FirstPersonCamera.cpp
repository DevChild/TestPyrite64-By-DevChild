#include "script/userScript.h"
#include "scene/sceneManager.h"

#include "globals.h"
#include "script/userScript.h"
#include "Basics/context.h"
#include "scene/components/collBody.h"
#include "scene/components/collMesh.h"
#include "collision/attach.h"
#include "scene/sceneManager.h"

#include "../p64/assetTable.h"

namespace
{
  constexpr float MOVE_SPEED_SLOWDOWN = 0.8f; // Factor de desaceleración para el movimiento
  constexpr float MOVE_SPEED = 50.00f; // Velocidad base de movimiento
  constexpr float ROT_SPEED = 0.01f; // Velocidad base de rotación
}

namespace P64::Script::C8D4DA2E7A73BC53
{
  P64_DATA(

    float playerRotX;
    float playerRotY;
    fm_vec3_t playerPos;
    fm_vec3_t playerDir;

    fm_vec3_t camTarget;
    fm_vec3_t camPos;
    fm_vec3_t camDir;

    Coll::Attach meshAttach;
    uint8_t stepSFXCooldown;
  );


  void initDelete(Object& obj, Data *data, bool isDelete)
  {
    if(isDelete) {
      
      return;
    }
    User::ctx.controlledId = obj.id;

    data->playerRotX = obj.rot.x; // rotación horizontal inicial
    data->playerRotY = obj.rot.y; // rotación vertical inicial
  }

  void update(Object& obj, Data *data, float deltaTime)
  {

    auto coll = obj.getComponent<Comp::CollBody>();
    //if(!coll)return;
    auto &bcs = coll->bcs;

    bcs.center -= data->meshAttach.update(bcs.center);
    //movimiento
    bcs.velocity.y -= 1000 * deltaTime; // gravedad
    
    bcs.velocity.x *= MOVE_SPEED_SLOWDOWN;
    bcs.velocity.z *= MOVE_SPEED_SLOWDOWN;

    if(fabsf(bcs.velocity.x) < 0.001f && fabsf(bcs.velocity.z) < 0.001f)
    {
      bcs.velocity.x = 0;
      bcs.velocity.z = 0;
    }
    
    if (User::ctx.isCutscene) {
      // Si estamos en una cinemática, no permitimos el control del jugador, como dialogos
      return;
    }
    //auto held = joypad_get_buttons_held(JOYPAD_PORT_1);
    auto joypad = joypad_get_inputs(JOYPAD_PORT_1);


    float playerRotSpeed = deltaTime * ROT_SPEED;   // velocidad de rotación
    float playerSpeed = deltaTime * MOVE_SPEED;     // velocidad de traslación
    
    data->playerRotX += (float)joypad.stick_x * playerRotSpeed; // rotación horizontal con stick
    //data->Angle = atan2f(camPos.x-obj.pos.x, camPos.z-obj.pos.z);

    fm_vec3_t euler{0.0f, data->playerRotX, 0.0f};
    fm_quat_from_euler(&obj.rot, euler.v);
    fm_quat_norm(&obj.rot, &obj.rot);

    float forward = (float)joypad.stick_y;

    // dirección hacia donde apunta el player
    float dirX = fm_sinf(data->playerRotX);
    float dirZ = fm_cosf(data->playerRotX);

    // mover en esa dirección
    bcs.velocity.x += dirX * forward * playerSpeed;
    bcs.velocity.z -= dirZ * forward * playerSpeed;
    //fm_vec3_t rotAxis{0.0f, 1.0f, 0.0f};
    //fm_quat_rotate(&obj.rot, &obj.rot, &rotAxis, deltaTime * 0.5f);
    //fm_quat_norm(&obj.rot, &obj.rot);

    //actualizar camara activa con la posición del player
    auto &cam = SceneManager::getCurrent().getActiveCamera();

    data->camTarget.v[0] = obj.pos.x + dirX;
    data->camTarget.v[1] = obj.pos.y + 20.0f; // altura de la cámara
    data->camTarget.v[2] = obj.pos.z - dirZ;
    
    data->camPos = obj.pos;
    data->camPos.v[1] += 20.0f; // altura de la cámara

    cam.setLookAt(data->camPos, data->camTarget);

    //sonidos de paso que me robe jijija

    if(joypad.stick_y > 0.05f || joypad.stick_y < -0.05f)
    {
      if (data->stepSFXCooldown == 0) {
        uint32_t sfxPool[3] {
          "sfx/StepStone00.wav64"_asset,
          "sfx/StepStone01.wav64"_asset,
          "sfx/StepStone02.wav64"_asset
        };
        auto sfx = AudioManager::play2D(sfxPool[rand() % 3]);
        sfx.setSpeed(1.0f - (P64::Math::rand01() * 0.21f));
        sfx.setVolume(0.3f);

        data->stepSFXCooldown = 30 + (rand() % 4);
      }
    }

    if (data->stepSFXCooldown > 0)--data->stepSFXCooldown;
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    /*
    auto coll = obj.getComponent<Comp::CollBody>();
    //if(!coll)return;
    auto &bcs = coll->bcs;
    //Dibujar texto DEBUG
    float posY = 30.0f; // conf.screenHeight - SCREEN_EDGE - 20.0f;
    rdpq_textparms_t TEXT_CENTER{
      .width = (int16_t)rdpq_get_attached()->width,
      .align = ALIGN_CENTER,
      .disable_aa_fix = true
    };

    DrawLayer::use2D();
      rdpq_text_printf(&TEXT_CENTER, User::FONT_TEXT, 0, posY,
        "Player Pos: %.2f, %.2f, %.2f",
        obj.pos.x, obj.pos.y, obj.pos.z
      );

      rdpq_text_printf(&TEXT_CENTER, User::FONT_TEXT, 0, posY + 20.0f,
        "Player velocity: %.2f, %.2f",
        bcs.velocity.x, bcs.velocity.z
      );
    DrawLayer::useDefault();
    */
  }

  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {
  }

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
    if(event.otherMesh)
    {
      data->meshAttach.setReference(event.otherMesh);
      return;
    }

  }
}
