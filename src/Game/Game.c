#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#define FUNC_IMAGE
#define FUNC_GAME
#include "Game.h"
#include "../Test/Test.h"
#include "../Divers/Divers.h"
#include "../SetingFile/SetingFile.h"
#include "../Grille/Grille.h"
#include "../IA/IA.h"
#include "../Graphic/Graphic.h"
#include "../Button/Button.h"

/**
 * \brief Initialisation de la structure du jeu
 * 
 * \return Une structure Game
 */
Game initGame(const char * PATH_SaveFolder) {
    Game game;
    game.window = SDL_CreateWindow("Morpion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SIZE_X, SIZE_Y, SDL_WINDOW_SHOWN); // Creation de la fenetre
    Test( NULL, NULL, ERROR, game.window == NULL, "SDL_CreateWindow", __FILE__, __LINE__ - 1);

    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_SOFTWARE); // Creation du rendue
    Test(game.window, NULL, ERROR, game.renderer == NULL, "SDL_CreateRenderer", __FILE__, __LINE__ - 1);

    Test(game.window, game.renderer, ERROR, IMG_Init(IMG_INIT_PNG) == 0, "IMG_Init", __FILE__, __LINE__);
    
    InitPlayer(&game, &game.player1, 1, "Joueur 1", 0);
    InitPlayer(&game, &game.player2, -1, "Joueur 2", 0);

    game.playerActif = 1;
    game.startPlayer = 1;

    game.Niveau = 2;
    
    game.color = rgba_to_color( 0, 0, 0, SDL_ALPHA_OPAQUE);
    game.background = rgba_to_color( 255, 255, 255, SDL_ALPHA_OPAQUE);
    loadSeting(game.window, game.renderer, strcat( strdup(PATH_SaveFolder), "\\Seting.bin"), &game.color, &game.background);
 
    game.boolMenu = false;
    game.boolMenu = set_tabBool(game.boolMenu, MENU, true);
    game.boolMenu = set_tabBool(game.boolMenu, CHANGE_COLOR, true);

    game.NivAuto = false;

    for (int_fast32_t i = 0; i < N_BUTTON; i++) {
        game.tabButton[i] = NULL;
    }
    
    resetGrille(game.grille);
    
    update(&game);
    return game;
}

/**
 * \brief Detruit la structure Game
 * \param game 
 */
void freeGame( Game* game, const char * PATH_SaveFolder) {
    saveSeting(game->window, game->renderer, strcat( strdup(PATH_SaveFolder), "\\Seting.bin"), game->color, game->background);

    freePlayer(&game->player1);
    freePlayer(&game->player2);
    
    for(int_fast32_t i = 0; i < N_BUTTON; i++) {
        if (game->tabButton[i] != NULL) {
            freeButton(game->window, game->renderer, game->tabButton[i]);
            free(game->tabButton[i]);
            game->tabButton[i] = NULL;
        }
    }
    
    SDL_DestroyRenderer(game->renderer);
    game->renderer = NULL;
    SDL_DestroyWindow(game->window);
    game->window = NULL;
}

/**
 * @brief actualise l'ecran et ccordonne toutes les fonction updates
 * 
 * @param game 
 */
void update( Game* game) {
    Test( game->window, game->renderer, ERROR, SDL_RenderClear(game->renderer), "SDL_RenderClear", __FILE__, __LINE__);
    if (get_tabBool(game->boolMenu, IN_GAME)) {
        update_in_game(game);
    } else if (get_tabBool(game->boolMenu, MENU_END)) {
        update_in_game(game);
        update_end_game(game);
    } else if (get_tabBool(game->boolMenu, MENU)) {
        update_in_menu(game);
    } else if (get_tabBool(game->boolMenu, MENU_LEVEL)) {
        update_in_menu_level(game);
    }
    SDL_RenderPresent(game->renderer);
}

bool getClick( Game* game, const uint_fast16_t clickX, const uint_fast16_t clickY) {
    if (get_tabBool(game->boolMenu, IN_GAME)) {
        addGrille( game, clickX, clickY);
    } else if (get_tabBool(game->boolMenu, MENU_END)) {
        if (clickButton(game->tabButton[OUI], clickX, clickY)) {
            restartGame( game);
            restartGameIA( game);
        } else if (clickButton(game->tabButton[NON], clickX, clickY)) {
            game->NivAuto = false;
            game->boolMenu = set_tabBool(game->boolMenu, MENU_END, false);
            game->boolMenu = set_tabBool(game->boolMenu, MENU, true);
            freeButton(game->window, game->renderer, game->tabButton[OUI]);
            free(game->tabButton[OUI]);
            game->tabButton[OUI] = NULL;
            freeButton(game->window, game->renderer, game->tabButton[NON]);
            free(game->tabButton[NON]);
            game->tabButton[NON] = NULL;
            update(game);
        }
    } else if (get_tabBool(game->boolMenu, MENU)) {
        if (clickButton(game->tabButton[BUTTON_MULTIPLAYER], clickX, clickY)) {
            clickButtonMenu( game, false);
        } else if (clickButton(game->tabButton[BUTTON_SOLO], clickX, clickY)) {
            clickButtonMenu( game, true);
        } else if (clickButton(game->tabButton[BUTTON_EXIT], clickX, clickY)) {
            return true;
        }
    } else if (get_tabBool(game->boolMenu, MENU_LEVEL)) {
        clickLevel(game, clickX, clickY);
    }
    return false;
}