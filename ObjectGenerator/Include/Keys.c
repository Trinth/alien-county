#include "Headers/Keys.h"


void UpdateKeys(){

    for(int i = 0; i < 322; i++){
        AllKeys[i].IsPressed = false;
        AllKeys[i].IsReleased = false;
    }


    SDL_Event e; // Esta variable se utliza para leer eventos de SDL como las teclas / el boton de salir

    while ( SDL_PollEvent(&e) ) { //Leer todas las teclas
        switch(e.type ){
            case SDL_QUIT: // Esto ocurre cuando presionas el boton de salir
                running = 0;
                break;
            case SDL_KEYDOWN:
                    AllKeys[e.key.keysym.scancode].Down = true;
                    break;
            case SDL_KEYUP:
                AllKeys[e.key.keysym.scancode].Down = false;
                AllKeys[e.key.keysym.scancode].IsPressedHelper = false;
                break;
        }
    }


}
