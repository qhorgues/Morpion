/**
 * \file main.c
 * \author Quentin Horgues
 * \brief Le fichier des constantes 
 * \version 1.1
 * \date 2021-05-09
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#ifndef CONSTANTE_H_INCLUDED
#define CONSTANTE_H_INCLUDED

#include <stdint.h>

#define SIZE_X 360
#define SIZE_Y 480
#define LEN_GRILLE 3
#define OF_SET 60

#define BLUE {63,72,204, SDL_ALPHA_OPAQUE}

#ifdef TAB_BOOL
// Constante preprocesseur pour le tableau de booleen
#define IN_GAME 0
#define SOLO 1
#define MENU 2
#define MENU_LEVEL 3
#define MENU_END 4
#define SAVE_GAME 5
#define LOAD_GAME 6
#define CHANGE_COLOR 7
#endif // TAB_BOOL

#define N_BUTTON 5
#define OUI 0
#define NON 1
#define BUTTON_SOLO 0
#define BUTTON_MULTIPLAYER 1
#define BUTTON_EXIT 2
#define BUTTON_EASY 0
#define BUTTON_MEDIUM 1
#define BUTTON_HARD 2
#define BUTTON_RETURN 3
#define BUTTON_AUTO 4




#endif // !CONSTANTE_H_INCLUDED