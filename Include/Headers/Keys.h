#ifndef KeyHeaderIncluded
#define KeyHeaderIncluded


typedef struct Key{

bool Down;
bool IsPressed;
bool IsReleased;

bool IsPressedHelper;

}Key;


struct Key AllKeys[322]; // KEYS BUFFER


#endif
