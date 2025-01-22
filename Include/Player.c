#include "Headers/Player.h"

#define CameraSpeed 3

PLAYER player = {0,0,0,0};

void ExecutePlayerLogic(){

    //if(AllKeys[SDL_SCANCODE_LEFT])


}

void SimpeCameraMovement(){

    if(AllKeys[SDL_SCANCODE_LEFT].Down){
        cam.target.x -= CameraSpeed;
    }
    else if(AllKeys[SDL_SCANCODE_RIGHT].Down){
        cam.target.x += CameraSpeed;
    }
    if(AllKeys[SDL_SCANCODE_UP].Down){
        cam.target.y -= CameraSpeed;
    }
    else if(AllKeys[SDL_SCANCODE_DOWN].Down){
        cam.target.y += CameraSpeed;
    }


}


void SimpePlayer(){
    int i = 0;
    if(AllKeys[SDL_SCANCODE_A].Down){
        NPCS[i].position.x -= 1;
    }
    else if(AllKeys[SDL_SCANCODE_D].Down){
        NPCS[i].position.x += 1;
    }
    if(AllKeys[SDL_SCANCODE_W].Down){
        NPCS[i].position.y -= 1;
    }
    else if(AllKeys[SDL_SCANCODE_S].Down){
        NPCS[i].position.y += 1;
    }


}

void PlayerLogic(){

    if(AllKeys[SDL_SCANCODE_A].Down){
        player.position.x -= 1;
    }
    else if(AllKeys[SDL_SCANCODE_D].Down){
        player.position.x += 1;
    }
    if(AllKeys[SDL_SCANCODE_W].Down){
        player.position.y -= 1;
    }
    else if(AllKeys[SDL_SCANCODE_S].Down){
        player.position.y += 1;
    }

}

void DrawPlayer(){


}
