#include "Headers/NPCS.h"
#include "Headers/main.h"

#define NPCWIDTH 8
#define NPCHEIGHT 8

NPC *NPCS;

int CurrentNumberOfNPCS = 15;




void LoadNPCS(){

    NPCS = (NPC*)realloc(NPCS,sizeof(NPC)*CurrentNumberOfNPCS);

    for(int i = 0; i < CurrentNumberOfNPCS; i ++){
        NPCS[i].position.x = RandomNum(0, (CurrentLevelWidth * 8)-8);
        NPCS[i].position.y = RandomNum(0, (CurrentLevelHeight * 8)-8);

        NPCS[i].speed.x = RandomNum(1, 4);
        NPCS[i].speed.y = RandomNum(1, 4);

        switch(RandomNum(0,3)){
            case 1:
                NPCS[i].speed.x *= -1;
                NPCS[i].speed.y *= -1;
                break;
            case 2:
                NPCS[i].speed.x *= -1;
                break;
            case 3:
                NPCS[i].speed.y *= -1;
                break;

        }

    }

}


void ExecuteLogicForAllNPCS(){
    for(int i = 0; i < CurrentNumberOfNPCS; i ++){
        ExecuteLogicForNPC(i);
    }


}

void ExecuteLogicForNPC(int i){
    //TODO: Crear mas tipos de comportamientos para los NPC
    NPCRandomMovement(i);

}

//Logica para el comportamiento de movimieto aleatorio
void NPCRandomMovement(int i){

    //Colision con los bordes del nivel
    //--------------------------------------------------------------------------------------------------------------------
    if(NPCS[i].position.x + NPCS[i].speed.x < 0 || NPCS[i].position.x + NPCS[i].speed.x > (CurrentLevelWidth * 8)-8){
        NPCS[i].speed.x *= -1;
    }
    if(NPCS[i].position.y + NPCS[i].speed.y < 0 || NPCS[i].position.y + NPCS[i].speed.y > (CurrentLevelHeight * 8)-8){
        NPCS[i].speed.y *= -1;
    }
    //--------------------------------------------------------------------------------------------------------------------


    NPCS[i].position.x += NPCS[i].speed.x;
    NPCS[i].position.y += NPCS[i].speed.y;
}


void DrawNPCS(){
    for(int i = 0; i < CurrentNumberOfNPCS; i ++){
        DrawRectangle(NPCS[i].position.x,NPCS[i].position.y,NPCWIDTH,NPCHEIGHT,BLACK);
    }
}
