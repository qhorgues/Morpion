#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include "../constante.h"
#define FUNC_GAME
#include "../Game/Game.h"

typedef struct Coor {
    uint_fast8_t x;
    uint_fast8_t y;
} Coor;

#ifndef STRUCT_COOR
int_fast32_t IA( Game* game, const int_fast8_t joueurT, const uint_fast8_t Profondeur, Coor* bestCoup);
int_fast32_t f_score(int_fast8_t (*grille)[LEN_GRILLE] , const char ID, Coor * dpt, Coor * arv);
bool testWin(Game* game);
void ouverture(Coor* coupOpen);
#endif

#endif