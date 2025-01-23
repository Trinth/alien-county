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
    if(AllKeys[SDL_SCANCODE_SPACE].Down ){



        if(player.Abducting == false){
        Vector2 CurrentPlayerTile = ToTileCoordinates(player.position.x,player.position.y+15);
        for(int i = 0; i < CurrentNumberOfNPCS; i ++){

            if(CheckCollisionRecs((Rectangle){CurrentPlayerTile.x * 8,CurrentPlayerTile.y * 8,14,14},(Rectangle){NPCS[i].position.x,NPCS[i].position.y,NPCWIDTH,NPCHEIGHT}) == true){
                NPCS[i].BeingAdbucted = true;
                player.AbductedNPC = i;
                player.Abducting = true;
                NPCS[i].SpeedZ = -0.4f;
                break;
            }

        }
        }
        else{
            NPCS[player.AbductedNPC].SpeedZ = -0.4f;
        }

    }
    else{


        for(int i = 0; i < CurrentNumberOfNPCS; i ++){

            NPCS[i].BeingAdbucted = false;

        }


        player.Abducting = false;

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

    cam.target.x = player.position.x - ResoultionW / (2 * zoom);
    cam.target.y = player.position.y - ResoultionH / (2 * zoom);

}

//void


void DrawPlayer(){

    player.AnimTimer ++;

    if(player.AnimTimer > 5){
        player.AnimTimer = 0;
        player.Anim ++;
        if(player.Anim >= 4){
            player.Anim = 0;
        }
    }

    if(AllKeys[SDL_SCANCODE_SPACE].Down){
        //Dibujar el rayo succionador
        DrawTexturePro(PlayerImage,(Rectangle){0,10,35,35},(Rectangle){player.position.x-10,player.position.y-11,35,35},0,WHITE);
    }

    //Dibujar al jugador
    DrawTexturePro(PlayerImage,(Rectangle){15*player.Anim,0,15,10},(Rectangle){player.position.x,player.position.y-20,15,10},0,WHITE);



}
