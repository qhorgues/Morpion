/**
 * \file Image.h
 * \author Quentin Horgues
 * \brief La gestion des images
 * \version 0.2
 * \date 2021-05-10
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <SDL2/SDL.h>

#define AUTO 0

/**
 * \brief La structure d'une image
 * 
 * \param texture la texture de l'image
 * \param RectImage le rectangle des dimensions de l'image 
 */
typedef struct IMG
{
    // 8 Octets
    SDL_Texture* texture; // la texture de l'image
    SDL_Rect* RectImage; // le rectangle des dimensions de l'image
} IMG;

#ifdef FUNC_IMAGE

void loadImage_BMP(SDL_Window* window, SDL_Renderer* renderer, const char *PATH, IMG *image);

#include <SDL2/SDL_image.h>
void loadImage(SDL_Window* window, SDL_Renderer* renderer, const char *PATH, IMG *image);

void printImage(SDL_Window* window, SDL_Renderer* renderer, IMG * image, const uint_fast16_t x, const uint_fast16_t y, const uint_fast16_t w, const uint_fast16_t h); // Afficher l'image
void freeImage(SDL_Window* window, SDL_Renderer* renderer, IMG *image); // Liberer l'image en memoire

#endif // FUNC_IMAGE

#endif // !IMAGE_H_INCLUDED