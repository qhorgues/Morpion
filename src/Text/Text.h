/**
 * \file Text.h
 * \author Quentin Horgues
 * \brief 
 * \version 0.2
 * \date 2021-05-10
 * 
 * \copyright Copyright (c) 2021
 * 
 */
#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define BLENDED 3
#define SHADED 2
#define SOLID 1

/**
 * \brief La structure pour les textes
 * 
 * \param texture la texture du texte
 * \param RectText le rectangle des dimensions du texte 
 */
typedef struct Text
{
    SDL_Texture* texture;
    SDL_Rect* RectText;
} Text;

void loadText(SDL_Window* window, SDL_Renderer* renderer, const char * text, TTF_Font * font, Text* text_ptr, const SDL_Color colorText, const unsigned char Quality, const SDL_Color* background);
void printText(SDL_Window* window, SDL_Renderer* renderer, Text* text, const unsigned short x, const unsigned short y);
void freeText(SDL_Window* window, SDL_Renderer* renderer, Text *text);

#endif // !TEXT_H_INCLUDED