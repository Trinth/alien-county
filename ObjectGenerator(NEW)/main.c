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

int AmountOfObjects = 0;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{



    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "layout_name");


    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


    camera = (Camera2D){ 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 5.0f;



    UnitTextures = LoadTexture("Recursos/Grounds.png");
    Icons = LoadTexture("Objetos/Icons/Icons.png");

    Allobjects = calloc(1,sizeof(Object));
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

                        DrawText(TextFormat("Amount of objects: %d", AmountOfObjects), 0, 0, 20, RED);
                        DrawText(TextFormat("Currently selected object: %d", CurrentlySelectedObject), 0, 30, 20, RED);

                        break;
                    case 1:

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
    DrawTexturePro(Icons,(Rectangle){0,0,Icons.width,Icons.height},(Rectangle){0,0,Icons.width,Icons.height},(Vector2){0,0},0,WHITE);
}

void Draw_Tools_Editing_Mode(){
        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        if (GuiSpinner((Rectangle){ 660, 56, 120, 24 }, "Largo en X", &Largo_en_XValue, 1, 50, Largo_en_XEditMode)) Largo_en_XEditMode = !Largo_en_XEditMode;
        if (GuiSpinner((Rectangle){ 660, 88, 120, 24 }, "Largo en Y", &Largo_en_YValue, 1, 50, Largo_en_YEditMode)) Largo_en_YEditMode = !Largo_en_YEditMode;
        if (GuiSpinner((Rectangle){ 660, 168, 120, 24 }, "Colision en X", &Colision_en_XValue, 1, 50, Colision_en_XEditMode)) Colision_en_XEditMode = !Colision_en_XEditMode;
        if (GuiSpinner((Rectangle){ 660, 200, 120, 24 }, "Colision en Y", &Colision_en_YValue, 1, 50, Colision_en_YEditMode)) Colision_en_YEditMode = !Colision_en_YEditMode;
        Boton_guardarPressed = GuiButton((Rectangle){ 660, 368, 120, 24 }, "Guardar");
        GuiStatusBar((Rectangle){ 660, 8, 120, 24 }, "Objeto");
        EqualizarPressed = GuiButton((Rectangle){ 660, 128, 120, 24 }, "Equalizar");
        Ver_Objetos_Pressed = GuiButton((Rectangle){ 660, 336, 120, 24 }, "Ver objetos");
        SobreEscribr_Pressed = GuiButton((Rectangle){ 660, 432, 120, 24 }, "Sobre escribr");
        if (GuiSpinner((Rectangle){ 660, 256, 120, 24 }, "Divergencia en X", &Img_off_XValue, -100, 100, Img_off_XEditMode)) Img_off_XEditMode = !Img_off_XEditMode;
        if (GuiSpinner((Rectangle){ 660, 288, 120, 24 }, "Divergencia en Y", &Img_off_YValue, -100, 100, Img_off_YEditMode)) Img_off_YEditMode = !Img_off_YEditMode;

        GuiCheckBox((Rectangle){ 660, 400, 24, 24 }, "Transparencia", &TransparenciaChecked);
        //----------------------------------------------------------------------------------
}

void Execute_button_logic(){
    if(EqualizarPressed == true){
        Colision_en_XValue = Largo_en_XValue;
        Colision_en_YValue = Largo_en_YValue;
    }

    if(Boton_guardarPressed == true){
        //SaveNewObject();
        //Object object;
        Object object = {Largo_en_XValue,Largo_en_YValue,Colision_en_XValue,Colision_en_YValue,Img_off_XValue,Img_off_YValue};
        object.texture = texture;

        AddObject(object);

        CurrentlySelectedObject = AmountOfObjects;
    }
    if(Ver_Objetos_Pressed == true){
        Ver_Objetos_Pressed = false;
        CurrentMode = 1;
        UnloadTexture(Icons);
        GenerateIcons();
        Icons = LoadTexture("Objetos/Icons/Icons.png");
    }
}

void Execute_Other_Logic(){
    if(IsKeyPressed(KEY_V) == true){
        system("xclip -se c -t image/png -o > out.png");
        texture = LoadTexture("out.png");
        CenterImage();
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
        if(CurrentlySelectedObject > AmountOfObjects){
            CurrentlySelectedObject = AmountOfObjects;
        }
        else{
            UpdateCurrentObject();
        }
    }




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
            DrawTexture(texture,Img_off_XValue,Img_off_YValue,WHITE);
    }
    else{
            DrawTexture(texture,Img_off_XValue,Img_off_YValue,(Color){255,255,255,100});
    }


}




