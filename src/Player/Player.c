#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <string.h>

#define FUNC_IMAGE
#include "Player.h"
#include "../Test/Test.h"


/**
 * \brief Initialiser une structure Player
 * 
 * \param game Un pointeur sur la structure Game
 * \param player Un pointeur sur la structure Player a modifier
 * \param ID L'identifiant du joueur
 * \param Name Le nom du joueur
 * \param Score Le score du joueur
 */
void InitPlayer( const Game* game, Player* player, const char ID, const char * Name, const int Score) {
    player->ID = ID;
    player->score = Score;

    size_t sizeName = strlen(Name);
    player->Name = malloc( ( sizeName + 1 ) * sizeof(char) );
    Test(game->window, game->renderer, WARNING, player->Name == NULL, "malloc", __FILE__, __LINE__);
    Test(game->window, game->renderer, WARNING, strcpy(player->Name, Name) == 0, "strcpy", __FILE__, __LINE__);
    player->Name[sizeName] = '\0';
}

/**
 * \brief Changer le nom d'un joueur
 * 
 * \param game Un pointeur sur la structure Game
 * \param player Un pointeur sur la structure Player a modifier
 * \param Name Le nom du joueur
 */
void changeName( const Game* game, Player* player, const char * Name) {
    size_t sizeName = strlen(Name);
    player->Name = realloc( player->Name, ( sizeName + 1 ) * sizeof(char) );
    Test(game->window, game->renderer, WARNING, player->Name == NULL, "realloc", __FILE__, __LINE__);
    Test(game->window, game->renderer, WARNING, strcpy(player->Name, Name) == NULL, "strcpy", __FILE__, __LINE__);
    player->Name[sizeName] = '\0';
}

void freePlayer(Player* player) {
    if (player->Name != NULL)
        free(player->Name);
    player->Name = NULL;
}