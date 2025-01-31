//Inclusion de las librerias
//-------------------------------------
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Include/Headers/Images.h"
#include "Include/Headers/main.h"
#include "Include/Math.c"
#include "Include/Keys.c"
#include "Include/NPCS.c"
#include "Include/Player.c"

#ifdef WEB
//Esto solo se incluye en el codigo si se pone #define WEB antes o si se pone -DWEB en el compilador (Esto es super util para hacer cosas para varias plataformas como windows, linux, web, android, etc) (Tambien se puede utilizar para otras cosas)
#include <emscripten.h>
#endif
//-------------------------------------






void MainLoop(){

    Uint64 start = SDL_GetPerformanceCounter(); //Esto esta aca para ver cuanto tiempo tarda el juego en ejecutar la logica y dibujar la imagen, midiendo el comienzo del cuadro


    UpdateKeys(); //Actualizar las teclas




    //Ejecutar la logica del jugador
    PlayerLogic();

    //Ejecutar la logica de los NPCS
    ExecuteLogicForAllNPCS();


    SDL_RenderClear(renderer); //Comenzar a dibujar




    //DrawUI();


    //Aca iria el codigo para dibujar

    DrawBackGround(WHITE);

    //DrawGameSimplyfied();

    DrawGame();

    SDL_RenderPresent(renderer); //Terminar de dibujar








    Uint64 end = SDL_GetPerformanceCounter(); //Esto esta aca para ver cuanto tiempo tarda el juego en ejecutar la logica y dibujar la imagen, midiendo el final del cuadro

    float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;//Calcular cuanto tiempo tardo el juego en dibujar un cuadro

    if(elapsedMS < 16.666f){ //Esto es verdadero cuando el juego tarda menos de 16.666 segundos en dibujar un cuadro nuevo, si se ejecuta el codigo de abajo cuanda esta condicion es falsa, el juego se detiene
        SDL_Delay(floor(16.666f - elapsedMS)); //Esperar suficiente tiempo para que la maxima cantidad de cuadros siempre sea 60
    }


}

int main (){
    CalculateIsometicTransformation();

    //Alocar las listas variables aca
    NPCS = calloc(15,sizeof(NPC));

    //Esto es utilizado para poder generar numeros aleatorios, es de las primeras cosas para generar
    srand(time(NULL));

    //Esta funcion va a cargar las caracteristicas de los NPCS, por ahora genera valores aleatorios
    LoadNPCS();

	SDL_CreateWindowAndRenderer(ResoultionW, ResoultionH,0,&win,&renderer); //Esto arranca la ventana

    //Esto arracna el audio
    //-------------------------------------------------------
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    //-------------------------------------------------------

    //Aqui hay que cargar los recursos del juego
    GroundImages = IMG_LoadTexture(renderer, "Resources/Images/Grounds.png");
    PlayerImage = IMG_LoadTexture(renderer, "Resources/Images/Alien.png");



    #ifndef WEB
    while (running) // Esto sigue cuando running es igual a 1
    {
        MainLoop();

    }
    #endif

	#ifdef WEB //Esto es para que funcione con la web
	emscripten_set_main_loop(MainLoop, 0, 1);
	#endif

    //A la hora de salir el codigo pasa por aca, se tiene que descargar todos los recursos aqui

}

void DrawGameSimplyfied(){//Este procedimiento dibuja el juego

    //Esto dibuja el fondo
    //DrawRectangle(0,0,ResoultionW,ResoultionH,WHITE);





    //Esto dibuja el suelo
    int Total = 0;
    for(int x = 0; x < CurrentLevelWidth;x ++){

        for(int y = 0; y < CurrentLevelHeight; y ++){
            if(Total % 2 == 0){
                DrawRectangle((x * UnitLenght) - cam.target.x,(y * UnitLenght) - cam.target.y,UnitLenght,UnitLenght,GREEN);
            }
            else{
                DrawRectangle((x * UnitLenght) - cam.target.x,(y * UnitLenght) - cam.target.y,UnitLenght,UnitLenght,WHITE);
            }
            Total ++;


        }
        Total ++;
    }

    //Esto dibuja el personaje
    Vector2 CurrentPlayerTile = ToTileCoordinates(player.position.x,player.position.y+15);
    DrawRectangle((CurrentPlayerTile.x*8)-cam.target.x,(CurrentPlayerTile.y*8)-cam.target.y,8,8,RED);


    DrawNPCS_SIMPLE();

}

