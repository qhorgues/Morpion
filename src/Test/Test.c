/**
 * \file Test.c
 * \author Quentin Horgues
 * \brief Le programme de teste des condition
 * \version 0.1
 * \date 2021-05-10
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>

#include <SDL2/SDL.h>

#include "Test.h"

/**
 * \brief Quit detruit le rendue, la fenetre   et quitte la SDL
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param codeTest Le code d'erreur a renvoyer
 */
static void Quit(SDL_Window* window, SDL_Renderer* renderer, const int_fast32_t codeTest) {
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer); // On detruit le rendue si il est non NULL
    }
    if (window != NULL) {
        SDL_DestroyWindow(window); // On detruit la fenetre si elle est non NULL
    }
    SDL_Quit();
    exit(codeTest);
}

/**
 * \brief Teste si une condition est vrai et affiche un message si vrai
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param Priority Definie la gravite de l'evenement : WARNING, ERROR, FATAL_ERROR
 * \param condition La condition a tester
 * \param message Le message a afficher
 * \param file Le fichier du teste, mettre __FILE__
 * \param line La ligne du teste mettre __LINE__
 */
void Test(SDL_Window* window, SDL_Renderer* renderer, const int_fast32_t Priority, const bool condition, const char* message, const char* file, const int_fast32_t line) {
    // priority 1 for Warning 2 for Test, 3 for Fatal Test
    if (condition) {
        if (Priority == 1) {
            if (printf("Warning : %s    file : %s in line %d   GetError: %s\n", message, file, line, SDL_GetError()) == EOF) {
                Quit(window, renderer, -3);
            }
        }
        else if (Priority == 2) {
            if (printf("Error : %s    file : %s in line %d   GetError: %s\n", message, file, line, SDL_GetError()) == EOF) {
                Quit(window, renderer, -3);
            }
            Quit(window, renderer, 1);
        }
        else if (Priority == 3) {
            if (printf("Fatal error : %s    file : %s in line %d   GetError: %s\n", message, file, line, SDL_GetError()) == EOF) {
                Quit(window, renderer, -3);
            }
            Quit(window, renderer, -1);
        }
    }
}