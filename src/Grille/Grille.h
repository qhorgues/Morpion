#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

#include "../Game/Game.h"

bool grilleVide(int_fast8_t (*grille)[LEN_GRILLE]);
bool grillePlein(int_fast8_t (*grille)[LEN_GRILLE]);
void resetGrille(int_fast8_t (*grille)[LEN_GRILLE]);
void printGrille( Game* game, const uint_fast8_t w);
bool addGrille( Game* game, const uint_fast16_t clickX, const uint_fast16_t clickY);

#endif // !GRILLE_H_INCLUDED