void DrawGame(){//Este procedimiento dibuja el juego

    Vector2 CurrentPlayerTile = ToTileCoordinates(player.position.x,player.position.y+15);

    int Total = 0;
    for(int x = 0; x < CurrentLevelWidth;x ++){

        for(int y = 0; y < CurrentLevelHeight; y ++){


            Total ++;
            if(Total % 2 == 0){
                DrawTexturePro(GroundImages,(Rectangle){0,0,14,7},(Rectangle){(x * IsoUnitDiameter)-(y * IsoUnitDiameter),(x * IsoUnitRadius)+(y * IsoUnitRadius),14,7},0,WHITE);
            }
            else{
                DrawTexturePro(GroundImages,(Rectangle){0,0,14,7},(Rectangle){(x * IsoUnitDiameter)-(y * IsoUnitDiameter),(x * IsoUnitRadius)+(y * IsoUnitRadius),14,7},0,BLUE);
            }

            if(CurrentPlayerTile.x == x && CurrentPlayerTile.y == y){
                DrawTexturePro(GroundImages,(Rectangle){0,0,14,7},(Rectangle){(x * IsoUnitDiameter)-(y * IsoUnitDiameter),(x * IsoUnitRadius)+(y * IsoUnitRadius),14,7},0,RED);
            }
        }
        Total++;

    }
        //Dibujar la sombra del jugador, esta puesto aca para que aparezca antes que los NPC y los edificios / arboles / etc
    DrawTexturePro(PlayerImage,(Rectangle){45,10,15,10},(Rectangle){player.position.x,player.position.y+10,15,10},0,WHITE);


    DrawNPCS();
    DrawPlayer();
}




//Dibujar parte de una imagen, requiere: una imagen, un rectangulo que representa el area de la imagen que dibujar,
//otro rectangulo para dibujar donde dibujar esa parte de la imagen, la rotacion y el color de la imagen.
//La posicion de este procedimiento esta afectada por la de la camara
void DrawTexturePro(SDL_Texture *img, Rectangle Origin, Rectangle Destination, int Rotation, Color color){

    SDL_Rect texO;
    texO.x = (Origin.x);
    texO.y = (Origin.y);
    texO.w = (Origin.width);
    texO.h = (Origin.height);

    SDL_Rect texD;
    texD.x = Destination.x - cam.target.x;
    texD.y = Destination.y - cam.target.y;
    texD.w = Destination.width;
    texD.h = Destination.height;


    texD.x = (texD.x * zoom) + FullScreenOffsetX;
	texD.y = (texD.y * zoom) + FullScreenOffsetY;
	texD.w = texD.w * zoom;
	texD.h = texD.h * zoom;

    SDL_SetTextureColorMod(img, color.r, color.g, color.b);




    if(Rotation != 0){
        float angle = Rotation; // set the angle.
        SDL_Point center = {texO.w * zoom, texO.h * zoom}; // the center where the texture will be rotated.
        SDL_RendererFlip flip = SDL_FLIP_NONE; // the flip of the texture.

        SDL_RenderCopyEx(renderer, img, &texO, &texD , angle, &center, flip);
        SDL_SetTextureColorMod(img, 255, 255, 255);
    }
    else{
        SDL_RenderCopy(renderer, img, &texO, &texD);
        SDL_SetTextureColorMod(img, 255, 255, 255);
    }

}

//Este procedimiento dibuja un rectangulo de cualquier color, la posicion de este procedimiento no esta afectada por la de la camara
void DrawRectangle(int x, int y, int w, int h, Color color){
    SDL_Rect rect;
    rect.x = x*zoom;
    rect.y = y*zoom;
    rect.w = w*zoom;
    rect.h = h*zoom;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void DrawBackGround(Color color){
    DrawRectangle(0,0,ResoultionW,ResoultionH,color);
}

void CalculateIsometicTransformation(){

double a = 0.5f * 12;
double b = -0.5f * 12;
double c = 0.25f * 12;
double d = 0.25f * 12;

const double det = (1 / (a * d - b * c));

IsoToTileA = det * d;
IsoToTileB = det * -b;
IsoToTileC = det * -c;
IsoToTileD = det * a;



}

Vector2 ToTileCoordinates(int x, int y){
    return (Vector2){ ( (x * IsoToTileA) + (y * IsoToTileB)),( (x * IsoToTileC) + (y * IsoToTileD)) };
}

bool CheckCollisionRecs(Rectangle REC1,Rectangle REC2){

    bool collision = false;

    if ((REC1.x < (REC2.x + REC2.width) && (REC1.x + REC1.width) > REC2.x) &&
        (REC1.y < (REC2.y + REC2.height) && (REC1.y + REC1.height) > REC2.y)) collision = true;

    return collision;
}

