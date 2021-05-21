#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include "../Game/Game.h"
#define STRUCT_COOR
#include "../IA/IA.h"

void update_in_game( Game* game);

void pop_up( Game* game, const unsigned short w, const unsigned short h);
void update_end_game( Game* game);

void lineWinner(Game* game, const Coor dpt, const Coor arv);

void restartGame( Game* game);
void restartGameIA( Game* game);

void update_in_menu( Game* game);

void update_in_menu_level( Game* game);

void clickButtonMenu(Game* game, const bool Solo);
void clickLevel(Game* game, const unsigned short clickX, const unsigned short clickY);

#endif