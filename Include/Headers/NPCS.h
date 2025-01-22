#ifndef NPCHEADER
#define NPCHEADER


typedef struct NPC{

    Vector2 position;
    Vector2 speed;

}NPC;

void ExecuteLogicForAllNPCS();
void ExecuteLogicForNPC(int i);

#endif
