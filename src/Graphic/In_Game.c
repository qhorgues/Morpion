#include <stdio.h>

#include "Graphic.h"
#include "../Grille/Grille.h"
#include "../Text/Text.h"
#include "../Test/Test.h"

/**
 * \brief Obtenir le nombre de caractere d'un nombre
 * 
 * \param nb Un nombre
 * \return le nombre de caractere du nombre
 */
size_t intLen(int nb) {
    size_t count = 1;
    while (nb > 1) {
        nb /= 10;
        count++;
    }
    return count;
}

/**
 * \brief Create a Text Score object
 * 
 * \param game Un pointeur sur la structure du jeu
 * \param font la police
 * \param txt le texte decrivant le score
 * \param score le score
 * 
 * \return Une structure Text
 */
Text createTextScore( const Game* game, TTF_Font* font, const char* txt, const int score) {
    
    size_t lenScore = strlen(txt) + 3 + intLen(score);
    char* strScore = malloc( (lenScore + 1) * sizeof(char));
    Test(game->window, game->renderer, ERROR, sprintf(strScore, "%s : %d", txt, score) == EOF, "sprintf", __FILE__, __LINE__);
    strScore[lenScore] = '\0';
    
    Text textSxore;
    loadText(game->window, game->renderer, strScore, font, &textSxore, game->color, SHADED, &game->background);
    free(strScore);

    return textSxore;
}

/**
 * \brief actualise l'ecran en plein jeu
 * 
 * \param game Un pointeur sur la structure du jeu
 */
void update_in_game( Game* game) {
    printGrille(game, 5);
    // Score 1
    Test(game->window, game->renderer, FATAL_ERROR, TTF_Init() != 0, "TTF_Init", __FILE__, __LINE__);

    TTF_Font* calibri = TTF_OpenFont("assets/Fonts/calibrib.ttf", OF_SET/2);
    Test(game->window, game->renderer, ERROR, calibri == NULL, "TTF_OpenFont", __FILE__, __LINE__-1);

    Text textScore1 = createTextScore(game, calibri, game->player1.Name, game->player1.score);
    printText(game->window, game->renderer, &textScore1, 5, SIZE_Y - (OF_SET/4) - textScore1.RectText->h);
    game->sizeNameJ1 = textScore1.RectText->w;
    freeText(game->window, game->renderer, &textScore1);

    Text textScore2 = createTextScore(game, calibri, game->player2.Name, game->player2.score);
    printText(game->window, game->renderer, &textScore2, SIZE_X - textScore2.RectText->w - 5, SIZE_Y - (OF_SET/4) - textScore2.RectText->h);
    game->sizeNameJ2 = textScore2.RectText->w;
    freeText(game->window, game->renderer, &textScore2);

    Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, game->color.r, game->color.g, game->color.b, game->color.a) != 0, "SDL_SetRenderDrawColor", __FILE__, __LINE__);
    if (game->playerActif == 1) {
        Test( game->window, game->renderer, WARNING, SDL_RenderDrawLine(game->renderer, 5, SIZE_Y-12, 5+game->sizeNameJ1, SIZE_Y-12), "SDL_RenderDrawLine", __FILE__, __LINE__);
        Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, game->background.r, game->background.g, game->background.b, game->background.a) != 0, "SDL_SetRenderDrawColor", __FILE__, __LINE__);
        Test( game->window, game->renderer, WARNING, SDL_RenderDrawLine(game->renderer, SIZE_X-game->sizeNameJ2-5, SIZE_Y-12, SIZE_X-5, SIZE_Y-12), "SDL_RenderDrawLine", __FILE__, __LINE__);
    } else {
        Test( game->window, game->renderer, WARNING, SDL_RenderDrawLine(game->renderer, SIZE_X-game->sizeNameJ2-5, SIZE_Y-12, SIZE_X-5, SIZE_Y-12), "SDL_RenderDrawLine", __FILE__, __LINE__);
        Test( game->window, game->renderer, WARNING, SDL_SetRenderDrawColor(game->renderer, game->background.r, game->background.g, game->background.b, game->background.a) != 0, "SDL_SetRenderDrawColor", __FILE__, __LINE__);
        Test( game->window, game->renderer, WARNING, SDL_RenderDrawLine(game->renderer, 5, SIZE_Y-12, 5+game->sizeNameJ1, SIZE_Y-12), "SDL_RenderDrawLine", __FILE__, __LINE__);
    }

    TTF_CloseFont(calibri);
    TTF_Quit();
}