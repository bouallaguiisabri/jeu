// map.c
#include "map.h"

void initMap(MapData *mapData)
{
    // Load map image
    mapData->map = IMG_Load("map.png");
    if (!mapData->map)
    {
        printf("Erreur lors du chargement de l'image de la grande carte : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    // Load minimap image
    mapData->minimap = IMG_Load("min_map.png");
    if (!mapData->minimap)
    {
        printf("Erreur lors du chargement de l'image de la minimap : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    // Load player image
    mapData->playerImage = IMG_Load("joueur.png");
    if (!mapData->playerImage)
    {
        printf("Erreur lors du chargement de l'image du joueur : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    // Initialize player position
    mapData->playerPosition.x = 0;
    mapData->playerPosition.y = 0;
    mapData->playerPosition.w = PLAYER_WIDTH;
    mapData->playerPosition.h = PLAYER_HEIGHT;

    // Initialize rectangle position on minimap
    mapData->rectanglePosition.x = 0;
    mapData->rectanglePosition.y = 0;
    mapData->rectanglePosition.w = 10;
    mapData->rectanglePosition.h = 10;
}

void afficherMap(MapData mapData, SDL_Surface *screen, TTF_Font *font)
{
    // Blit map onto screen
    SDL_BlitSurface(mapData.map, NULL, screen, &mapData.mapPosition);

    // Blit minimap onto screen
    SDL_BlitSurface(mapData.minimap, NULL, screen, &mapData.minimapPosition);

    // Blit player onto screen
    SDL_BlitSurface(mapData.playerImage, NULL, screen, &mapData.playerPosition);

    // Update position of rectangle representing player on minimap
    mapData.rectanglePosition.x = (mapData.playerPosition.x * mapData.minimapPosition.w) / mapData.mapPosition.w;
    mapData.rectanglePosition.y = (mapData.playerPosition.y * mapData.minimapPosition.h) / mapData.mapPosition.h;

    // Display rectangle representing player on minimap
    SDL_FillRect(screen, &mapData.rectanglePosition, SDL_MapRGB(screen->format, 255, 255, 255));

    // Display time in the format min:sec
    int elapsedSeconds = SDL_GetTicks() / 1000;
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;
    char timeText[10];
    sprintf(timeText, "%02d:%02d", minutes, seconds);
    SDL_Color textColor = {255, 255, 255, 0}; // White color
    SDL_Surface *timeSurface = TTF_RenderText_Solid(font, timeText, textColor);
    SDL_Rect timePosition = {1, 560, 0, 0}; // Position of the time text
    SDL_BlitSurface(timeSurface, NULL, screen, &timePosition); // Blit time text onto screen
    SDL_FreeSurface(timeSurface); // Free surface
}

void animerMinimap(MapData *mapData, int x, int y)
{
    // Update the position of the rectangle representing the animation
    mapData->rectanglePosition.x = x;
    mapData->rectanglePosition.y = y;

    // Change the color of the puzzle/enigma positions on the minimap dynamically
    static Uint8 color = 0; // Initialize color value
    color += 5;             // Increment color value (adjust as needed for desired speed)
    if (color > 255)
        color = 0; // Reset color value if it exceeds 255 (RGB range)
    Uint32 newColor = SDL_MapRGB(mapData->minimap->format, color, 0, 0); // Create new color with varying red component

    // Fill the rectangle representing the puzzle/enigma positions with the new color
    SDL_FillRect(mapData->minimap, &mapData->rectanglePosition, newColor);
}

void MAJMinimap(SDL_Rect posJoueur, MapData *m, SDL_Rect camera, int redimensionnement)
{
    // Calculate absolute player position
    SDL_Rect posJoueurABS;
    posJoueurABS.x = posJoueur.x + camera.x;
    posJoueurABS.y = posJoueur.y + camera.y;

    // Update position of the miniature character on the minimap
    m->rectanglePosition.x = posJoueurABS.x * redimensionnement / 100;
    m->rectanglePosition.y = posJoueurABS.y * redimensionnement / 100;
}

void Liberer(MapData *m)
{
    SDL_FreeSurface(m->minimap);
    SDL_FreeSurface(m->playerImage);
}

