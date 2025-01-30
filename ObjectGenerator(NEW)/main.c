/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

//Descomentar esto para guardar los numeros en forma de texto
//#define SAVENUMBERASTEXT

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"



unsigned char* Return_inverse_array(int number);

unsigned char* Return_array(int number);


unsigned char* Return_Object_Name (int object);

unsigned char* Return_Object_Image_Name (int object);

unsigned char* Return_Object_Icon_Name (int object);

//Caracteristicas de una unidad isometrica
//---------------------------------------------------------------------------
const int IsoUnitLenght = 12;
const int IsoUnitDiameter = IsoUnitLenght / 2;
const int IsoUnitRadius = (IsoUnitDiameter / 2) + (IsoUnitDiameter % 2);
//---------------------------------------------------------------------------

Texture2D UnitTextures;
Texture2D texture;

Texture2D Icons;

Image SaveImage;


Camera2D camera = { 0 };

// layout_name: controls initialization
//----------------------------------------------------------------------------------
bool Largo_en_XEditMode = false;
int Largo_en_XValue = 3;
bool Largo_en_YEditMode = false;
int Largo_en_YValue = 3;
bool Colision_en_XEditMode = false;
int Colision_en_XValue = 3;
bool Colision_en_YEditMode = false;
int Colision_en_YValue = 3;
bool Boton_guardarPressed = false;
bool EqualizarPressed = false;
bool Ver_Objetos_Pressed = false;
bool SobreEscribr_Pressed = false;
bool Img_off_XEditMode = false;
int Img_off_XValue = 0;
bool Img_off_YEditMode = false;
int Img_off_YValue = 0;
bool TransparenciaChecked = false;
bool PegarPressed = false;

//----------------------------------------------------------------------------------

typedef struct Object{
    int Largo_en_X;
    int Largo_en_Y;

    int Colision_en_X;
    int Colision_en_Y;

    int Img_off_X;
    int Img_off_Y;

    Texture2D texture;

    Rectangle position;
}Object;
//Lista variable para los objetos
Object* Allobjects;

int CurrentMode = 0;
//0 = Editing mode
//1 = Object viewing / selection mode

#define Icon_Rows 10
#define IconSize 32



int CurrentlySelectedObject = 0;
bool CurrentlySelectedObjectEditMode = false;

int LastSelectedObject = 0;

int AmountOfObjects = 1;


int MouseX = 0;
int MouseY = 0;


int MovedObject = -1;

bool RightClicking = false;
bool EditorSelectorPressed = false;
bool MoverSelectorPressed = false;
bool EliminarSelectorPressed = false;

