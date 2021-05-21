#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>

#include "Divers.h"


void Version(void) {
    SDL_version SDL;
    SDL_GetVersion(&SDL);
    fprintf(stdout, "SDL %d.%d.%d | ", SDL.major, SDL.minor, SDL.patch);
    SDL_VERSION(&SDL);
    fprintf(stdout, "SDL %d.%d.%d\n", SDL.major, SDL.minor, SDL.patch);

    SDL_TTF_VERSION(&SDL)
    fprintf(stdout, "SDL_ttf %d.%d.%d\n", SDL.major, SDL.minor, SDL.patch);
    
    SDL_IMAGE_VERSION(&SDL);
    fprintf(stdout, "SDL_image %d.%d.%d\n", SDL.major, SDL.minor, SDL.patch);
}