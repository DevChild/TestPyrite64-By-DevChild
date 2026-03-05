
#pragma once
#include <renderer/particles/ptxSprites.h>

//DECALARACION DE FUNCIONES PARA LOS SPRITES, COMO LA INICIALIZACION, DIBUJADO, ETC. 
//ESTO SE HACE PARA MANTENER EL CODIGO ORGANIZADO Y FACIL DE MANTENER.

//Ademas si viene en el archivo de pruebas juasjaus

namespace P64::User::Sprites
{
  //inline PTX::Sprites* test;

  void init();
  void destroy();

  void draw();
}