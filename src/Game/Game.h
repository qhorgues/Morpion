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
    signed char grille[LEN_GRILLE][LEN_GRILLE];

    // 8 Octets
    SDL_Window* window;
    SDL_Renderer* renderer;

    // 4 Octets
    SDL_Color color;
    SDL_Color background;

    // 2 Octets
    unsigned short sizeNameJ1;
    unsigned short sizeNameJ2;

    // 1 Octet
    tabBool boolMenu;
    signed char startPlayer;
    signed char playerActif;
    signed char modeFinish;
    unsigned char Niveau;
    unsigned char startNiveau;
    bool NivAuto;
} Game;

#endif // !STRUCT_GAME_INCLUDED



#ifdef FUNC_GAME
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

Game initGame(const char * PATH_SaveFolder);
void freeGame( Game* game, const char * PATH_SaveFolder);
void update( Game* game);
bool getClick( Game* game, const unsigned short clickX, const unsigned short clickY);

#endif // !GAME_H_INCLUDED
#endif // FUNC_GAME
