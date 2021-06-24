#include <SDL2/SDL.h>

#include "Graphic.h"
#define STRUCT_COOR
#include "../IA/IA.h"
#include "../constante.h"
#include "../Test/Test.h"
#include "../Game/Game.h"

static int_fast8_t signe(const int_fast32_t n);
static void ligneHorizontale(const Game *game, const int_fast16_t x, const int_fast16_t y, const int_fast16_t w);
static void disque(Game *game, const int_fast16_t cx, const int_fast16_t cy, const int_fast16_t rayon);

void lineWinner(Game *game, const Coor dpt, const Coor arv)
{
	const int_fast8_t cx = signe(arv.x - dpt.x);
	const int_fast8_t cy = signe(arv.y - dpt.y);

	uint_fast16_t x = dpt.x * (SIZE_X / 3) + SIZE_X / 6;
	uint_fast16_t y = dpt.y * (SIZE_X / 3) + SIZE_X / 6 + OF_SET;
	const uint_fast16_t x_arv = arv.x * (SIZE_X / 3) + SIZE_X / 6;
	const uint_fast16_t y_arv = arv.y * (SIZE_X / 3) + SIZE_X / 6 + OF_SET;

	Test(game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, 77, 218, 225, 50) != 0, "SDL_SetRenderDrawColor", __FILE__, __LINE__);
	Test(game->window, game->renderer, WARNING, SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_BLEND) != 0, "SDL_SetRenderDrawBlendMode", __FILE__, __LINE__);

	while (x != x_arv || y != y_arv)
	{
		disque(game, x, y, 5);
		x += cx;
		y += cy;
		SDL_RenderPresent(game->renderer);
		SDL_Delay(1);
	}

	Test(game->window, game->renderer, WARNING, SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_NONE) != 0, "SDL_SetRenderDrawBlendMode", __FILE__, __LINE__);
	SDL_Delay(500);
}

static void disque(Game *game, const int_fast16_t cx, const int_fast16_t cy, const int_fast16_t rayon)
{
	int_fast16_t d, y, x;

	d = 3 - (2 * rayon);
	x = 0;
	y = rayon;

	while (y >= x)
	{
		ligneHorizontale(game, cx - x, cy - y, 2 * x + 1);
		ligneHorizontale(game, cx - x, cy + y, 2 * x + 1);
		ligneHorizontale(game, cx - y, cy - x, 2 * y + 1);
		ligneHorizontale(game, cx - y, cy + x, 2 * y + 1);

		if (d < 0)
			d = d + (4 * x) + 6;
		else
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}

		x++;
	}
}

static void ligneHorizontale(const Game *game, const int_fast16_t x, const int_fast16_t y, const int_fast16_t w)
{
	SDL_Rect r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = 1;

	Test(game->window, game->renderer, WARNING, SDL_RenderFillRect(game->renderer, &r) != 0, "SDL_RenderFillRect", __FILE__, __LINE__);
}

static int_fast8_t signe(const int_fast32_t n)
{
	if (n < 0)
	{
		return -1;
	}
	return n > 0;
}