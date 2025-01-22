#include "Headers/Math.h"

//Esta funcion devuelve un numero aleatorio entre Min y Max
int RandomNum(const int Min, const int Max){
    if(Min < Max){
        int RandomNum;
        RandomNum = rand()%(Max-Min)+Min;
        return RandomNum;
    }
    else{
        return Max;
    }
}

//Esta funcion devuelve el numero mas pequeño
int Smallest(int a, int b){

    if(a > b){

        return b;

    }

    return a;

}

//Esta funcion devuelve el numero mas grande
int Biggest(int a, int b){

    if(a < b){

        return b;

    }

    return a;

}
