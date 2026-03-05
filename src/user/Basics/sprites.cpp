//este script es solo para SPRITES ANIMADOS CON TAMAÑO DEFINIDO (checar ejemplo j25)
//ESTA COMPLETAMENTE COMENTADO POR QUE NO LO USO
#include "sprites.h"

#include "script/userScript.h"
#include <scene/scene.h>
#include "scene/sceneManager.h"


#include "../../p64/sceneTable.h"
#include "vi/swapChain.h"

//constinit P64::PTX::Sprites* test = nullptr;

namespace
{
  //aqui dejo la apertura para la funcion de particulas
}

//Aqui basicamente establecemos las propiedades de cada imagen que se va a mostrar, como el tamaño, si es rotativa o no, etc.
void P64::User::Sprites::init()
{
  /*
  test = new PTX::Sprites("rom:/ptx/test.sprite", PTX::Sprites::Conf{
    .maxSize = 256,
    .isRotating = false,
    .noRng = false,
  });
  test->setColor({0xFF, 0xEF, 0xFF, 0xFF});
  */
}

void P64::User::Sprites::destroy()
{
  //delete test; test = nullptr;
}

void P64::User::Sprites::draw()
{
  /*
  float deltaTime = VI::SwapChain::getDeltaTime();

  float far = P64::SceneManager::getCurrent().getActiveCamera().far; //Funcion que llama al scenemanager para obtener la camra actual y su valor de far, que es la distancia a la que se pueden ver los objetos en la escena.
  far = 1.0f / (far / 500.f); //Aqui se hace una especie de ajuste para que los sprites se vean bien a diferentes distancias.
  Float2 pos = {100, 100}; //Posicion en la pantalla donde se va a dibujar el sprite
  far * = 64; //Aqui se ajusta el tamaño del sprite en funcion de la distancia a la camara, para que se vea mas grande cuando esta cerca y mas pequeño cuando esta lejos.
  tpx_state_set_base_size((uint16_t)far); //Funcion que establece el tamaño base de los sprites, que es el valor calculado anteriormente.

  test->draw(deltaTime); //Finalmente se llama a la funcion draw del sprite
  */
}