Vector2 RightClickPosition;


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{



    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "Editor de objetos");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


    camera = (Camera2D){ 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 5.0f;



    UnitTextures = LoadTexture("Recursos/Grounds.png");
   // Icons = LoadTexture("Objetos/Icons/Icons.png");

    Allobjects = calloc(1,sizeof(Object));
    //Allobjects[0].texture = calloc(1,sizeof(Texture2D));

    LoadAllObjects();


    //GenerateIcons();

    //LoadObject(0);
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic



        //----------------------------------------------------------------------------------



        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

             switch(CurrentMode){
                    case 0:
                        Execute_button_logic();

                        Execute_Other_Logic();


                        BeginMode2D(camera);
                            DrawUnits();
                        EndMode2D();

                        Draw_Tools_Editing_Mode();

                        //DrawText(TextFormat("Amount of objects: %d", AmountOfObjects), 0, 0, 20, RED);
                        //DrawText(TextFormat("Currently selected object: %d", CurrentlySelectedObject), 0, 30, 20, RED);

                        break;
                    case 1:

                        BlockSelectorLogic();
                        DrawBlockSelector();

                        break;
            }






        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    SaveAllObjects();


    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------



    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------


void DrawBlockSelector(){
    int MaxY = (AmountOfObjects / Icon_Rows) + 1;

    //int CurrentDrawObject = 0;

    for(int y = 0; y < MaxY; y ++){

        for(int x = 0; x < Icon_Rows; x ++){
            DrawTexturePro(Icons,(Rectangle){x * 32,y * 32,32,32},(Rectangle){x * 32,y*32,32,32},(Vector2){0,0},0,WHITE);
        }
    }

    if(MovedObject == -1){
        DrawRectangle(MouseX*32,MouseY*32,32,32,(Color){255,0,0,100});
    }
    else{
        DrawRectangle(MouseX*32,MouseY*32,32,32,(Color){0,0,255,100});
    }

    if(RightClicking == true){
        EditorSelectorPressed = GuiButton((Rectangle){ RightClickPosition.x, RightClickPosition.y, 120, 24 }, "Editar");
        MoverSelectorPressed = GuiButton((Rectangle){ RightClickPosition.x, RightClickPosition.y + 32, 120, 24 }, "Mover");
        EliminarSelectorPressed = GuiButton((Rectangle){ RightClickPosition.x, RightClickPosition.y + 64, 120, 24 }, "Eliminar");
    }


}

void BlockSelectorLogic(){


    Vector2 MousePos = GetMousePosition();


    if(RightClicking == false){
        MouseX = truncate(((int)(MousePos.x) / 32),0,Icon_Rows-1);
        MouseY = truncate(((int)(MousePos.y) / 32),0,((AmountOfObjects / Icon_Rows)));
    }


    if(EliminarSelectorPressed == true){
        int Object = (MouseY * Icon_Rows) + MouseX;

        RemoveObject(Object);

        EliminarSelectorPressed = false;

        RightClicking = false;
    }

    if(MoverSelectorPressed == true){
        MovedObject = (MouseY * Icon_Rows) + MouseX;

        MoverSelectorPressed = false;

        RightClicking = false;
    }


    if(EditorSelectorPressed == true){
        EditorSelectorPressed = false;
        RightClicking = false;
        CurrentlySelectedObject = (MouseY * Icon_Rows) + MouseX;
        UpdateCurrentObject();
        CurrentMode = 0;
    }


    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && MovedObject != -1){
        int CurrentObject = (MouseY * Icon_Rows) + MouseX;

        if(CurrentObject < AmountOfObjects){
            Object obj = Allobjects[CurrentObject];

            Allobjects[CurrentObject] = Allobjects[MovedObject];

            Allobjects[MovedObject] = obj;

            UnloadTexture(Icons);
            GenerateIcons();
            Icons = LoadTexture("Objetos/Icons/Icons.png");

            MovedObject = -1;
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && RightClicking == false && MovedObject == -1){
        int CurrentObject = (MouseY * Icon_Rows) + MouseX;

        if(CurrentObject < AmountOfObjects){
            RightClicking = true;

            RightClickPosition = MousePos;
        }

    }

}

void Draw_Tools_Editing_Mode(){
        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        GuiStatusBar((Rectangle){ 660, 8, 120, 24 }, TextFormat("Objeto: %d | Total %d", CurrentlySelectedObject,AmountOfObjects));



        if (GuiSpinner((Rectangle){ 660, 56, 120, 24 }, "Largo en X", &Largo_en_XValue, 1, 10, Largo_en_XEditMode)) Largo_en_XEditMode = !Largo_en_XEditMode;
        if (GuiSpinner((Rectangle){ 660, 88, 120, 24 }, "Largo en Y", &Largo_en_YValue, 1, 10, Largo_en_YEditMode)) Largo_en_YEditMode = !Largo_en_YEditMode;


        EqualizarPressed = GuiButton((Rectangle){ 660, 128, 120, 24 }, "Equalizar");


        if (GuiSpinner((Rectangle){ 660, 168, 120, 24 }, "Colision en X", &Colision_en_XValue, 0, 10, Colision_en_XEditMode)) Colision_en_XEditMode = !Colision_en_XEditMode;
        if (GuiSpinner((Rectangle){ 660, 200, 120, 24 }, "Colision en Y", &Colision_en_YValue, 0, 10, Colision_en_YEditMode)) Colision_en_YEditMode = !Colision_en_YEditMode;


        if (GuiSpinner((Rectangle){ 660, 256, 120, 24 }, "Divergencia en X", &Img_off_XValue, -100, 100, Img_off_XEditMode)) Img_off_XEditMode = !Img_off_XEditMode;
        if (GuiSpinner((Rectangle){ 660, 288, 120, 24 }, "Divergencia en Y", &Img_off_YValue, -100, 100, Img_off_YEditMode)) Img_off_YEditMode = !Img_off_YEditMode;


        GuiCheckBox((Rectangle){ 660, 336, 24, 24 }, "Transparencia", &TransparenciaChecked);
        Boton_guardarPressed = GuiButton((Rectangle){ 660, 368, 120, 24 }, "Nuevo objeto");
        SobreEscribr_Pressed = GuiButton((Rectangle){ 660, 400, 120, 24 }, "Hacer copia");

        Ver_Objetos_Pressed = GuiButton((Rectangle){ 660, 432, 120, 24 }, "Ver objetos");

        if (GuiSpinner((Rectangle){ 660, 464, 120, 24 }, "Objeto selecionado", &CurrentlySelectedObject, 0, AmountOfObjects-1, CurrentlySelectedObjectEditMode)) {
            CurrentlySelectedObjectEditMode = !CurrentlySelectedObjectEditMode;
        }

        PegarPressed = GuiButton((Rectangle){ 660, 496, 120, 24 }, "Pegar imagen");




        if(CurrentlySelectedObject != LastSelectedObject){
            UpdateCurrentObject();
        }

        LastSelectedObject = CurrentlySelectedObject;



        //----------------------------------------------------------------------------------
}

void Execute_button_logic(){
    if(EqualizarPressed == true){
        Colision_en_XValue = Largo_en_XValue;
        Colision_en_YValue = Largo_en_YValue;
    }

    if(Boton_guardarPressed == true){
        Object object = {3,3,3,3,0,0};
        object.texture = LoadTexture("NULL.png");

        AddObject(object);

        CurrentlySelectedObject = AmountOfObjects-1;

        UpdateCurrentObject();
    }
    if(Ver_Objetos_Pressed == true){
        Ver_Objetos_Pressed = false;
        CurrentMode = 1;
        UnloadTexture(Icons);
        GenerateIcons();
        Icons = LoadTexture("Objetos/Icons/Icons.png");
    }
    if(SobreEscribr_Pressed == true){
        Object object = Allobjects[CurrentlySelectedObject];
        //object.texture = LoadTexture("NULL.png");
        SobreEscribr_Pressed = false;

        AddObject(object);

        CurrentlySelectedObject = AmountOfObjects-1;

        UpdateCurrentObject();

    }

}

void Execute_Other_Logic(){

    if(IsKeyPressed(KEY_V) == true || PegarPressed == true){
        PegarPressed = false;
        system("rm out.png");
        system("xclip -se c -t image/png -o > out.png");

        UnloadTexture(Allobjects[CurrentlySelectedObject].texture);

        if(FileExists("out.png")){
            Allobjects[CurrentlySelectedObject].texture = LoadTexture("out.png");
        }

    }


    if(IsKeyPressed(KEY_Q) == true){
        CurrentlySelectedObject--;
        if(CurrentlySelectedObject < 0){
            CurrentlySelectedObject = 0;
        }
        else{
            UpdateCurrentObject();
        }
    }
    else if(IsKeyPressed(KEY_W) == true){
        CurrentlySelectedObject++;
        if(CurrentlySelectedObject > AmountOfObjects-1){
            CurrentlySelectedObject = AmountOfObjects-1;
        }
        else{
            UpdateCurrentObject();
        }
    }

    UpdateObject();
}

void DrawUnits(){

    int Camera_Off_X = (54 );
    int Camera_Off_Y = (28 );


    camera.offset = (Vector2){Camera_Off_X * camera.zoom, Camera_Off_Y * camera.zoom };





    int Total = 0;
    for(int x = 0; x < Largo_en_XValue;x ++){

        for(int y = 0; y < Largo_en_YValue; y ++){


            Total ++;
            if(Total % 2 == 0){
                DrawTexturePro(UnitTextures,(Rectangle){0,0,14,7},(Rectangle){(x * IsoUnitDiameter)-(y * IsoUnitDiameter),(x * IsoUnitRadius)+(y * IsoUnitRadius),14,7},(Vector2){0,0},0,WHITE);
            }
            else{
                DrawTexturePro(UnitTextures,(Rectangle){0,0,14,7},(Rectangle){(x * IsoUnitDiameter)-(y * IsoUnitDiameter),(x * IsoUnitRadius)+(y * IsoUnitRadius),14,7},(Vector2){0,0},0,BLUE);
            }

        }
        Total++;

    }


    Total = 0;
    for(int x = 0; x < Colision_en_XValue;x ++){

        for(int y = 0; y < Colision_en_YValue; y ++){

            Color COL = (Color){255,0,0,100};
            Total ++;
            if(Total % 2 == 0){
                DrawTexturePro(UnitTextures,(Rectangle){0,0,14,7},(Rectangle){(x * IsoUnitDiameter)-(y * IsoUnitDiameter),(x * IsoUnitRadius)+(y * IsoUnitRadius),14,7},(Vector2){0,0},0,COL);
            }
            else{
                DrawTexturePro(UnitTextures,(Rectangle){0,0,14,7},(Rectangle){(x * IsoUnitDiameter)-(y * IsoUnitDiameter),(x * IsoUnitRadius)+(y * IsoUnitRadius),14,7},(Vector2){0,0},0,COL);
            }

        }
        Total++;

    }

    //Dibujar el objeto
    if(TransparenciaChecked == false){
            DrawTexture(Allobjects[CurrentlySelectedObject].texture,Img_off_XValue,Img_off_YValue,WHITE);
    }
    else{
            DrawTexture(Allobjects[CurrentlySelectedObject].texture,Img_off_XValue,Img_off_YValue,(Color){255,255,255,100});
    }
    /*Texture2D TEST = Allobjects[CurrentlySelectedObject].texture;
    DrawTexture(TEST,0,0,RED);*/



}




void GenerateIcons(){

    //unsigned char* name = Return_Object_Image_Name(0);

    int NumberOfObjects = AmountOfObjects;

    RenderTexture2D target = LoadRenderTexture(Icon_Rows * IconSize, IconSize * ((NumberOfObjects / Icon_Rows) + 1) );

    int x = 0;
    int y = 0;


    //Renderizar el icono en 32 * 32
    //------------------------------------------------
    BeginTextureMode(target);
        for(int i = 0; i < NumberOfObjects; i++ ){
            DrawTexturePro(Allobjects[i].texture,(Rectangle){0,0,Allobjects[i].position.width,Allobjects[i].position.height},(Rectangle){x*IconSize,y*IconSize,IconSize,IconSize},(Vector2){0,0},0,WHITE);
            x++;
            if(x >= Icon_Rows){
                x = 0;
                y ++;
            }
        }
    EndTextureMode();
    //------------------------------------------------

     //Crear la imagen para guardar y guardarla
    //------------------------------------------------
    SaveImage = LoadImageFromTexture(target.texture);

    ImageFlipVertical(&SaveImage);

    ExportImage(SaveImage,"Objetos/Icons/Icons.png");
    //------------------------------------------------


}

void CenterImage(){

    Img_off_XValue = texture.width / 2;
    Img_off_YValue = -texture.height / 2;

}




void UpdateCurrentObject(){

    Largo_en_XValue = Allobjects[CurrentlySelectedObject].Largo_en_X;
    Largo_en_YValue = Allobjects[CurrentlySelectedObject].Largo_en_Y;

    Colision_en_XValue = Allobjects[CurrentlySelectedObject].Colision_en_X;
    Colision_en_YValue = Allobjects[CurrentlySelectedObject].Colision_en_Y;

    Img_off_XValue = Allobjects[CurrentlySelectedObject].Img_off_X;
    Img_off_YValue = Allobjects[CurrentlySelectedObject].Img_off_Y;

    texture = Allobjects[CurrentlySelectedObject].texture;

}

void UpdateObject(){
    Allobjects[CurrentlySelectedObject].Largo_en_X = Largo_en_XValue;
    Allobjects[CurrentlySelectedObject].Largo_en_Y = Largo_en_YValue;

    Allobjects[CurrentlySelectedObject].Colision_en_X = Colision_en_XValue;
    Allobjects[CurrentlySelectedObject].Colision_en_Y = Colision_en_YValue;

    Allobjects[CurrentlySelectedObject].Img_off_X = Img_off_XValue;
    Allobjects[CurrentlySelectedObject].Img_off_Y = Img_off_YValue;

}




void LoadAllObjects(){
    printf("Loading\n");
    if(FileExists("Objetos/All.obt")){

        FILE* fp = fopen("Objetos/All.obt","rb");

        int NumberOfObjects = getw(fp);

        Allobjects = realloc(Allobjects,sizeof(Object)*NumberOfObjects);

        for(int i = 0; i < NumberOfObjects; i++ ){

            Allobjects[i].Largo_en_X = getw(fp);
            Allobjects[i].Largo_en_Y = getw(fp);

            Allobjects[i].Colision_en_X = getw(fp);
            Allobjects[i].Colision_en_Y = getw(fp);

            Allobjects[i].Img_off_X = getw(fp);
            Allobjects[i].Img_off_Y = getw(fp);

            Allobjects[i].position.x = getw(fp);
            Allobjects[i].position.y = getw(fp);
            Allobjects[i].position.width = getw(fp);
            Allobjects[i].position.height = getw(fp);



        }




        Image TexturesBuffer = LoadImage("Objetos/Images/All.png");

        //ImageFlipVertical(&TexturesBuffer);

        Texture2D AllTextures = LoadTextureFromImage(TexturesBuffer);

        int x = 0;

        for(int i = 0; i < NumberOfObjects; i++ ){

            printf("Rendering texture with size W: %f H:%f\n",Allobjects[i].position.width,Allobjects[i].position.height);
            printf("And position X: %f Y:%f\n",Allobjects[i].position.x,Allobjects[i].position.y);
            RenderTexture2D target = LoadRenderTexture(Allobjects[i].position.width,Allobjects[i].position.height);

            BeginTextureMode(target);
                    DrawTexturePro(AllTextures,(Rectangle){x,0,Allobjects[i].position.width,Allobjects[i].position.height},
                                               (Rectangle){0,0,Allobjects[i].position.width,Allobjects[i].position.height},(Vector2){0,0},0,WHITE);
                    x += Allobjects[i].position.width;
            EndTextureMode();

            Image buffer = LoadImageFromTexture(target.texture);

            ImageFlipVertical(&buffer);

            Allobjects[i].texture = LoadTextureFromImage(buffer);

        }

        AmountOfObjects = NumberOfObjects;

    }
    else{
        Allobjects[0] = (Object){3,3,3,3,0,0};
        Allobjects[0].position = (Rectangle){0,0,0,0};
        Allobjects[0].texture = LoadTexture("NULL.png");
        printf("HELP\n\n\n\n");
    }

    UpdateCurrentObject();

}

void SaveAllObjects(){

    //Create and save the singular blocks image
    //-------------------------------------------------------------------------------

        Object* objects = calloc(AmountOfObjects,sizeof(Object));


        int x = 0;

        int BiggestHeight = 0;
        int TotalWidth = 0;

        for(int i = 0; i < AmountOfObjects; i++ ){


            //Cargar el nombre de la imagen
            //------------------------------------------------
            //name = Return_Object_Image_Name(i);
            Texture2D tex = Allobjects[i].texture;


            Allobjects[i].position.x = TotalWidth;
            Allobjects[i].position.y = 0;
            Allobjects[i].position.width = tex.width;
            Allobjects[i].position.height = tex.height;

            TotalWidth += tex.width;

            if(tex.height > BiggestHeight){
                BiggestHeight = tex.height;
            }


            objects[i] = Allobjects[i];
        }


        RenderTexture2D target = LoadRenderTexture(TotalWidth,BiggestHeight);

        //------------------------------------------------
        BeginTextureMode(target);
            for(int i = 0; i < AmountOfObjects; i++ ){
                //Texture2D tex = Allobjects[i].texture;

                DrawTexturePro(Allobjects[i].texture,(Rectangle){0,0,Allobjects[i].texture.width,Allobjects[i].texture.height},
                               (Rectangle){x,0,Allobjects[i].texture.width,Allobjects[i].texture.height},(Vector2){0,0},0,WHITE);
                x += Allobjects[i].texture.width;
            }
        EndTextureMode();
        //------------------------------------------------


        //Crear la imagen para guardar y guardarla
        //------------------------------------------------
        Image image = LoadImageFromTexture(target.texture);

        ImageFlipVertical(&image);

        ExportImage(image,"Objetos/Images/All.png");
        //------------------------------------------------

    //-------------------------------------------------------------------------------

    //Save the tile values and the image position / size

    FILE* fp = fopen("Objetos/All.obt","wb");

    putw(AmountOfObjects,fp);

    for(int i = 0; i < AmountOfObjects; i++ ){

        putw(Allobjects[i].Largo_en_X,fp);
        putw(Allobjects[i].Largo_en_Y,fp);

        putw(Allobjects[i].Colision_en_X,fp);
        putw(Allobjects[i].Colision_en_Y,fp);

        putw(Allobjects[i].Img_off_X,fp);
        putw(Allobjects[i].Img_off_Y,fp);


        putw(Allobjects[i].position.x,fp);
        putw(Allobjects[i].position.y,fp);
        putw(Allobjects[i].position.width,fp);
        putw(Allobjects[i].position.height,fp);


    }

    fclose(fp);



}

unsigned char* Return_inverse_array(int number){

    unsigned char* array;

    array = calloc(ReturnNumberOfDigits(number), sizeof(unsigned char));

    int Number = number;
    for(int r = 0; r < ReturnNumberOfDigits(number); r++){
        array[r] = (Number % 10) + '0';
        Number /= 10;
    }

    return array;
}
unsigned char* Return_array(int number){

    const int NumberOfDigits = ReturnNumberOfDigits(number);

    unsigned char* array = Return_inverse_array(number);
    unsigned char* array2;

    array2 = calloc(NumberOfDigits, sizeof(unsigned char));




    for(int e = 0; e <= NumberOfDigits; e++){
       array2[e] = array[NumberOfDigits - e - 1];
    }


    free(array);
    array = NULL;
    return array2;
}



//Appends a new object to the end of the list
void AddObject(Object object){

    AmountOfObjects++;

    Allobjects = realloc(Allobjects,sizeof(Object)*(AmountOfObjects + 1));

    Allobjects[AmountOfObjects-1] = object;

    Allobjects[AmountOfObjects-1].texture = object.texture;
}

//Removes the chosen object and rearenges the list
void RemoveObject(int object){
    //AmountOfObjects--;
    if(object < AmountOfObjects && object >= 0){
        for(int i = object; i < AmountOfObjects; i++){
            Allobjects[i] = Allobjects[i+1];
        }

        AmountOfObjects --;

        UnloadTexture(Icons);
        GenerateIcons();
        Icons = LoadTexture("Objetos/Icons/Icons.png");
    }


}





int ReturnNumberOfDigits(int n){
   int digits = 1;

    if (n != 0){
        n = AbsoluteInteger(n);
        digits = (int)log10(n);
        digits++;
    }

return digits;
}
int AbsoluteInteger(int x){
    if(x < 0){
        return x * -1;
    }
    return x;
}
int truncate(int num, int min, int max){

    if(num < min){
        return min;
    }
    else if(num > max){
        return max;
    }

    return num;

}
