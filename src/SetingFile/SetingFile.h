/**
 * \file SetingFile.h
 * \author Quentin Horgues
 * \brief 
 * \version 0.1
 * \date 2021-05-10
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#ifndef SETING_FILE_H_INCLUDED
#define SETING_FILE_H_INCLUDED

#include <SDL2/SDL.h>

void loadSeting(SDL_Window* window, SDL_Renderer* renderer, const char* PATH, SDL_Color* color, SDL_Color* background);
void saveSeting(SDL_Window* window, SDL_Renderer* renderer, const char* PATH, const SDL_Color color, const SDL_Color background);
char* createFolder(void);


#endif // !SETING_FILE_H_INCLUDED