#ifndef DIVERS_H_INCLUDED
#define DIVERS_H_INCLUDED

#include <SDL2/SDL.h>
#include "../Game/Game.h"
void changeColor( Game* game);
SDL_Color rgba_to_color( const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
void Version(void);

#endif // !DIVERS_H_INCLUDED