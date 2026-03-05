#pragma once
#include <libdragon.h>

/*
Este es un namespace con algunas variables relevantes diganse "Globales" para el usuario
como la posición del jugador, la cámara, etc.

Pudiendolos utilizar mas adelante en cualquier parte del código sin necesidad de pasarlos como parámetros
en cada lugar que ocupes
*/

namespace P64::User
{
  struct Context
  {
    uint16_t controlledId{0};
    fm_vec3_t playerPos{};

    uint16_t cameraId{0};
    fm_vec3_t camPos{};

    uint32_t frame{0};
    uint8_t isCutscene{false};
    uint8_t canInteract{false};
  };
  //Asi nos referiremos al context
  extern Context ctx;
}