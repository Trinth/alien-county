//Inclusion de las librerias
//-------------------------------------
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


#ifdef WEB
//Esto solo se incluye en el codigo si se pone #define WEB antes o si se pone -DWEB en el compilador (Esto es super util para hacer cosas para varias plataformas como windows, linux, web, android, etc) (Tambien se puede utilizar para otras cosas)
#include <emscripten.h>
#endif
//-------------------------------------

int running = 1;//Esta variable controla si el juego sigue siendo ejecutado
SDL_Renderer *renderer = NULL; //Esta variable almacena es para dibujar cosas en las ventanas
SDL_Window *win = NULL; //Esta variable alamacena la ventana




void MainLoop(){

    SDL_Event e; // Esta variable se utliza para leer eventos de SDL como las teclas / el boton de salir

    while ( SDL_PollEvent(&e) ) { //Leer todas las teclas
        switch(e.type ){
            case SDL_QUIT: // Esto ocurre cuando presionas el boton de salir
                running = 0;
                break;
        }
    }

    SDL_RenderClear(renderer); //Comenzar a dibujar

    //Aca iria el codigo para dibujar

    SDL_RenderPresent(renderer); //Terminar de dibujar

}

int main (){

	SDL_CreateWindowAndRenderer(800, 600,0,&win,&renderer); //Esto arranca la ventana

    //Esto arracna el audio
    //-------------------------------------------------------
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    //-------------------------------------------------------

    //Aqui hay que cargar los recursos del juego

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
