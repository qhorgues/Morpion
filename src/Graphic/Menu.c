#define FUNC_GAME
#include "Graphic.h"
#include "../Grille/Grille.h"
#include "../Text/Text.h"
#include "../Test/Test.h"

void update_in_menu( Game* game) {
    Test(game->window, game->renderer, WARNING,
         SDL_SetRenderDrawColor(game->renderer, game->background.r, game->background.g, game->background.b, game->background.a),
         "SDL_SetRenderDrawColor", __FILE__, __LINE__ - 1);

    Test(game->window, game->renderer, WARNING, SDL_RenderClear(game->renderer) != 0, "SDL_RenderClear", __FILE__, __LINE__);

    Test(game->window, game->renderer, FATAL_ERROR, TTF_Init() != 0, "TTF_Init", __FILE__, __LINE__);

    TTF_Font* Imprisha = TTF_OpenFont("assets/Fonts/IMPRISHA.TTF", 70);
    Test(game->window, game->renderer, ERROR, Imprisha == NULL, "TTF_OpenFont", __FILE__, __LINE__-1);

    Text Titre;
    loadText( game->window, game->renderer, "Morpion", Imprisha, &Titre, game->color, SHADED, &game->background);
    printText(game->window, game->renderer, &Titre, SIZE_X/2 - Titre.RectText->w/2 , 10);
    freeText(game->window, game->renderer, &Titre);
    TTF_CloseFont(Imprisha);

    Imprisha = TTF_OpenFont("assets/Fonts/IMPRISHA.ttf", 20);
    Test(game->window, game->renderer, ERROR, Imprisha == NULL, "TTF_OpenFont", __FILE__, __LINE__-1);

    Text Dev;
    loadText( game->window, game->renderer, "by Quentin Horgues", Imprisha, &Dev, game->color, SHADED, &game->background);
    printText( game->window, game->renderer, &Dev, 5, SIZE_Y - Dev.RectText->h - 5);
    freeText(game->window, game->renderer, &Dev);

    TTF_CloseFont(Imprisha);

    TTF_Font* calibri = TTF_OpenFont("assets/Fonts/calibrib.ttf", 30);
    Test(game->window, game->renderer, ERROR, calibri == NULL, "TTF_OpenFont", __FILE__, __LINE__-1);

    SDL_Color white = {255, 255, 255, SDL_ALPHA_OPAQUE};
    SDL_Color blue = BLUE;

    game->tabButton[BUTTON_SOLO] = allocButtonText( game->window, game->renderer, SIZE_X/1.3, SIZE_Y/8, "SOLO", calibri, white, blue);
    printButton( game->window, game->renderer, game->tabButton[BUTTON_SOLO], SIZE_X/2 - game->tabButton[BUTTON_SOLO]->rectButton.w/2, SIZE_Y/3);

    game->tabButton[BUTTON_MULTIPLAYER] = allocButtonText( game->window, game->renderer, SIZE_X/1.3, SIZE_Y/8, "MULTI-JOUEURS", calibri, white, blue);
    printButton( game->window, game->renderer, game->tabButton[BUTTON_MULTIPLAYER], SIZE_X/2 - game->tabButton[BUTTON_MULTIPLAYER]->rectButton.w/2, game->tabButton[BUTTON_SOLO]->rectButton.y
     + game->tabButton[BUTTON_SOLO]->rectButton.h + 20);

    game->tabButton[BUTTON_EXIT] = allocButtonText( game->window, game->renderer, SIZE_X/1.3, SIZE_Y/8, "QUITTER", calibri, white, blue);
    printButton( game->window, game->renderer, game->tabButton[BUTTON_EXIT], SIZE_X/2 - game->tabButton[BUTTON_EXIT]->rectButton.w/2, game->tabButton[BUTTON_MULTIPLAYER]->rectButton.y
     + game->tabButton[BUTTON_MULTIPLAYER]->rectButton.h + 20);


    TTF_CloseFont(calibri);
    TTF_Quit();
}

void clickButtonMenu(Game* game, const bool Solo) {
    freeButton( game->window, game->renderer, game->tabButton[BUTTON_SOLO]);
    free(game->tabButton[BUTTON_SOLO]);
    game->tabButton[BUTTON_SOLO] = NULL;
    freeButton( game->window, game->renderer, game->tabButton[BUTTON_MULTIPLAYER]);
    free(game->tabButton[BUTTON_MULTIPLAYER]);
    game->tabButton[BUTTON_MULTIPLAYER] = NULL;
    freeButton( game->window, game->renderer, game->tabButton[BUTTON_EXIT]);
    free(game->tabButton[BUTTON_EXIT]);
    game->tabButton[BUTTON_EXIT] = NULL;

    game->boolMenu = set_tabBool(game->boolMenu, SOLO, Solo);
    game->boolMenu = set_tabBool(game->boolMenu, MENU, false);
    if (Solo) {
        game->boolMenu = set_tabBool(game->boolMenu, MENU_LEVEL, true);
        changeName(game, &game->player2, "IA");
    } else {
        game->boolMenu = set_tabBool(game->boolMenu, IN_GAME, true);
        changeName(game, &game->player2, "Joueur 2");
    }
    resetGrille(game->grille);
    game->player1.score = 0;
    game->player2.score = 0;
    game->startPlayer = 1;
    game->playerActif = 1;

    update( game);
}