void GenerateIcons(){

    unsigned char* name = Return_Object_Image_Name(0);

    int NumberOfObjects = Return_number_of_objects();

    Texture2D* textures = calloc(NumberOfObjects, sizeof(Texture2D));

    RenderTexture2D target = LoadRenderTexture(Icon_Rows * IconSize, IconSize * ((NumberOfObjects / Icon_Rows) + 1) );

    int x = 0;
    int y = 0;

    for(int i = 0; i < NumberOfObjects; i++ ){
         //Cargar el nombre de la imagen
        //------------------------------------------------
        name = Return_Object_Image_Name(i);
        textures[i] = LoadTexture(name);
    }

    //Renderizar el icono en 32 * 32
    //------------------------------------------------
    BeginTextureMode(target);
        for(int i = 0; i < NumberOfObjects; i++ ){
            DrawTexturePro(textures[i],(Rectangle){0,0,textures[i].width,textures[i].height},(Rectangle){x*IconSize,y*IconSize,IconSize,IconSize},(Vector2){0,0},0,WHITE);
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

//Makes a new object file
/*void SaveNewObject(){

    int object = Return_number_of_objects();

    FILE *fp;

    unsigned char* name = Return_Object_Name(object);

    fp = fopen(name,"wb");

    Add_number_to_file(Largo_en_XValue,fp);
    Add_number_to_file(Largo_en_YValue,fp);

    Add_number_to_file(Colision_en_XValue,fp);
    Add_number_to_file(Colision_en_YValue,fp);

    Add_number_to_file(Img_off_XValue,fp);
    Add_number_to_file(Img_off_YValue,fp);


    fclose(fp);

    free(name);


    name = NULL;

    SaveImage = LoadImageFromTexture(texture);

    name = Return_Object_Image_Name(object);

    ExportImage(SaveImage, name);
}*/

//Save an object file specifically
/*void SaveCurrentObject(int object){

    FILE *fp;

    unsigned char* name = Return_Object_Name(object);

    fp = fopen(name,"wb");

    Add_number_to_file(Largo_en_XValue,fp);
    Add_number_to_file(Largo_en_YValue,fp);

    Add_number_to_file(Colision_en_XValue,fp);
    Add_number_to_file(Colision_en_YValue,fp);

    Add_number_to_file(Img_off_XValue,fp);
    Add_number_to_file(Img_off_YValue,fp);


    fclose(fp);

    free(name);


    name = NULL;

    SaveImage = LoadImageFromTexture(texture);

    name = Return_Object_Image_Name(object);

    ExportImage(SaveImage, name);

}*/




void UpdateCurrentObject(){

    Largo_en_XValue = Allobjects[CurrentlySelectedObject].Largo_en_X;
    Largo_en_YValue = Allobjects[CurrentlySelectedObject].Largo_en_Y;

    Colision_en_XValue = Allobjects[CurrentlySelectedObject].Colision_en_X;
    Colision_en_YValue = Allobjects[CurrentlySelectedObject].Colision_en_Y;

    Img_off_XValue = Allobjects[CurrentlySelectedObject].Img_off_X;
    Img_off_YValue = Allobjects[CurrentlySelectedObject].Img_off_Y;

    texture = Allobjects[CurrentlySelectedObject].texture;

}






void LoadAllObjects(){
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


        unsigned char* name = Return_Object_Image_Name(0);


        for(int i = 0; i < NumberOfObjects; i++ ){
            //Cargar el nombre de la imagen
            //------------------------------------------------
            name = Return_Object_Image_Name(i);
            Allobjects[i].texture = LoadTexture(name);

        }

        AmountOfObjects = NumberOfObjects;

    }
    else{
       // running = 0;
        Allobjects[0] = (Object){3,3,3,3,0,0};
    }

}

void SaveAllObjects(){

    //AmountOfObjects = AmountOfObjects - 2;
    //Create and save the singular blocks image
    //-------------------------------------------------------------------------------

        //unsigned char* name = Return_Object_Image_Name(0);

        //int NumberOfObjects = Return_number_of_objects();

        Texture2D* textures = calloc(AmountOfObjects, sizeof(Texture2D));
        Object* objects = calloc(AmountOfObjects,sizeof(Object));


        int x = 0;

        int BiggestHeight = 0;
        int TotalWidth = 0;

        for(int i = 0; i < AmountOfObjects; i++ ){
            //Cargar el nombre de la imagen
            //------------------------------------------------
            //name = Return_Object_Image_Name(i);
            textures[i] = Allobjects[i].texture;

            objects[i].position.x = TotalWidth;
            objects[i].position.x = 0;
            objects[i].position.width = textures[i].width;
            objects[i].position.height = textures[i].height;

            TotalWidth += textures[i].width;

            if(textures[i].height > BiggestHeight){
                BiggestHeight = textures[i].height;
            }


            //LoadObject(i);

            objects[i].Largo_en_X = Allobjects[i].Largo_en_X;
            objects[i].Largo_en_Y = Allobjects[i].Largo_en_Y;

            objects[i].Colision_en_X = Allobjects[i].Colision_en_X;
            objects[i].Colision_en_Y = Allobjects[i].Colision_en_Y;

            objects[i].Img_off_X = Allobjects[i].Img_off_X;
            objects[i].Img_off_Y = Allobjects[i].Img_off_Y;
        }


        RenderTexture2D target = LoadRenderTexture(TotalWidth,BiggestHeight);

        //------------------------------------------------
        BeginTextureMode(target);
            for(int i = 0; i < AmountOfObjects; i++ ){
                DrawTexturePro(textures[i],(Rectangle){0,0,textures[i].width,textures[i].height},(Rectangle){x,0,textures[i].width,textures[i].height},(Vector2){0,0},0,WHITE);
                x += textures[i].width;
            }
        EndTextureMode();
        //------------------------------------------------


        //Crear la imagen para guardar y guardarla
        //------------------------------------------------
        SaveImage = LoadImageFromTexture(target.texture);

        ImageFlipVertical(&SaveImage);

        ExportImage(SaveImage,"Objetos/Images/All.png");
        //------------------------------------------------

    //-------------------------------------------------------------------------------

    //Save the tile values and the image position / size

    FILE* fp = fopen("Objetos/All.obt","wb");

    putw(AmountOfObjects,fp);

    for(int i = 0; i < AmountOfObjects; i++ ){

        putw(objects[i].Largo_en_X,fp);
        putw(objects[i].Largo_en_Y,fp);

        putw(objects[i].Colision_en_X,fp);
        putw(objects[i].Colision_en_Y,fp);

        putw(objects[i].Img_off_X,fp);
        putw(objects[i].Img_off_Y,fp);


        putw(objects[i].position.x,fp);
        putw(objects[i].position.y,fp);
        putw(objects[i].position.width,fp);
        putw(objects[i].position.height,fp);


    }

    fclose(fp);



}

/*
void LoadObject(int object){

    FILE *fp;

    unsigned char* name = Return_Object_Name(object);

    fp = fopen(name,"rb");

    Largo_en_XValue = getw(fp);
    Largo_en_YValue = getw(fp);

    Colision_en_XValue = getw(fp);
    Colision_en_YValue = getw(fp);

    Img_off_XValue = getw(fp);
    Img_off_YValue = getw(fp);

    fclose(fp);

    free(name);


    name = NULL;

    name = Return_Object_Image_Name(object);

    texture = LoadTexture(name);

}
*/

void Add_number_to_file(int number,FILE *fp){
    #ifdef SAVENUMBERASTEXT
        unsigned char* array = Return_array(number);

        for(int i = 0; i < ReturnNumberOfDigits(number) ;i++){
            putc(array[i],fp);
        }

        putc('\n',fp);

        free(array);
        array = NULL;

    #else
        putw(number,fp);
    #endif

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


int Return_number_of_objects(){

    int Number = 0;


    while(FileExists(Return_Object_Name(Number))){
        Number++;
    }

    return Number;
}


unsigned char* Return_Object_Name (int object){

    unsigned char* name = calloc(45,sizeof(unsigned char));

    strcat(name,"Objetos/obj");

    const int NumberOfDigits = ReturnNumberOfDigits(object);

    unsigned char* array = Return_inverse_array(object);

    for(int e = 0; e <= NumberOfDigits; e++){
       name[e+11] = array[NumberOfDigits - e - 1];
    }

    strcat(name,".obt");

    return name;

}
unsigned char* Return_Object_Image_Name (int object){

    unsigned char* name = calloc(45,sizeof(unsigned char));

    strcat(name,"Objetos/Images/obj");

    const int NumberOfDigits = ReturnNumberOfDigits(object);

    unsigned char* array = Return_inverse_array(object);

    for(int e = 0; e <= NumberOfDigits; e++){
       name[e+18] = array[NumberOfDigits - e - 1];
    }

    strcat(name,".png");

    return name;

}
unsigned char* Return_Object_Icon_Name (int object){

    unsigned char* name = calloc(45,sizeof(unsigned char));

    strcat(name,"Objetos/Icons/obj");

    const int NumberOfDigits = ReturnNumberOfDigits(object);

    unsigned char* array = Return_inverse_array(object);

    for(int e = 0; e <= NumberOfDigits; e++){
       name[e+17] = array[NumberOfDigits - e - 1];
    }

    strcat(name,".png");

    return name;

}


//Appends a new object to the end of the list
void AddObject(Object object){

    AmountOfObjects++;

    Allobjects = realloc(Allobjects,sizeof(Object)*(AmountOfObjects + 1));

    Allobjects[AmountOfObjects] = object;
}

//Removes the chosen object and rearenges the list
void RemoveObject(int object){

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
