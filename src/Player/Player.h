#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Image/Image.h"
#define TAB_BOOL
#include "../bool/bool.h"
#include "../constante.h"



/**
 * \brief La structure d'un joueur
 * 
 * \param ID L'identifiant du joueur : 1 ou -1
 * \param Name Le nom du joueur
 * \param score Le score du joueur
 * 
 */
typedef struct Player
{
    // 8 Octets
    char * Name;

    // 1 Octet
    int_fast8_t ID;
    uint_fast8_t score;
} Player;

#include "../Game/Game.h"

void InitPlayer( const Game* game, Player* player, const char ID, const char * Name, const uint_fast8_t Score);
void changeName( const Game* game, Player* player, const char * Name);
void freePlayer(Player* player);


#endif