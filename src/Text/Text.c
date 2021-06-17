/**
 * \file Text.c
 * \author Quentin Horgues
 * \brief La gestion du texte en SDL /!\ necessite SDL_ttf
 * \version 0.1
 * \date 2021-05-10
 * 
 * \copyright Copyright (c) 2021
 * 
 */


#include "Text.h"
#include "../Test/Test.h"

/**
 * \brief Charger le texte en memoire
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param text Le texte a afficher
 * \param font Un pointeur sur une structure TTF_Font (la police)
 * \param text_ptr Un pointeur sur une stucture Text non alloue 
 * \param colorText Une structure pour la couleur du texte
 * \param Quality La qualite du texte utiliser : BLENDED, SHADED, SOLID
 * \param background Si SHADED Un pointeur sur une structure pour la couleur de fond sinon NULL
 */
void loadText(SDL_Window* window, SDL_Renderer* renderer, const char * text, TTF_Font * font, Text* text_ptr, const SDL_Color colorText, const uint_fast8_t Quality, const SDL_Color* background) { // Charger le texte en memoire
    text_ptr->RectText = malloc(sizeof(SDL_Rect));
    Test(window, renderer, ERROR, text_ptr->RectText == NULL, "malloc", __FILE__, __LINE__-1);

    // On charge le texte en surface
    SDL_Surface* TextSurface = NULL;
    if (Quality == 3) {
        TextSurface = TTF_RenderUTF8_Blended(font, text, colorText);
        Test(window, renderer, ERROR, TextSurface == NULL, "TTF_RenderUTF8_Blended", __FILE__, __LINE__-1);
    } else if (Quality == 2) {
        TextSurface = TTF_RenderUTF8_Shaded(font, text, colorText, *background);
        Test(window, renderer, ERROR, TextSurface == NULL, "TTF_RenderUTF8_Shaded", __FILE__, __LINE__-1);
    } else {
        TextSurface = TTF_RenderUTF8_Solid(font, text, colorText);
        Test(window, renderer, ERROR, TextSurface == NULL, "TTF_RenderUTF8_Solid", __FILE__, __LINE__-1);
    }

    text_ptr->texture = SDL_CreateTextureFromSurface(renderer, TextSurface); // On convertie la surface en texture
    SDL_FreeSurface(TextSurface); // on libere la surface
    Test(window, renderer, ERROR, text_ptr->texture == NULL, "SDL_CreateTextureFromSurface", __FILE__, __LINE__);

    Test(window, renderer, WARNING, SDL_QueryTexture(text_ptr->texture, NULL, NULL, &text_ptr->RectText->w, &text_ptr->RectText->h), "SDL_QueryTexture", __FILE__, __LINE__);
    // On obtient les dimension du texte
}

/**
 * \brief Afficher le texte
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param text Un pointeur sur la structure Text
 * \param x la coordonnee x du texte
 * \param y la coordonnee y du texte
 */
void printText(SDL_Window* window, SDL_Renderer* renderer, Text* text, const uint_fast16_t x, const uint_fast16_t y) { // Afficher le texte
    Test(window, renderer, FATAL_ERROR, text == NULL, "access to unallocated space", __FILE__, __LINE__);
    Test(window, renderer, ERROR, text->RectText == NULL, "access to unallocated space", __FILE__, __LINE__);
    Test(window, renderer, ERROR, text->texture == NULL, "access to unallocated space", __FILE__, __LINE__);

    text->RectText->x = x;// On definie la position du texte
    text->RectText->y = y;
    Test(window, renderer, WARNING, SDL_RenderCopy(renderer, text->texture, NULL, text->RectText) != 0, "RenderCopy", __FILE__, __LINE__); // On copie le texte sur le rendue
}

/**
 * \brief Liberer la texture et le rect du texte
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param text Un pointeur sur la structure du texte
 */
void freeText(SDL_Window* window, SDL_Renderer* renderer, Text *text) { // Liberer le texte

    Test(window, renderer, FATAL_ERROR, text == NULL, "access to unallocated space", __FILE__, __LINE__);
    Test(window, renderer, WARNING, text->texture == NULL, "access to unallocated space", __FILE__, __LINE__);
    Test(window, renderer, WARNING, text->RectText == NULL, "access to unallocated space", __FILE__, __LINE__);
    
    SDL_DestroyTexture(text->texture); // On libere la texture du texte
    free(text->RectText);
    text->texture = NULL;
    text->RectText = NULL;
}