#include "script/userScript.h"
#include "scene/sceneManager.h"

namespace P64::Script::C33851F2ED7EBB6A
{
  P64_DATA(
    //setemos la velocidad de rotacion desde el editor
    [[P64::Name("Speed")]]
    float speed;
  );

  
  void initDelete(Object& obj, Data *data, bool isDelete)
  {
    if(isDelete) {
      return;
    }

  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    //Aca el script que lo hace rotar (recordar que el motor usa quaternions)
    fm_vec3_t r{0.0f, 1.0f, 0.0f};
    fm_quat_rotate(&obj.rot, &obj.rot, &r, data->speed * deltaTime);
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
