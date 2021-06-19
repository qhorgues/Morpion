/**
 * \file Test.h
 * \author Quentin Horgues
 * \brief Le programme de teste des conditions
 * \version 0.1
 * \date 2021-05-10
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "../bool/bool.h"

#define WARNING 1
#define ERROR 2
#define FATAL_ERROR 3

void Test(SDL_Window* window, SDL_Renderer* renderer, const int_fast32_t Priority, const bool condition, const char* message, const char* file, const int_fast32_t line);

#endif // TEST_H_INCLUDED