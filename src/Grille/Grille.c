#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define FUNC_IMAGE
#define FUNC_GAME
#include "Grille.h"
#include "../Test/Test.h"
#include "../Image/Image.h"
#include "../Game/Game.h"
#include "../IA/IA.h"
#include "../Graphic/Graphic.h"

/**
 * \brief Teste si la grille est vide si oui retourne 1 (true)
 * 
 * \param grille  
 * 
 * \return true 
 * \return false 
 */
bool grilleVide(int (*grille)[LEN_GRILLE])
{
    for (int i = 0; i < LEN_GRILLE; i++)
    {
        for (int j = 0; j < LEN_GRILLE; j++)
        {
            if (grille[i][j] != 0)
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * \brief Teste si la grille est pleine si oui retourne 1 (true)
 * 
 * \param grille  
 * 
 * \return true 
 * \return false 
 */
bool grillePlein(int (*grille)[LEN_GRILLE])
{
    for (int i = 0; i < LEN_GRILLE; i++)
    {
        for (int j = 0; j < LEN_GRILLE; j++)
        {
            if (grille[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * \brief Reinitialiser la grille a 0
 * 
 * \param grille la grille a reinitiliser
 */
void resetGrille(int (*grille)[LEN_GRILLE])
{
    for (int i = 0; i < LEN_GRILLE; i++)
    {
        for (int j = 0; j < LEN_GRILLE; j++)
        {
            grille[j][i] = 0;
        }
    }
}

/**
 * \brief Efface l'ecran et affiche la grille sur l'interface
 * 
 * \param game Un pointeur sur la structure du jeu
 * \param w La largeur des lignes de la grille
 */
void printGrille( Game *game, const int w)
{
    Test(game->window, game->renderer, WARNING,
         SDL_SetRenderDrawColor(game->renderer, game->background.r, game->background.g, game->background.b, game->background.a),
         "SDL_SetRenderDrawColor", __FILE__, __LINE__ - 1);

    Test(game->window, game->renderer, WARNING, SDL_RenderClear(game->renderer) != 0, "SDL_RenderClear", __FILE__, __LINE__);

    Test(game->window, game->renderer, WARNING,
         SDL_SetRenderDrawColor(game->renderer, game->color.r, game->color.g, game->color.b, game->color.a),
         "SDL_SetRenderDrawColor", __FILE__, __LINE__ - 1);

    for (int i = 1; i < 3; i++)
    {
        SDL_Rect ligne;
        ligne.x = i * (SIZE_X / 3) - (w / 2);
        ligne.y = OF_SET;
        ligne.h = SIZE_Y - 2 * OF_SET;
        ligne.w = w;
        Test(game->window, game->renderer, WARNING, SDL_RenderFillRect(game->renderer, &ligne) != 0, "SDL_RenderFillRect", __FILE__, __LINE__);
    }
    for (int i = 1; i < 3; i++)
    {
        SDL_Rect ligne;
        ligne.x = 0;
        ligne.y = i * (SIZE_X / 3) - (w / 2) + OF_SET;
        ligne.h = w;
        ligne.w = SIZE_X;
        Test(game->window, game->renderer, WARNING, SDL_RenderFillRect(game->renderer, &ligne) != 0, "SDL_RenderFillRect", __FILE__, __LINE__);
    }

    IMG *SymJ1 = NULL;
    IMG *SymJ2 = NULL;
    if (grilleVide(game->grille))
    {
        return;
    }

    Test(game->window, game->renderer, FATAL_ERROR, IMG_Init(IMG_INIT_PNG) == 0, "IMG_Init", __FILE__, __LINE__);

    for (int i = 0; i < LEN_GRILLE; i++)
    {
        for (int j = 0; j < LEN_GRILLE; j++)
        {
            if (game->grille[i][j] == 1)
            {
                if (SymJ1 == NULL)
                {
                    SymJ1 = malloc(sizeof(IMG));
                    Test(game->window, game->renderer, ERROR, SymJ1 == NULL, "malloc", __FILE__, __LINE__ - 1);
                    loadImage(game->window, game->renderer, "assets/Croix.png", SymJ1);
                }
                printImage(game->window, game->renderer, SymJ1, j * (SIZE_X / 3) + ((SIZE_X / 3 - SIZE_X / 4) / 2),
                           i * (SIZE_X / 3) + OF_SET + ((SIZE_X / 3 - SIZE_X / 4) / 2), AUTO, AUTO);
            }
            else if (game->grille[i][j] == -1)
            {
                if (SymJ2 == NULL)
                {
                    SymJ2 = malloc(sizeof(IMG));
                    Test(game->window, game->renderer, ERROR, SymJ2 == NULL, "malloc", __FILE__, __LINE__ - 1);
                    loadImage(game->window, game->renderer, "assets/Rond.png", SymJ2);
                }
                printImage(game->window, game->renderer, SymJ2, j * (SIZE_X / 3) + ((SIZE_X / 3 - SIZE_X / 4) / 2),
                           i * (SIZE_X / 3) + OF_SET + ((SIZE_X / 3 - SIZE_X / 4) / 2), AUTO, AUTO);
            }
        }
    }
    IMG_Quit();
    if (SymJ1 != NULL)
    {
        freeImage(game->window, game->renderer, SymJ1);
        free(SymJ1);
        SymJ1 = NULL;
    }
    if (SymJ2 != NULL)
    {
        freeImage(game->window, game->renderer, SymJ2);
        free(SymJ2);
        SymJ2 = NULL;
    }
}

/**
 * \brief Affiche X ou O sur l'interface a l'emplacement de la case ou le joueur a clique
 * 
 * \param game Un pointeur sur la structure du jeu
 * \param clickX La position X de la souris lors du clique
 * \param clickY La position Y de la souris lors du clique
 * 
 * \return retourne 0 si ca marche sinon 1
 */
bool addGrille( Game *game, const int clickX, const int clickY)
{
    if (clickY >= OF_SET && clickY <= SIZE_Y - OF_SET)
    {
        int y = (clickY - OF_SET) / (SIZE_X / 3);
        int x = clickX / (SIZE_X / 3);
        if (game->grille[y][x] == 0)
        {
            game->grille[y][x] = game->playerActif;

            IMG Symbole;
            Test(game->window, game->renderer, FATAL_ERROR, IMG_Init(IMG_INIT_PNG) == 0, "IMG_Init", __FILE__, __LINE__);

            (game->playerActif == 1)
                ? loadImage(game->window, game->renderer, "assets/Croix.png", &Symbole)
                : loadImage(game->window, game->renderer, "assets/Rond.png", &Symbole);

            printImage(game->window, game->renderer, &Symbole, x * (SIZE_X / 3) + ((SIZE_X / 3 - SIZE_X / 4) / 2),
                       y * (SIZE_X / 3) + OF_SET + ((SIZE_X / 3 - SIZE_X / 4) / 2), AUTO, AUTO);

            freeImage(game->window, game->renderer, &Symbole);

            if (testWin(game)) {
                IMG_Quit();
                return false;
            }
            
            if ( game->playerActif == -1 && get_tabBool(game->boolMenu, SOLO) ) {
                Coor bestCoup;
                IA(game, game->playerActif, 1, &bestCoup);
                game->grille[bestCoup.y][bestCoup.x] = game->playerActif;
                loadImage(game->window, game->renderer, "assets/Rond.png", &Symbole);
                printImage(game->window, game->renderer, &Symbole, bestCoup.x * (SIZE_X / 3) + ((SIZE_X / 3 - SIZE_X / 4) / 2),
                       bestCoup.y * (SIZE_X / 3) + OF_SET + ((SIZE_X / 3 - SIZE_X / 4) / 2), AUTO, AUTO);
                freeImage(game->window, game->renderer, &Symbole);
                SDL_Delay(200);
                SDL_RenderPresent(game->renderer);
                if (testWin(game)) {
                    IMG_Quit();
                    return false;
                }

            }
            
            IMG_Quit();

            return false;
        }
    }
    return true;
}
