// map.h
#ifndef MAP_H
#define MAP_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600
#define LARGEUR_CAMERA 320
#define HAUTEUR_CAMERA 240
#define REDUCTION_MINIMAP 10
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 32

typedef struct
{
    SDL_Surface *map;
    SDL_Rect mapPosition;
    SDL_Surface *minimap;
    SDL_Rect minimapPosition;
    SDL_Surface *playerImage;
    SDL_Rect playerPosition;
    SDL_Rect rectanglePosition;
} MapData;

void initMap(MapData *mapData);
void afficherMap(MapData mapData, SDL_Surface *screen, TTF_Font *font);
void animerMinimap(MapData *mapData, int x, int y);
void MAJMinimap(SDL_Rect posJoueur, MapData *m, SDL_Rect camera, int redimensionnement);
void Liberer(MapData *m);

#endif

