#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>

// Constants
#define MENU_VOLUME_STEP 10

// Structure for a button
typedef struct {
    SDL_Rect rect;           // Rectangle representing the button's position and size
    SDL_Surface* image;      // Image for the button
    SDL_Surface* imageHover; // Image for the button when hovered
} Button;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
// Function declarations
bool initializeResources(SDL_Surface** screen, Mix_Music** backgroundMusic, SDL_Surface** backgroundImage);
SDL_Surface* createVideoMode(int width, int height);
Mix_Music* loadMusic(const char* filename);
Button initializeButton(int w, int h, int x, int y, const char* imageFile, const char* imageHoverFile);
bool isPointInsideButton(int x, int y, const Button* button);
void drawButton(SDL_Surface* screen, const Button* button, bool isHover);
SDL_Surface* loadImage(const char* filename);
void increaseVolume();
void decreaseVolume();



#endif /* MENU_H */
