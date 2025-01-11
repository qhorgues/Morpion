/**
 * \file Test.c
 * \author Quentin Horgues
 * \brief Le programme de test des condition
 * \version 0.1
 * \date 2021-05-10
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>

#include <SDL2/SDL.h>

#include "Test.h"

#define BLACK  "\033[30m"
#define RED    "\033[1;31m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE   "\033[1;34m"
#define NORMAL "\033[0;39m"

/**
 * \brief Quit detruit le rendue, la fenetre   et quitte la SDL
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param codeTest Le code d'erreur a renvoyer
 */
static void Quit(SDL_Window* window, SDL_Renderer* renderer, const int codeTest) {
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
 * \param file Le fichier du test, mettre __FILE__
 * \param line La ligne du test mettre __LINE__
 */
void Test(SDL_Window* window, SDL_Renderer* renderer, const int Priority, const bool condition, const char* message, const char* file, const int line) {
    // priority 1 for Warning 2 for Error, 3 for Fatal Error
    if (condition) {
        if (Priority == WARNING) {
            #if defined(_WIN32) || defined(_WIN64)
                if (printf("Warning : %s    file : %s in line %d   GetError: %s\n", message, file, line, SDL_GetError()) == EOF) {
            #else
                if (printf(YELLOW"Warning"NORMAL" : %s    file : %s in line %d   GetError: %s\n", message, file, line, SDL_GetError()) == EOF) {
            #endif
                Quit(window, renderer, -3);
            }
        }
        else if (Priority == ERROR) {
            #if defined(_WIN32) || defined(_WIN64)
                if (printf("Error : %s    file : %s in line %d   GetError: %s\n", message, file, line, SDL_GetError()) == EOF) {
            #else
                if (printf(RED"Error"NORMAL" : %s    file : %s in line %d   GetError: %s\n", message, file, line, SDL_GetError()) == EOF) {
            #endif
                Quit(window, renderer, -3);
            }
            Quit(window, renderer, 1);
        }
        else if (Priority == FATAL_ERROR) {
            #if defined(_WIN32) || defined(_WIN64)
                if (printf("Fatal error : %s    file : %s in line %d   GetError: %s\n", message, file, line, SDL_GetError()) == EOF) {
            #else
                if (printf(RED"Fatal error"NORMAL": %s    file : %s in line %d   GetError: %s\n", message, file, line, SDL_GetError()) == EOF) {
            #endif
                Quit(window, renderer, -3);
            }
            Quit(window, renderer, -1);
        }
    }
}