#ifndef PLAYERH
#define PLAYERH



typedef struct PLAYER{

    Vector2 position;
    Vector2 speed;

    int Anim;
    int AnimTimer;

    bool Abducting; //Esto es verdadero cuando el jugador esta abudciendo en NPC

    int AbductedNPC; //This keeps track pf which NPC is being abducted
}PLAYER;


#endif
