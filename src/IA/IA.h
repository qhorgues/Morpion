#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include "../constante.h"
#define FUNC_GAME
#include "../Game/Game.h"

typedef struct Coor {
    unsigned char x;
    unsigned char y;
} Coor;

#ifndef STRUCT_COOR
int IA( Game* game, const signed char joueurT, const unsigned char Profondeur, Coor* bestCoup);
int f_score(signed char (*grille)[LEN_GRILLE] , const char ID, Coor * dpt, Coor * arv);
bool testWin(Game* game);
void ouverture(Coor* coupOpen);
#endif

#endif