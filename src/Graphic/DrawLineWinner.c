#include <SDl2/SDL.h>

#include "Graphic.h"
#define STRUCT_COOR
#include "../IA/IA.h"
#include "../constante.h"
#include "../Test/Test.h"
#include "../Game/Game.h"

signed char signe(const int n);
void ligneHorizontale(const Game* game, const short x, const short y, const short w);
void disque(Game* game, const short cx, const short cy, const short rayon);


void lineWinner(Game* game, const Coor dpt, const Coor arv) {
    const signed char cx = signe(arv.x - dpt.x);
    const signed char cy = signe(arv.y - dpt.y);
	
    unsigned short x = dpt.x* (SIZE_X/3) + SIZE_X/6;
    unsigned short y = dpt.y* (SIZE_X/3) + SIZE_X/6 + OF_SET;
    const unsigned short x_arv = arv.x* (SIZE_X/3) + SIZE_X/6;
    const unsigned short y_arv = arv.y* (SIZE_X/3) + SIZE_X/6 + OF_SET;

    Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, 77, 218, 225, 50) != 0, "SDL_SetRenderDrawColor", __FILE__, __LINE__);
    Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_BLEND) != 0, "SDL_SetRenderDrawBlendMode", __FILE__, __LINE__);

    while (x != x_arv || y != y_arv) {
        disque( game, x, y, 5);
        x += cx;
        y += cy;
        SDL_RenderPresent(game->renderer);
        SDL_Delay(1);
    }

    Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_NONE) != 0, "SDL_SetRenderDrawBlendMode", __FILE__, __LINE__);
    SDL_Delay(500);
}


void disque(Game* game, const short cx, const short cy, const short rayon) {
  short d, y, x;
 
  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;
 
  while (y >= x) {
    ligneHorizontale(game, cx - x, cy - y, 2 * x + 1);
    ligneHorizontale(game, cx - x, cy + y, 2 * x + 1);
    ligneHorizontale(game, cx - y, cy - x, 2 * y + 1);
    ligneHorizontale(game, cx - y, cy + x, 2 * y + 1);
 
    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }
 
    x++;
  }
}

void ligneHorizontale(const Game* game, const short x, const short y, const short w) {
  SDL_Rect r;
 
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = 1;
 
  Test( game->window, game->renderer, WARNING, SDL_RenderFillRect( game->renderer, &r) != 0, "SDL_RenderFillRect", __FILE__, __LINE__);
}

signed char signe(const int n) {
    if (n < 0) {
        return -1;
    }
    return n > 0;
}