#include "Button.h"
#include "../Test/Test.h"

Button* allocButtonText(SDL_Window* window, SDL_Renderer* renderer, const uint_fast16_t w, const signed int_fast16_t h, const char * text, TTF_Font * font, const SDL_Color colorText, const SDL_Color back) {
    Button* bouton = malloc(sizeof(Button));
    Test( window, renderer, ERROR, bouton == NULL, "malloc", __FILE__, __LINE__);
    loadButtonText( window, renderer, w, h, text, font, bouton, colorText, back);
    return bouton;
}

void loadButtonText(SDL_Window* window, SDL_Renderer* renderer, const uint_fast16_t w, const uint_fast16_t h, const char * text, TTF_Font * font, Button* bouton, const SDL_Color colorText, const SDL_Color back) {
    loadText( window, renderer, text, font, &bouton->textButton, colorText, SHADED, &back);
    if (bouton->textButton.RectText->w < w) {
        bouton->rectButton.w = w;
    } else {
        bouton->rectButton.w = bouton->textButton.RectText->w;
    }
    if (bouton->textButton.RectText->h < h) {
        bouton->rectButton.h = h;
    } else {
        bouton->rectButton.h = bouton->textButton.RectText->h;
    }
    bouton->colorButton = back;
}

void printButton(SDL_Window* window, SDL_Renderer* renderer, Button* bouton, const uint_fast16_t x, const uint_fast16_t y) {
    bouton->rectButton.x = x;
    bouton->rectButton.y = y;
    Test( window, renderer, WARNING, SDL_SetRenderDrawColor(renderer, bouton->colorButton.r, bouton->colorButton.g, bouton->colorButton.b, bouton->colorButton.a) != 0, "SDL_SetRenderDrawColor", __FILE__, __LINE__);
    Test(window, renderer, WARNING, SDL_RenderFillRect(renderer, &bouton->rectButton) != 0, "SDL_RenderFillRect", __FILE__, __LINE__);
    if (bouton->buttonImage) {
        printImage(window, renderer, &bouton->ImgButton, (bouton->rectButton.x + bouton->rectButton.w/2) - bouton->textButton.RectText->w/2, (bouton->rectButton.y + bouton->rectButton.h/2) - bouton->textButton.RectText->h/2, AUTO, AUTO);
    } else {
        printText(window, renderer, &bouton->textButton, (bouton->rectButton.x + bouton->rectButton.w/2) - bouton->textButton.RectText->w/2, (bouton->rectButton.y + bouton->rectButton.h/2) - bouton->textButton.RectText->h/2);
    }
}

bool clickButton( const Button* bouton, const uint_fast16_t clickX, const uint_fast16_t clickY) {
    if (bouton != NULL) {
        if (clickX >= bouton->rectButton.x && clickX <= bouton->rectButton.x + bouton->rectButton.w && clickY >= bouton->rectButton.y && clickY <= bouton->rectButton.y + bouton->rectButton.h) {
        return true;
        }
    }
    return false;
    
}

void freeButton(SDL_Window* window, SDL_Renderer* renderer, Button* bouton) {
    freeText(window, renderer, &bouton->textButton);
}