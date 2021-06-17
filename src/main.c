/**
 * @file main.c
 * @author Quentin Horgues
 * @brief 
 * @version 0.1
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#define FUNC_GAME
#include "Game/Game.h"
#include "Divers/Divers.h"
#include "Test/Test.h"
#include "Grille/Grille.h"
#include "SetingFile/SetingFile.h"

#undef main

int_fast32_t main(void)
{
    const char * PATH = createFolder();
    Version();

    Test( NULL, NULL, FATAL_ERROR, SDL_Init(SDL_INIT_EVENTS) != 0, "SDL_Init", __FILE__, __LINE__); // on charge la SDL

    Game game = initGame(PATH);

    SDL_Event event;
    
    while (SDL_WaitEvent(&event))
    {
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if( getClick(&game, event.motion.x, event.motion.y) ) {
                goto end;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    changeColor(&game);
                    break;
                case SDLK_ESCAPE:
                    goto end;
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    game.boolMenu = set_tabBool(game.boolMenu, CHANGE_COLOR, true);
                    break;
                default:
                    break;
            }
            break;
        case SDL_QUIT:
            goto end;
            break;
        default:
            break;
        }
    }

end:
    // Liberation memoire
    freeGame(&game, PATH);
    SDL_Quit();
    return 0;
}