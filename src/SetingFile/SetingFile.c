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

//#include <windows.h>
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
        fread(&color->r, sizeof(unint_fast8_t), 1, file);
        fread(&color->g, sizeof(unint_fast8_t), 1, file);
        fread(&color->b, sizeof(unint_fast8_t), 1, file);
        fread(&color->a, sizeof(unint_fast8_t), 1, file);
        fread(&background->r, sizeof(unint_fast8_t), 1, file);
        fread(&background->g, sizeof(unint_fast8_t), 1, file);
        fread(&background->b, sizeof(unint_fast8_t), 1, file);
        fread(&background->a, sizeof(unint_fast8_t), 1, file);
        Test( window, renderer, ERROR, fclose(file) == EOF, "fclose", __FILE__, __LINE__);
    }
}

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
        fwrite(&color.r, sizeof(unint_fast8_t), 1, file);
        fwrite(&color.g, sizeof(unint_fast8_t), 1, file);
        fwrite(&color.b, sizeof(unint_fast8_t), 1, file);
        fwrite(&color.a, sizeof(unint_fast8_t), 1, file);
        fwrite(&background.r, sizeof(unint_fast8_t), 1, file);
        fwrite(&background.g, sizeof(unint_fast8_t), 1, file);
        fwrite(&background.b, sizeof(unint_fast8_t), 1, file);
        fwrite(&background.a, sizeof(unint_fast8_t), 1, file);
        Test( window, renderer, ERROR, fclose(file) == EOF, "fclose", __FILE__, __LINE__);
    }
}

const char* createFolder(void) {
    const size_t sizeFolder = 21 + strlen(getenv("APPDATA"));
    
    char folder[sizeFolder];
    strcpy(folder, getenv("APPDATA"));
    strcat(folder, "\\..\\LocalLow\\Morpion");

    mkdir(folder);
    char command[sizeFolder +5];
    strcpy(command, folder);
    strcat(command, "\\save");
    mkdir(command);

    const char * folderSave = strcat(folder, "\\save");

    return folderSave;
}