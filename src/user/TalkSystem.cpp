#include "script/userScript.h"
#include "scene/sceneManager.h"

#include "globals.h"
#include "script/userScript.h"
#include "Basics/context.h"
#include "scene/components/collBody.h"
#include "scene/components/collMesh.h"
#include <scene/components/nodeGraph.h>
#include "../p64/assetTable.h"

namespace P64::Script::C86B31D40D42AB7B
{
  P64_DATA(
    bool collidedThisFrame;
    //ESTO ES INESTABLE, EL ASSET TABLE CAMBIA DE IDS DE AUDIOS CADA QUE SE AGREGA UNO (sistema inxcompleto)
    [[P64::Name("Voice")]]
    uint32_t assetId;
  );

  void initDelete(Object& obj, Data *data, bool isDelete)
  {
    if(isDelete) {
      return;
    }
    data->collidedThisFrame = false;
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    //Esto es para la deteccion dinamica del trigger, si el player colisiona con el trigger o se salio
    User::ctx.canInteract = data->collidedThisFrame;
    data->collidedThisFrame = false;
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
  }

  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {
  }

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
    if(!event.otherBCS)return;
    //utilizamos e ctx para verificar si el objeto tiene la id del player actual, para evitar que otros objetos colisionen y activen el evento
    if(event.otherBCS->obj->id != User::ctx.controlledId)return;
    //chequea si no esta en cinematica
    if (User::ctx.isCutscene) return;
    data->collidedThisFrame = true;

    //Aca declaramos inputs
    auto pressed = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    //Aqui obtenemos el nodo que esta adjunto al objeto pára poder ejecutarñlo desde aqui
    auto graphComp = obj.getComponent<Comp::NodeGraph>();
    
    //checa si no esta corriendo el nodo
    if(graphComp->isRunning()) return;
    //si se preciona ejecutar el nodo y audio (incompleto)
    if(pressed.a) {
      if (data->assetId != 0) {
        auto sfx = AudioManager::play2D((wav64_t*)AssetManager::getByIndex(data->assetId));
        sfx.setVolume(0.5f);
      }
      graphComp->run();
    }
  }
}
