#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include "../Game/Game.h"
#define STRUCT_COOR
#include "../IA/IA.h"

void update_in_game( Game* game);

void pop_up( Game* game, const uint_fast16_t w, const uint_fast16_t h);
void update_end_game( Game* game);

void lineWinner(Game* game, const Coor dpt, const Coor arv);

void restartGame( Game* game);
void restartGameIA( Game* game);

void update_in_menu( Game* game);

void update_in_menu_level( Game* game);

void clickButtonMenu(Game* game, const bool Solo);
void clickLevel(Game* game, const uint_fast16_t clickX, const uint_fast16_t clickY);

#endif