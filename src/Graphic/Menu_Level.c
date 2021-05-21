#define FUNC_GAME
#include "Graphic.h"
#include "../Grille/Grille.h"
#include "../Text/Text.h"
#include "../Test/Test.h"

void update_in_menu_level( Game* game) {

    for(int i = 0; i < N_BUTTON; i++) {
        if (game->tabButton[i] != NULL) {
            freeButton(game->window, game->renderer, game->tabButton[i]);
            free(game->tabButton[i]);
            game->tabButton[i] = NULL;
        }
    }

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

    TTF_Font* calibri = TTF_OpenFont("assets/Fonts/calibrib.ttf", 30);
    Test(game->window, game->renderer, ERROR, calibri == NULL, "TTF_OpenFont", __FILE__, __LINE__-1);

    const SDL_Color white = {255, 255, 255, SDL_ALPHA_OPAQUE};
    const SDL_Color blue = BLUE;

    game->tabButton[BUTTON_EASY] = allocButtonText( game->window, game->renderer, SIZE_X/1.3, SIZE_Y/8, "FACILE", calibri, white, blue);
    printButton( game->window, game->renderer, game->tabButton[BUTTON_EASY], SIZE_X/2 - game->tabButton[BUTTON_EASY]->rectButton.w/2, SIZE_Y/4);

    game->tabButton[BUTTON_MEDIUM] = allocButtonText( game->window, game->renderer, SIZE_X/1.3, SIZE_Y/8, "MOYEN", calibri, white, blue);
    printButton( game->window, game->renderer, game->tabButton[BUTTON_MEDIUM], SIZE_X/2 - game->tabButton[BUTTON_MEDIUM]->rectButton.w/2, game->tabButton[BUTTON_EASY]->rectButton.y
     + game->tabButton[BUTTON_EASY]->rectButton.h + 20);

    game->tabButton[BUTTON_HARD] = allocButtonText( game->window, game->renderer, SIZE_X/1.3, SIZE_Y/8, "DIFFICILE", calibri, white, blue);
    printButton( game->window, game->renderer, game->tabButton[BUTTON_HARD], SIZE_X/2 - game->tabButton[BUTTON_HARD]->rectButton.w/2, game->tabButton[BUTTON_MEDIUM]->rectButton.y
     + game->tabButton[BUTTON_MEDIUM]->rectButton.h + 20);

    game->tabButton[BUTTON_RETURN] = allocButtonText( game->window, game->renderer, SIZE_X/3, SIZE_Y/8, "RETOUR", calibri, white, blue);
    printButton( game->window, game->renderer, game->tabButton[BUTTON_RETURN], game->tabButton[BUTTON_HARD]->rectButton.x, game->tabButton[BUTTON_HARD]->rectButton.y
     + game->tabButton[BUTTON_HARD]->rectButton.h + 20);

    if (!game->NivAuto) {
        game->tabButton[BUTTON_AUTO] = allocButtonText(game->window, game->renderer, SIZE_X/4, SIZE_Y/8, "AUTO", calibri, white, blue);
        printButton(game->window, game->renderer, game->tabButton[BUTTON_AUTO], game->tabButton[BUTTON_RETURN]->rectButton.x + game->tabButton[BUTTON_RETURN]->rectButton.w + 10,
        game->tabButton[BUTTON_HARD]->rectButton.y + game->tabButton[BUTTON_HARD]->rectButton.h + 20);
    } else {
        const SDL_Color green = { 0, 157, 12, SDL_ALPHA_OPAQUE};
        game->tabButton[BUTTON_AUTO] = allocButtonText(game->window, game->renderer, SIZE_X/4, SIZE_Y/8, "AUTO", calibri, white, green);
        printButton(game->window, game->renderer, game->tabButton[BUTTON_AUTO], game->tabButton[BUTTON_RETURN]->rectButton.x + game->tabButton[BUTTON_RETURN]->rectButton.w + 10,
        game->tabButton[BUTTON_HARD]->rectButton.y + game->tabButton[BUTTON_HARD]->rectButton.h + 20);
    }

    TTF_CloseFont(calibri);
    TTF_Quit();
}

