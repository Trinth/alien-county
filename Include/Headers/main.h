#ifndef MainHeaderIncluded //Esto es para que no añadir este archivo dos veces
#define MainHeaderIncluded



    #define YELLOW (Color){255, 0, 0, 255}

    #define WHITE (Color){255, 255, 255, 255}
    #define BLACK (Color){0, 0, 0, 255}
    #define VIOLET (Color){255, 0, 255, 255}

    #define RED (Color){255, 0, 0, 255}
    #define GREEN (Color){0, 255, 0, 255}
    #define BLUE (Color){0, 0, 255, 255}




    int running = 1;//Esta variable controla si el juego sigue siendo ejecutado
    SDL_Renderer *renderer = NULL; //Esta variable almacena es para dibujar cosas en las ventanas
    SDL_Window *win = NULL; //Esta variable alamacena la ventana

    #define ResoultionW 800
    #define ResoultionH 600

    int zoom = 1;

    //Estas variables son utilizadas para correr la pantalla en pantalla completa
    int FullScreenOffsetX = 0;
    int FullScreenOffsetY = 0;



    int CurrentLevelWidth = 50; //Cuantas unidades hay en el eje x
    int CurrentLevelHeight = 50; //Cuantas unidades hay en el eje y

    int UnitLenght = 8;



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


    const int IsoUnitLenght = 14;
    const int IsoUnitDiameter = IsoUnitLenght / 2;
    const int IsoUnitRadius = (IsoUnitDiameter / 2) + (IsoUnitDiameter % 2);











#endif
