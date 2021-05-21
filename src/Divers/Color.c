#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define FUNC_GAME
#include "Divers.h"
#include "../Game/Game.h"

/**
 * \brief Inverse la couleur du background avec la couleur de l'ecriture
 * 
 * \param game Un pointeur sur la structure du jeu
 */
void changeColor( Game* game) {
    if (get_tabBool(game->boolMenu, CHANGE_COLOR)) {
        SDL_Color T = game->background;
        game->background = game->color;
        game->color = T;
        update(game);
        game->boolMenu = set_tabBool(game->boolMenu, CHANGE_COLOR, false);
    }
    
}

/**
 * \brief Convertie 4 nombre en structure SDL_Color
 * 
 * \param r Un entier de 0 a 255 pour le rouge
 * \param g Un entier de 0 a 255 pour le vert
 * \param b Un entier de 0 a 255 pour le bleu
 * \param a Un entier de 0 a 255 pour la transparence
 * \return SDL_Color 
 */
SDL_Color rgba_to_color( const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) {
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}
