#ifndef NPCHEADER
#define NPCHEADER


typedef struct NPC{

    Vector2 position; //The current position of the NPC
    Vector2 speed; //This is the speed of the NPC

    bool BeingAdbucted; //Checks if the NPC is beign abducted

    //bool Grounded; //Verdadero cuando su valor en Z es 0

    float Z; //Position in the z axis

    float SpeedZ; //Speed in the z axis

}NPC;

void ExecuteLogicForAllNPCS();
void ExecuteLogicForNPC(int i);

#endif
