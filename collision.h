// collision.h
#ifndef COLLISION_H
#define COLLISION_H

#include "SDL/SDL.h"

Uint32 get_pixel(SDL_Surface *surface, int x, int y);
int collisionPP(SDL_Rect playerPosition, SDL_Surface *mask);
void handleCollisionWindow(SDL_Surface *screen, int *collisionFlag);

#endif

