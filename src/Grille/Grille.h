#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

#include "../Game/Game.h"

bool grilleVide(signed char (*grille)[LEN_GRILLE]);
bool grillePlein(signed char (*grille)[LEN_GRILLE]);
void resetGrille(signed char (*grille)[LEN_GRILLE]);
void printGrille( Game* game, const unsigned char w);
bool addGrille( Game* game, const unsigned short clickX, const unsigned short clickY);

#endif // !GRILLE_H_INCLUDED