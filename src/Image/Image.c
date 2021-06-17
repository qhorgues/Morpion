/**
 * \file Image.c
 * \author Quentin Horgues
 * \brief La gestion des images
 * \version 0.2
 * \date 2021-05-10
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Image.h"

#include "../bool/bool.h"
#include "../Test/Test.h"

/**
 * \brief Charger une image BMP en memoire
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param PATH Le chemin de l'image
 * \param image Un pointeur sur une structure IMG contenant la future image
 * 
 */
void loadImage_BMP(SDL_Window* window, SDL_Renderer* renderer, const char *PATH, IMG *image) { // Charger l'image en memoire
    image->RectImage = malloc(sizeof(SDL_Rect));
    Test( window, renderer, ERROR, image->RectImage == NULL, "malloc", __FILE__, __LINE__-1);

    SDL_Surface* imgSurface = SDL_LoadBMP(PATH); // On charge l'image en surface
    Test( window, renderer, ERROR, imgSurface == NULL, "IMG_Load", __FILE__, __LINE__-1);

    image->texture = SDL_CreateTextureFromSurface(renderer, imgSurface); // On convertie la surface en texture
    SDL_FreeSurface(imgSurface); // on libere la surface
    Test( window, renderer, ERROR, image->texture == NULL, "SDL_CreateTextureFromSurface", __FILE__, __LINE__);

    Test( window, renderer, WARNING, SDL_QueryTexture(image->texture, NULL, NULL, &image->RectImage->w, &image->RectImage->h), "SDL_QueryTexture", __FILE__, __LINE__);
    // On obtient les dimension de l'image
}

/**
 * \brief Charger une image en memoire /!\ Utilise SDL_image
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param PATH Le chemin de l'image
 * \param image Un pointeur sur une structure IMG contenant la future image
 * 
 */
void loadImage(SDL_Window* window, SDL_Renderer* renderer, const char *PATH, IMG *image) { // Charger l'image en memoire
    image->RectImage = malloc(sizeof(SDL_Rect));
    Test( window, renderer, ERROR, image->RectImage == NULL, "malloc", __FILE__, __LINE__-1);

    SDL_Surface* imgSurface = IMG_Load(PATH); // On charge l'image en surface
    Test( window, renderer, ERROR, imgSurface == NULL, "IMG_Load", __FILE__, __LINE__-1);

    image->texture = SDL_CreateTextureFromSurface(renderer, imgSurface); // On convertie la surface en texture
    SDL_FreeSurface(imgSurface); // on libere la surface
    Test( window, renderer, ERROR, image->texture == NULL, "SDL_CreateTextureFromSurface", __FILE__, __LINE__);

    Test( window, renderer, WARNING, SDL_QueryTexture(image->texture, NULL, NULL, &image->RectImage->w, &image->RectImage->h), "SDL_QueryTexture", __FILE__, __LINE__);
    // On obtient les dimension de l'image
}

/**
 * \brief copie l'image sur le rendue
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param image Un pointeur de la structure de l'image
 * \param x la coordonnee x de l'image
 * \param y la coordonnee y de l'image
 * \param w la largeur de l'image, AUTO pour la derniere largeur utilise
 * \param h la hauteur de l'image, AUTO pour la derniere hauteur utilise
 * 
 */
void printImage(SDL_Window* window, SDL_Renderer* renderer, IMG * image, const uint_fast16_t x, const uint_fast16_t y, const uint_fast16_t w, const uint_fast16_t h) { // Afficher l'image sur le rendue
    Test( window, renderer, FATAL_ERROR, image == NULL, "access to unallocated space", __FILE__, __LINE__);
    Test( window, renderer, ERROR, image->RectImage == NULL, "access to unallocated space", __FILE__, __LINE__);
    Test( window, renderer, ERROR, image->texture == NULL, "access to unallocated space", __FILE__, __LINE__);

    image->RectImage->x = x; // On definie la taille et la position de l'image
    image->RectImage->y = y;
    if (w != AUTO)
        image->RectImage->w = w;
    if (h != AUTO)
        image->RectImage->h = h;

    Test( window, renderer, WARNING, SDL_RenderCopy(renderer, image->texture, NULL, image->RectImage) != 0, "RenderCopy", __FILE__, __LINE__); // On copie l'image sur le rendue
}

/**
 * \brief Libere en memoire la texture de l'image et le rectangle de l'image
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param image Un pointeur de la structure de l'image
 * 
 */
void freeImage(SDL_Window* window, SDL_Renderer* renderer, IMG *image) { // Liberer l'image

    Test( window, renderer, FATAL_ERROR, image == NULL, "access to unallocated space", __FILE__, __LINE__);
    Test( window, renderer, WARNING, image->texture == NULL, "access to unallocated space", __FILE__, __LINE__);
    Test( window, renderer, WARNING, image->RectImage == NULL, "access to unallocated space", __FILE__, __LINE__);
    
    SDL_DestroyTexture(image->texture); // On libere la texture de l'image
    free(image->RectImage);
    image->texture = NULL;
    image->RectImage = NULL;
}