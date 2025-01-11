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

    Player player1;
    Player player2;

    Button* tabButton[N_BUTTON]; 

    int grille[LEN_GRILLE][LEN_GRILLE];

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Color color;
    SDL_Color background;

    int sizeNameJ1;
    int sizeNameJ2;

    tabBool boolMenu;
    int startPlayer;
    int playerActif;
    int modeFinish;
    int Niveau;
    int startNiveau;
    bool NivAuto;
} Game;

#endif // !STRUCT_GAME_INCLUDED



#ifdef FUNC_GAME
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

Game initGame(const char * PATH_SaveFolder);
void freeGame( Game* game, const char * PATH_SaveFolder);
void update( Game* game);
bool getClick( Game* game, const int clickX, const int clickY);

#endif // !GAME_H_INCLUDED
#endif // FUNC_GAME
