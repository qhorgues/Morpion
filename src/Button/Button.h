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

void loadButtonText(SDL_Window* window, SDL_Renderer* renderer, const unsigned short w, const unsigned short h, const char * text, TTF_Font * font, Button* bouton, const SDL_Color colorText, const SDL_Color back);
Button* allocButtonText(SDL_Window* window, SDL_Renderer* renderer, const unsigned short w, const signed short h, const char * text, TTF_Font * font, const SDL_Color colorText, const SDL_Color back);
void printButton(SDL_Window* window, SDL_Renderer* renderer, Button* bouton, unsigned short x, unsigned short y);
bool clickButton( const Button* bouton, const unsigned short clickX, const unsigned short clickY);
void freeButton(SDL_Window* window, SDL_Renderer* renderer, Button* bouton);

#endif
