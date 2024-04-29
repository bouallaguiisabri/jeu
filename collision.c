// collision.c
#include "collision.h"


Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    // Convert the surface to 32-bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    // Get the pixel at the desired position
    return pixels[(y * surface->w) + x];
}
int collisionPP(SDL_Rect playerPosition, SDL_Surface *mask)
{
    int playerCenterX = playerPosition.x + (playerPosition.w / 2);
    int playerCenterY = playerPosition.y + (playerPosition.h / 2);
    Uint8 r, g, b;
    SDL_GetRGB(get_pixel(mask, playerCenterX, playerCenterY), mask->format, &r, &g, &b);
    if (r == 0 && g == 0 && b == 0)
    {
        return 1;
    }
    return 0;
}

void handleCollisionWindow(SDL_Surface *screen, int *collisionFlag)
{
    SDL_Surface *collisionScreen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    if (!collisionScreen)
    {
        printf("Erreur lors de la création de la fenêtre de collision : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FillRect(collisionScreen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_Flip(collisionScreen);
    int running = 1;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
    }
    SDL_FreeSurface(collisionScreen);
    *collisionFlag = 0;
}

