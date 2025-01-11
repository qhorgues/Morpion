#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

#include "../Game/Game.h"

bool grilleVide(int (*grille)[LEN_GRILLE]);
bool grillePlein(int (*grille)[LEN_GRILLE]);
void resetGrille(int (*grille)[LEN_GRILLE]);
void printGrille( Game* game, const int w);
bool addGrille( Game* game, const int clickX, const int clickY);

#endif // !GRILLE_H_INCLUDED