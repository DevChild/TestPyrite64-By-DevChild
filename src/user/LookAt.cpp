//FUNCION QUE HACE QUE UN PLANO MIRE A CAMARA UUUUUUUH, solo adjuntalo y ya estara :b

#include "script/userScript.h"
#include "scene/sceneManager.h"

#include "Basics/context.h"

namespace P64::Script::C2C1D9FF697E777B
{
  P64_DATA(
    // Put your arguments here if needed, those will show up in the editor.
    //
    // Types that can be set in the editor:
    // - uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t
    // - float
    // - AssetRef<sprite_t>
    // - ObjectRef

    float Angle;
  );

  // The following functions are called by the engine at different points in the object's lifecycle.
  // If you don't need a specific function you can remove it.

  void initDelete(Object& obj, Data *data, bool isDelete)
  {
    if(isDelete) {
      // do cleanup
      return;
    }
    // do initialization
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    auto &cam = SceneManager::getCurrent().getActiveCamera();
    fm_vec3_t camPos = cam.getPos();
    //fm_vec3_t cam = User::ctx.camPos;

    data->Angle = atan2f(camPos.x-obj.pos.x, camPos.z-obj.pos.z);

    fm_vec3_t euler{0.0f, -data->Angle, -T3D_PI};
    fm_quat_from_euler(&obj.rot, euler.v);
    fm_quat_norm(&obj.rot, &obj.rot);
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
  }

  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {
  }

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
  }
}
