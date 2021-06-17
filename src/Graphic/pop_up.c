#include "Graphic.h"
#include "../Test/Test.h"

void pop_up( Game* game, const uint_fast16_t w, const uint_fast16_t h) {
    SDL_Rect back;
    back.x = 0;
    back.y = 0;
    back.w = SIZE_X;
    back.h = SIZE_Y;

    Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 150) != 0, "SDL_SetRenderDrawColor", __FILE__, __LINE__);
    Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_BLEND) != 0, "SDL_SetRenderDrawBlendMode", __FILE__, __LINE__);
    Test( game->window, game->renderer, WARNING, SDL_RenderFillRect(game->renderer, &back) != 0, "SDL_SetRenderFillRect", __FILE__, __LINE__);

    back.w = w;
    back.h = h;
    back.x = (SIZE_X/2) - back.w/2;
    back.y = (SIZE_Y/2) - back.h/2;

    Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, game->background.r, game->background.g, game->background.b, game->background.a) != 0, "SetRenderDrawColor", __FILE__, __LINE__);
    Test( game->window, game->renderer, WARNING, SDL_RenderFillRect(game->renderer, &back) != 0, "RenderFillRect", __FILE__, __LINE__);

    Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, game->color.r, game->color.g, game->color.b, game->color.a) != 0, "SetRenderDrawColor", __FILE__, __LINE__);
    Test( game->window, game->renderer, WARNING, SDL_RenderDrawRect(game->renderer, &back) != 0, "RenderFillRect", __FILE__, __LINE__);

    Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_NONE) != 0, "SDL_SetRenderDrawBlendMode", __FILE__, __LINE__);
}