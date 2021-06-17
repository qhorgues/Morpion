#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SDL2/SDL.h>
#include "../Text/Text.h"
#define FUNC_IMAGE
#include "../Image/Image.h"
#include "../bool/bool.h"

typedef struct Button
{
    union {
        Text textButton;
        IMG ImgButton;
    };
    SDL_Rect rectButton;

    SDL_Color colorButton;
    bool buttonImage;
} Button;

void loadButtonText(SDL_Window* window, SDL_Renderer* renderer, const uint_fast16_t w, const uint_fast16_t h, const char * text, TTF_Font * font, Button* bouton, const SDL_Color colorText, const SDL_Color back);
Button* allocButtonText(SDL_Window* window, SDL_Renderer* renderer, const uint_fast16_t w, const int_fast16_t h, const char * text, TTF_Font * font, const SDL_Color colorText, const SDL_Color back);
void printButton(SDL_Window* window, SDL_Renderer* renderer, Button* bouton, uint_fast16_t x, uint_fast16_t y);
bool clickButton( const Button* bouton, const uint_fast16_t clickX, const uint_fast16_t clickY);
void freeButton(SDL_Window* window, SDL_Renderer* renderer, Button* bouton);

#endif