void freebuttonLevel(Game* game) {
    freeButton( game->window, game->renderer, game->tabButton[BUTTON_EASY]);
    free(game->tabButton[BUTTON_EASY]);
    game->tabButton[BUTTON_EASY] = NULL;
    freeButton( game->window, game->renderer, game->tabButton[BUTTON_MEDIUM]);
    free(game->tabButton[BUTTON_MEDIUM]);
    game->tabButton[BUTTON_MEDIUM] = NULL;
    freeButton( game->window, game->renderer, game->tabButton[BUTTON_HARD]);
    free(game->tabButton[BUTTON_HARD]);
    game->tabButton[BUTTON_HARD] = NULL;
    freeButton( game->window, game->renderer, game->tabButton[BUTTON_RETURN]);
    free(game->tabButton[BUTTON_RETURN]);
    game->tabButton[BUTTON_RETURN] = NULL;
    freeButton( game->window, game->renderer, game->tabButton[BUTTON_AUTO]);
    free(game->tabButton[BUTTON_AUTO]);
    game->tabButton[BUTTON_AUTO] = NULL;
}

void clickButtonLevel(Game* game) {
    freebuttonLevel(game);
    game->boolMenu = set_tabBool(game->boolMenu, MENU_LEVEL, false);
    game->boolMenu = set_tabBool(game->boolMenu, IN_GAME, true);
    resetGrille(game->grille);
    game->player1.score = 0;
    game->player2.score = 0;
    game->startPlayer = 1;
    game->playerActif = 1;
    update( game);
}

void clickLevel(Game* game, const unsigned short clickX, const unsigned short clickY) {
    if (clickButton(game->tabButton[BUTTON_EASY], clickX, clickY)) {
        game->Niveau = 2;
        game->startNiveau = 2;
        clickButtonLevel(game);
    } else if (clickButton(game->tabButton[BUTTON_MEDIUM], clickX, clickY)) {
        game->Niveau = 4;
        game->startNiveau = 4;
        clickButtonLevel(game);
    } else if (clickButton(game->tabButton[BUTTON_HARD], clickX, clickY)) {
        game->Niveau = 6;
        game->startNiveau = 6;
        clickButtonLevel(game);
    } else if (clickButton(game->tabButton[BUTTON_RETURN], clickX, clickY)) {
        freebuttonLevel(game);
        game->NivAuto = false;
        game->boolMenu = set_tabBool(game->boolMenu, MENU_LEVEL, false);
        game->boolMenu = set_tabBool(game->boolMenu, MENU, true);
        update( game);
    } else if (clickButton(game->tabButton[BUTTON_AUTO], clickX, clickY)) {
        Test(game->window, game->renderer, FATAL_ERROR, TTF_Init() != 0, "TTF_Init", __FILE__, __LINE__);

        TTF_Font* calibri = TTF_OpenFont("assets/Fonts/calibrib.ttf", OF_SET/2);
        Test(game->window, game->renderer, ERROR, calibri == NULL, "TTF_OpenFont", __FILE__, __LINE__-1);

        freeButton( game->window, game->renderer, game->tabButton[BUTTON_AUTO]);
        free(game->tabButton[BUTTON_AUTO]);
        game->tabButton[BUTTON_AUTO] = NULL;

        const SDL_Color white = { 255, 255, 255, SDL_ALPHA_OPAQUE};
        if (game->NivAuto) {
            const SDL_Color blue = BLUE;
            game->tabButton[BUTTON_AUTO] = allocButtonText(game->window, game->renderer, SIZE_X/4, SIZE_Y/8, "AUTO", calibri, white, blue);
            printButton(game->window, game->renderer, game->tabButton[BUTTON_AUTO], game->tabButton[BUTTON_RETURN]->rectButton.x + game->tabButton[BUTTON_RETURN]->rectButton.w + 10,
            game->tabButton[BUTTON_HARD]->rectButton.y + game->tabButton[BUTTON_HARD]->rectButton.h + 20);
            game->NivAuto = false;
        } else {
            const SDL_Color green = { 0, 157, 12, SDL_ALPHA_OPAQUE};
            game->tabButton[BUTTON_AUTO] = allocButtonText(game->window, game->renderer, SIZE_X/4, SIZE_Y/8, "AUTO", calibri, white, green);
            printButton(game->window, game->renderer, game->tabButton[BUTTON_AUTO], game->tabButton[BUTTON_RETURN]->rectButton.x + game->tabButton[BUTTON_RETURN]->rectButton.w + 10,
            game->tabButton[BUTTON_HARD]->rectButton.y + game->tabButton[BUTTON_HARD]->rectButton.h + 20);
            game->NivAuto = true;
        }
        SDL_RenderPresent(game->renderer);
        TTF_CloseFont(calibri);
        TTF_Quit();
        
    }
}