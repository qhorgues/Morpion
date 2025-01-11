#include <stdio.h>
#define FUNC_IMAGE
#define FUNC_GAME
#define TAB_BOOL
#include "../IA/IA.h"
#include "../Game/Game.h"
#include "../Grille/Grille.h"
#include "Graphic.h"
#include "../constante.h"
#include "../Text/Text.h"
#include "../Test/Test.h"
#include "../Button/Button.h"

void update_end_game( Game* game) {
    pop_up(game, (int)(SIZE_X/1.3), (int)(SIZE_Y/2));

    Test(game->window, game->renderer, FATAL_ERROR, IMG_Init(IMG_INIT_PNG) == 0, "IMG_Init", __FILE__, __LINE__);
    Test(game->window, game->renderer, FATAL_ERROR, TTF_Init() != 0, "TTF_Init", __FILE__, __LINE__);

    TTF_Font* calibri = TTF_OpenFont("assets/calibrib.ttf", OF_SET/2);
    Test(game->window, game->renderer, ERROR, calibri == NULL, "TTF_OpenFont", __FILE__, __LINE__-1);

    if (game->modeFinish != 0) {
        IMG win;
        Text textWin;
        if (game->modeFinish == 1 || (game->modeFinish == -1 && !get_tabBool(game->boolMenu, SOLO) ) ) {
            loadImage(game->window, game->renderer, "assets/Victory.png", &win);
            char nameWinnner[24];

            if (game->modeFinish == 1) {
                sprintf( nameWinnner, u8"%s à gagné(e)", game->player1.Name);
            } else {
                sprintf( nameWinnner, u8"%s à gagné(e)", game->player2.Name);
            }
            loadText(game->window, game->renderer, nameWinnner, calibri, &textWin, game->color, SHADED, &game->background);
            printText(game->window, game->renderer, &textWin, SIZE_X/2 - textWin.RectText->w/2, SIZE_Y/2 - SIZE_Y/4 + win.RectImage->h + 10);
        } else {
            loadImage(game->window, game->renderer, "assets/Bad.png", &win);
            loadText(game->window, game->renderer, "Vous avez perdu", calibri, &textWin, game->color, SHADED, &game->background);
            printText(game->window, game->renderer, &textWin, SIZE_X/2 - textWin.RectText->w/2, SIZE_Y/2 - SIZE_Y/4 + win.RectImage->h + 10);
        }
        printImage(game->window, game->renderer, &win, SIZE_X/2 - win.RectImage->w/2, SIZE_Y/2 - SIZE_Y/4 + 5, AUTO, AUTO);

        freeImage(game->window, game->renderer, &win);
        freeText(game->window, game->renderer, &textWin);
    }
    else if (game->modeFinish == 0) {
        IMG null;
        loadImage(game->window, game->renderer, "assets/XO.png", &null);
        printImage(game->window, game->renderer, &null, SIZE_X/2 - null.RectImage->w/2, SIZE_Y/2 - SIZE_Y/4 + 5, AUTO, AUTO);

        Text textNull;
        loadText(game->window, game->renderer, "Match null", calibri, &textNull, game->color, SHADED, &game->background);
        printText(game->window, game->renderer, &textNull, SIZE_X/2 - textNull.RectText->w/2, null.RectImage->y + null.RectImage->h + 5);
        
        freeText(game->window, game->renderer, &textNull);
        freeImage( game->window, game->renderer, &null);
    }
    Text restart;
    loadText( game->window, game->renderer, "Recommencer ? ", calibri, &restart, game->color, SHADED, &game->background);
    printText( game->window, game->renderer, &restart, SIZE_X/2 - restart.RectText->w/2+10, SIZE_Y/2 +15);
    freeText( game->window, game->renderer, &restart);

    const SDL_Color white = {255, 255, 255, SDL_ALPHA_OPAQUE};
    const SDL_Color blue = BLUE;

    game->tabButton[OUI] = allocButtonText(game->window, game->renderer, (int)((SIZE_X/1.3) /2 -10), 60, "OUI", calibri, white, blue);
    printButton(game->window, game->renderer, game->tabButton[OUI], SIZE_X/2 - game->tabButton[OUI]->rectButton.w -5, SIZE_Y/2 + SIZE_Y/4 - game->tabButton[OUI]->rectButton.h -5 );

    game->tabButton[NON] = allocButtonText(game->window, game->renderer, (int)((SIZE_X/1.3)/2  -10), 60, "NON", calibri, white, blue);
    printButton(game->window, game->renderer, game->tabButton[NON], (int)(SIZE_X/2 + ((SIZE_X/1.3)/2) -5 - game->tabButton[NON]->rectButton.w), SIZE_Y/2 + SIZE_Y/4 - game->tabButton[NON]->rectButton.h -5 );

    TTF_CloseFont(calibri);

    IMG_Quit();
    TTF_Quit();
}

void restartGame( Game* game) {
    resetGrille( game->grille);
    game->startPlayer *= -1;
    game->playerActif = game->startPlayer;
    game->boolMenu = set_tabBool(game->boolMenu, MENU_END, false);
    game->boolMenu = set_tabBool(game->boolMenu, IN_GAME, true);
    freeButton(game->window, game->renderer, game->tabButton[OUI]);
    free(game->tabButton[OUI]);
    game->tabButton[OUI] = NULL;
    freeButton(game->window, game->renderer, game->tabButton[NON]);
    free(game->tabButton[NON]);
    game->tabButton[NON] = NULL;
    update(game);
}

void restartGameIA( Game* game) {
    if (game->startPlayer == -1 && get_tabBool(game->boolMenu, SOLO)) {
        Coor bestCoup;
        IMG Symbole;
        ouverture(&bestCoup);
        game->grille[bestCoup.y][bestCoup.x] = game->playerActif;
        Test(game->window, game->renderer, FATAL_ERROR, IMG_Init(IMG_INIT_PNG) == 0, "IMG_Init", __FILE__, __LINE__);
        loadImage(game->window, game->renderer, "assets/Rond.png", &Symbole);
        IMG_Quit();
        printImage(game->window, game->renderer, &Symbole, bestCoup.x * (SIZE_X / 3) + ((SIZE_X / 3 - SIZE_X / 4) / 2),
                bestCoup.y * (SIZE_X / 3) + OF_SET + ((SIZE_X / 3 - SIZE_X / 4) / 2), AUTO, AUTO);
        freeImage(game->window, game->renderer, &Symbole);
        SDL_RenderPresent(game->renderer);
        testWin(game);
    }
}