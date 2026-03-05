/**
* @copyright 2026 - Max Bebök
* @license MIT
*/

//Aqui se refiere todo lo relacionado con los mensajes de dialogo, como el texto
#pragma once
#include <lib/types.h>

#define MSG(ID, NEXT_ID, IMAGE_ID, TEXT) \
  if (messageId == ID##_hash) { \
    return { TEXT, NEXT_ID, IMAGE_ID, 0 }; \
  }

#define MSG_MODAL(ID, IMAGE_ID, TEXT) \
  if (messageId == ID##_hash) { \
    return { TEXT, 0, IMAGE_ID, 1 }; \
  }

namespace P64::User::Dialog
{
  struct Message
  {
    const char* const text;
    uint32_t nextMessageId;
    uint8_t imageId;
    uint8_t isModal;
  };

  #define CTRL_SLOW "\x01"

  constexpr uint8_t IMG_HEAD = 0;
  constexpr uint8_t NON_MODAL = 0;
  constexpr uint8_t MODAL = 1;

  constexpr Message getMessage(uint32_t messageId)
  {

//Aqui establecemos los dialogos del juego que despues referenciaremos en el sistema de nodos

// ======== test ========//
    MSG("IntroStart", 0, IMG_HEAD,
      "Bienvenido a mi hogar\x01...\n"
      "Joven viajero... xddddd"
    );
    MSG_MODAL("ModalTest", IMG_HEAD,
        "Elije Pibe\n"
        "SI|NO..."
    );
    return {};
  }
}

#undef MESSAGE_ENTRY