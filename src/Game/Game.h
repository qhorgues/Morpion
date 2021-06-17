#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define TAB_BOOL
#include "../bool/bool.h"
#include "../constante.h"
#include "../Player/Player.h"
#include "../Button/Button.h"

#ifndef STRUCT_GAME_INCLUDED
#define STRUCT_GAME_INCLUDED
typedef struct Game
{
    // 40 Octets 
    Player player1;
    Player player2;

    // x Octets
    Button* tabButton[N_BUTTON]; 

    // 9 Octets
    int_fast8_t grille[LEN_GRILLE][LEN_GRILLE];

    // 8 Octets
    SDL_Window* window;
    SDL_Renderer* renderer;

    // 4 Octets
    SDL_Color color;
    SDL_Color background;

    // 2 Octets
    uint_fast16_t sizeNameJ1;
    uint_fast16_t sizeNameJ2;

    // 1 Octet
    tabBool boolMenu;
    int_fast8_t startPlayer;
    int_fast8_t playerActif;
    int_fast8_t modeFinish;
    uint_fast8_t Niveau;
    uint_fast8_t startNiveau;
    bool NivAuto;
} Game;

#endif // !STRUCT_GAME_INCLUDED



#ifdef FUNC_GAME
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

Game initGame(const char * PATH_SaveFolder);
void freeGame( Game* game, const char * PATH_SaveFolder);
void update( Game* game);
bool getClick( Game* game, const uint_fast16_t clickX, const uint_fast16_t clickY);

#endif // !GAME_H_INCLUDED
#endif // FUNC_GAME
