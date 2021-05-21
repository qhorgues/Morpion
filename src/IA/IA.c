#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define TAB_BOOL
#include "IA.h"
#include "../bool/bool.h"
#include "../Graphic/Graphic.h"
#include "../Game/Game.h"
#include "../Grille/Grille.h"
#include "../constante.h"
#include "../Test/Test.h"

int IA(Game *game, const signed char joueurT, const unsigned char Profondeur, Coor *bestCoup)
{
    Coor *tabBestCoup = NULL;
    unsigned char size_tabBestCoup = 0;
    short score = 0;
    short scoreT = 0;
    Coor firstCaseDispo = {10, 10};

    for (unsigned char i = 0; i < LEN_GRILLE; i++)
    {
        for (unsigned char j = 0; j < LEN_GRILLE; j++)
        {
            if (game->grille[i][j] == 0)
            {
                if (firstCaseDispo.x == 10)
                {
                    firstCaseDispo.x = j;
                    firstCaseDispo.y = i;
                }

                game->grille[i][j] = joueurT;
                scoreT = f_score( game->grille, joueurT, NULL, NULL);
                if (scoreT > 80) {
                    scoreT *= (game->Niveau - Profondeur+1);
                }
                if (Profondeur < game->Niveau && scoreT < 80)
                {
                    scoreT -= IA(game, joueurT * -1, Profondeur + 1, NULL);
                }

                if (scoreT > score || (i == firstCaseDispo.y && j == firstCaseDispo.x))
                {
                    if (Profondeur == 1)
                    {
                        size_tabBestCoup = 1;
                        if (tabBestCoup != NULL)
                        {
                            free(tabBestCoup);
                        }
                        tabBestCoup = malloc(sizeof(Coor));
                        tabBestCoup->x = j;
                        tabBestCoup->y = i;
                    }
                    score = scoreT;
                }
                else if (scoreT == score)
                {
                    if (Profondeur == 1)
                    {
                        size_tabBestCoup++;
                        tabBestCoup = realloc(tabBestCoup, size_tabBestCoup * sizeof(Coor));
                        tabBestCoup[size_tabBestCoup - 1].x = j;
                        tabBestCoup[size_tabBestCoup - 1].y = i;
                    }
                }
                scoreT = 0;
                game->grille[i][j] = 0;
            }
        }
    }
    if (Profondeur == 1)
    {
        srand(time(NULL));
        const unsigned char result = rand() % size_tabBestCoup;
        bestCoup->x = tabBestCoup[result].x;
        bestCoup->y = tabBestCoup[result].y;
    }
    free(tabBestCoup);
    return score;
}

bool testWin(Game *game)
{

    Coor depart;
    Coor arriver;

    if (f_score(game->grille, game->playerActif, &depart, &arriver) > 80)
    {
        lineWinner(game, depart, arriver);
        game->boolMenu = set_tabBool(game->boolMenu, IN_GAME, false);
        game->boolMenu = set_tabBool(game->boolMenu, MENU_END, true);
        game->modeFinish = game->playerActif;
        if (game->playerActif == 1)
        {
            game->player1.score++;
        }
        else
        {
            game->player2.score++;
        }
        if (get_tabBool(game->boolMenu, SOLO) && game->NivAuto) {
            game->Niveau = game->startNiveau + (game->player1.score - game->player2.score);
            if (game->Niveau > 6)
                game->Niveau = 6;
            else if (game->Niveau < 1)
                game->Niveau = 1;
        }
        printf("Niveau : %d\n", game->Niveau);
        update(game);
        return true;
    }
    else if (grillePlein(game->grille))
    {
        game->boolMenu = set_tabBool(game->boolMenu, IN_GAME, false);
        game->boolMenu = set_tabBool(game->boolMenu, MENU_END, true);
        game->modeFinish = 0;
        update(game);
        return true;
    }
    else
    {
        game->playerActif *= -1;
        Test(game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, game->color.r, game->color.g, game->color.b, game->color.a) != 0, "SDL_SetRenderDrawColor", __FILE__, __LINE__);
        if (game->playerActif == 1)
        {
            Test(game->window, game->renderer, WARNING, SDL_RenderDrawLine(game->renderer, 5, SIZE_Y - 12, 5 + game->sizeNameJ1, SIZE_Y - 12), "SDL_RenderDrawLine", __FILE__, __LINE__);
            Test(game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, game->background.r, game->background.g, game->background.b, game->background.a) != 0, "SDL_SetRenderDrawColor", __FILE__, __LINE__);
            Test(game->window, game->renderer, WARNING, SDL_RenderDrawLine(game->renderer, SIZE_X - game->sizeNameJ2 - 5, SIZE_Y - 12, SIZE_X - 5, SIZE_Y - 12), "SDL_RenderDrawLine", __FILE__, __LINE__);
        }
        else
        {
            Test(game->window, game->renderer, WARNING, SDL_RenderDrawLine(game->renderer, SIZE_X - game->sizeNameJ2 - 5, SIZE_Y - 12, SIZE_X - 5, SIZE_Y - 12), "SDL_RenderDrawLine", __FILE__, __LINE__);
            Test(game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, game->background.r, game->background.g, game->background.b, game->background.a) != 0, "SDL_SetRenderDrawColor", __FILE__, __LINE__);
            Test(game->window, game->renderer, WARNING, SDL_RenderDrawLine(game->renderer, 5, SIZE_Y - 12, 5 + game->sizeNameJ1, SIZE_Y - 12), "SDL_RenderDrawLine", __FILE__, __LINE__);
        }
        SDL_RenderPresent(game->renderer);
    }
    return false;
}


void ouverture(Coor* coupOpen) {
    srand(time(NULL));
    const unsigned char configX[4] = { 0, 0, 2, 2};
    const unsigned char configY[4] = { 0, 2, 0, 2};
    const unsigned char result = rand() % 4;
    coupOpen->x = configX[result];
    coupOpen->y = configY[result];
}