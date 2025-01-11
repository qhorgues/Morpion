/**
 * \file SetingFile.c
 * \author Quentin Horgues
 * \brief 
 * \version 0.1
 * \date 2021-05-10
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "../Test/Test.h"
#include "SetingFile.h"

#include <string.h>
#include <sys/stat.h>



/**
 * \brief Charge les parametres d'un fichier
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param PATH Le chemin d'acces du fichier
 * \param color Un pointeur sur color a modifier 
 * \param background Un pointeur sur background a modifier
 */
void loadSeting(SDL_Window* window, SDL_Renderer* renderer, const char* PATH, SDL_Color* color, SDL_Color* background) {
    FILE* file = fopen(PATH, "rb");

    if (file != NULL) {
        Test( window, renderer, ERROR, fread(&color->r, sizeof(int), 1, file) == 0, "fread", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fread(&color->g, sizeof(int), 1, file) == 0, "fread", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fread(&color->b, sizeof(int), 1, file) == 0, "fread", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fread(&color->a, sizeof(int), 1, file) == 0, "fread", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fread(&background->r, sizeof(int), 1, file) == 0, "fread", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fread(&background->g, sizeof(int), 1, file) == 0, "fread", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fread(&background->b, sizeof(int), 1, file) == 0, "fread", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fread(&background->a, sizeof(int), 1, file) == 0, "fread", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fclose(file) == EOF, "fclose", __FILE__, __LINE__);
    }
}
#include <errno.h>
/**
 * \brief Enregistre les parametres dans un fichier
 * 
 * \param window Un pointeur sur la fenetre
 * \param renderer Un pointeur sur le rendue
 * \param PATH Le chemin d'acces du fichier
 * \param color La structure color a sauvegarder 
 * \param background La structure background a sauvegarder 
 */
void saveSeting(SDL_Window* window, SDL_Renderer* renderer, const char* PATH, const SDL_Color color, const SDL_Color background) {

    FILE* file = fopen(PATH, "wba");
    
    if (file != NULL) {
        Test( window, renderer, ERROR, fwrite(&(color.r), sizeof(int), 1, file) == 0, "fwrite", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fwrite(&(color.g), sizeof(int), 1, file) == 0, "fwrite", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fwrite(&(color.b), sizeof(int), 1, file) == 0, "fwrite", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fwrite(&(color.a), sizeof(int), 1, file) == 0, "fwrite", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fwrite(&(background.r), sizeof(int), 1, file) == 0, "fwrite", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fwrite(&(background.g), sizeof(int), 1, file) == 0, "fwrite", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fwrite(&(background.b), sizeof(int), 1, file) == 0, "fwrite", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fwrite(&(background.a), sizeof(int), 1, file) == 0, "fwrite", __FILE__, __LINE__);
        Test( window, renderer, ERROR, fclose(file) == EOF, "fclose", __FILE__, __LINE__);
    }
}

char* createFolder(void) {

    #if defined(_WIN32) || defined(_WIN64)
        const int size_env = strlen(getenv("LOCALAPPDATA"));
        char *PATH = malloc(sizeof(char) * (size_env  + 21));
        Test(NULL, NULL, ERROR, PATH == NULL, "malloc", __FILE__, __LINE__);

        strcpy(PATH, getenv("LOCALAPPDATA"));

        strcat(PATH, "Morpion");

        mkdir(PATH);

    #elif defined(UNIX) || defined(__LINUX__)
        const size_t size_env = strlen(getenv("HOME"));
        char *PATH = malloc(sizeof(char) * (size_env  + 22));
        Test(NULL, NULL, ERROR, PATH == NULL, "malloc", __FILE__, __LINE__);

        strcpy(PATH, getenv("HOME"));

        strcat(PATH, "/.local/share/Morpion");

        mkdir(PATH, S_IRWXO | S_IRWXG | S_IRWXU);
        
    #else
        char *PATH = malloc(sizeof(char) * 7);
        Test(NULL, NULL, ERROR, PATH == NULL, "malloc", __FILE__, __LINE__);

        const char* PATH = "./Save";
        mkdir(PATH, S_IRUSR);
    #endif
    
    return PATH;
}