#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include "../constante.h"
#define FUNC_GAME
#include "../Game/Game.h"

typedef struct Coor {
    int x;
    int y;
} Coor;

#ifndef STRUCT_COOR
int IA( Game* game, const int joueurT, const int Profondeur, Coor* bestCoup);
int f_score(int (*grille)[LEN_GRILLE] , const int ID, Coor * dpt, Coor * arv);
bool testWin(Game* game);
void ouverture(Coor* coupOpen);
#endif

#endif