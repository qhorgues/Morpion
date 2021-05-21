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

#include <windows.h>
#include <string.h>


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
        fread(&color->r, sizeof(unsigned char), 1, file);
        fread(&color->g, sizeof(unsigned char), 1, file);
        fread(&color->b, sizeof(unsigned char), 1, file);
        fread(&color->a, sizeof(unsigned char), 1, file);
        fread(&background->r, sizeof(unsigned char), 1, file);
        fread(&background->g, sizeof(unsigned char), 1, file);
        fread(&background->b, sizeof(unsigned char), 1, file);
        fread(&background->a, sizeof(unsigned char), 1, file);
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
        fwrite(&color.r, sizeof(unsigned char), 1, file);
        fwrite(&color.g, sizeof(unsigned char), 1, file);
        fwrite(&color.b, sizeof(unsigned char), 1, file);
        fwrite(&color.a, sizeof(unsigned char), 1, file);
        fwrite(&background.r, sizeof(unsigned char), 1, file);
        fwrite(&background.g, sizeof(unsigned char), 1, file);
        fwrite(&background.b, sizeof(unsigned char), 1, file);
        fwrite(&background.a, sizeof(unsigned char), 1, file);
        Test( window, renderer, ERROR, fclose(file) == EOF, "fclose", __FILE__, __LINE__);
    }
}

const char* createFolder(void) {
    const size_t sizeFolder = 21 + strlen(getenv("APPDATA"));
    
    char * folder = malloc(sizeFolder * sizeof(char));
    folder = strcat(getenv("APPDATA"), "\\..\\LocalLow\\Morpion");

    char command[sizeFolder +12];
    strcpy(command, "mkdir ");
    strcat(command, folder);
    system(command);
    strcat(command, "\\save");
    command[sizeFolder+12] = '\0';
    system(command);

    const char * folderSave = strcat(folder, "\\save");
    return folderSave;
}