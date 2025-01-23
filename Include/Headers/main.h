#ifndef MainHeaderIncluded //Esto es para que no añadir este archivo dos veces
#define MainHeaderIncluded



    #define YELLOW (Color){255, 0, 0, 255}

    #define WHITE (Color){255, 255, 255, 255}
    #define BLACK (Color){0, 0, 0, 255}
    #define VIOLET (Color){255, 0, 255, 255}

    #define RED (Color){255, 0, 0, 255}
    #define GREEN (Color){0, 255, 0, 255}
    #define BLUE (Color){0, 0, 255, 255}



    //Variables cruciales no especificas
    //--------------------------------------------------------------------------
    int running = 1;//Esta variable controla si el juego sigue siendo ejecutado

    //--------------------------------------------------------------------------




    //Estas variables son utilizadas para correr la pantalla en pantalla completa
    int FullScreenOffsetX = 0;
    int FullScreenOffsetY = 0;



    int CurrentLevelWidth = 50; //Cuantas unidades hay en el eje x en el nivel actual
    int CurrentLevelHeight = 50; //Cuantas unidades hay en el eje y en el nivel actual

    #define UnitLenght 8 //Tamaño de las unidades en la simulación (Modo simple) Utilizado para convertir la posicion de los NPC de a perspectiva isometrica y para la simulación de los NPCS



    //Defincion de estructuras
    typedef struct Rectangle {
        int x;                // Posicion en x del rectangulo
        int y;                // Posicion en y del rectangulo
        int width;            // Ancho del rectangulo
        int height;           // Alto del rectangulo
    } Rectangle;

    typedef struct Vector2 {
        int x;
        int y;
    } Vector2;

    //Funciones y estructuras utilizadas para renderizar
    //---------------------------------------------------------------------------

    int zoom = 3; //Que tanto zoom tiene la pantalla

    SDL_Renderer *renderer = NULL; //Esta variable almacena es para dibujar cosas en las ventanas
    SDL_Window *win = NULL; //Esta variable alamacena la ventana

    #define ResoultionW 800 //Ancho de la ventana deseada
    #define ResoultionH 600 //Alto de la ventana deseada

    typedef struct Color {
        unsigned char r;        // Color red value
        unsigned char g;        // Color green value
        unsigned char b;        // Color blue value
        unsigned char a;        // Color alpha value
    } Color;


    typedef struct Camera2D {
        Vector2 offset;         // Camera offset (displacement from target)
        Vector2 target;         // Camera target (rotation and zoom origin)
    } Camera2D;


    Camera2D cam; //Defincion de la camara principal


    void DrawRectangle(int x, int y, int w, int h, Color color);
    void DrawTexturePro(SDL_Texture *img, Rectangle Origin, Rectangle Destination, int Rotation, Color color);
    //---------------------------------------------------------------------------


    //Caracteristicas de una unidad isometrica
    //---------------------------------------------------------------------------
    const int IsoUnitLenght = 12;
    const int IsoUnitDiameter = IsoUnitLenght / 2;
    const int IsoUnitRadius = (IsoUnitDiameter / 2) + (IsoUnitDiameter % 2);
    //---------------------------------------------------------------------------



    //Valores para conversion isometrica (Por ejemplo: Esto es utilizado para saber donde esta el jugador en el mapa)
    //---------------------------------------------------------------------------

        double IsoToTileA ;
        double IsoToTileB ;
        double IsoToTileC ;
        double IsoToTileD ;

        Vector2 ToTileCoordinates(int x, int y);
    //-------------------------------------------------------------------------



    bool CheckCollisionRecs(Rectangle REC1,Rectangle REC2);


#endif
