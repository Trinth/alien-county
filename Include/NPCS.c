#include "Headers/NPCS.h"
#include "Headers/main.h"

#define NPCWIDTH 8
#define NPCHEIGHT 8

#define MaxZ_Speed 2.0f
#define Gravity 0.05f

NPC *NPCS;

int CurrentNumberOfNPCS = 15;




void LoadNPCS(){

    NPCS = (NPC*)realloc(NPCS,sizeof(NPC)*CurrentNumberOfNPCS);

    for(int i = 0; i < CurrentNumberOfNPCS; i ++){
        NPCS[i].position.x = RandomNum(0, (CurrentLevelWidth * 8)-8);
        NPCS[i].position.y = RandomNum(0, (CurrentLevelHeight * 8)-8);

        NPCS[i].speed.x = RandomNum(1, 1);
        NPCS[i].speed.y = RandomNum(1, 1);

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

        NPCS[i].Z = 0;
    }

}


void ExecuteLogicForAllNPCS(){
    for(int i = 0; i < CurrentNumberOfNPCS; i ++){
        ExecuteLogicForNPC(i);
    }


}

void ExecuteLogicForNPC(int i){


    //TODO: Crear mas tipos de comportamientos para los NPC

    if(NPCS[i].BeingAdbucted == false && NPCS[i].Z == 0){
         NPCRandomMovement(i);
    }
    else{
        NPCAbduction_Gravity(i);
    }



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

void NPCAbduction_Gravity(int i){

    if(NPCS[i].BeingAdbucted == false){
        NPCS[i].SpeedZ += Gravity;

        if(NPCS[i].SpeedZ > MaxZ_Speed){
            NPCS[i].SpeedZ = MaxZ_Speed;
        }
    }

    NPCS[i].Z += NPCS[i].SpeedZ;

    if(NPCS[i].Z > 0){
        NPCS[i].Z = 0.0f;
    }
}





void DrawNPCS_SIMPLE(){
    for(int i = 0; i < CurrentNumberOfNPCS; i ++){
        DrawRectangle(NPCS[i].position.x - cam.target.x,NPCS[i].position.y - cam.target.y,NPCWIDTH,NPCHEIGHT,BLACK);
    }
}

//Esta funcion dibuja los NPCS en el modo isometrico
void DrawNPCS(){

    for(int i = 0; i < CurrentNumberOfNPCS; i ++){

        float x = NPCS[i].position.x;
        float y = NPCS[i].position.y;


        DrawRectangle( ((x * IsoUnitDiameter)-(y * IsoUnitDiameter)) / UnitLenght - cam.target.x,
                      (((x * IsoUnitRadius)+(y * IsoUnitRadius)) / UnitLenght - cam.target.y) + (int)NPCS[i].Z,
                      NPCWIDTH,NPCHEIGHT,BLACK);
    }

}
