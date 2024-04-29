#include "menu.h"
#include <stdbool.h> 

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool initializeResources(SDL_Surface** screen, Mix_Music** backgroundMusic, SDL_Surface** backgroundImage) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (*screen == NULL) {
        printf("SDL_SetVideoMode Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Mix_OpenAudio Error: %s\n", Mix_GetError());
        SDL_Quit();
        return false;
    }

    *backgroundMusic = Mix_LoadMUS("music.mp3");
    if (*backgroundMusic == NULL) {
        printf("Mix_LoadMUS Error (music): %s\n", Mix_GetError());
        SDL_Quit();
        Mix_CloseAudio();
        return false;
    }
    Mix_PlayMusic(*backgroundMusic, -1);

    *backgroundImage = IMG_Load("bg_main.jpg");
    if (*backgroundImage == NULL) {
        printf("IMG_Load Error (background1.png): %s\n", IMG_GetError());
        Mix_FreeMusic(*backgroundMusic);
        SDL_Quit();
        return false;
    }

    return true;
}
SDL_Surface* createVideoMode(int width, int height) {
    SDL_Surface* screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    if (screen == NULL) {
        printf("SDL_SetVideoMode Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    return screen;
}
Mix_Music* loadMusic(const char* filename) {
    Mix_Music* music = Mix_LoadMUS(filename);
    if (music == NULL) {
        printf("Mix_LoadMUS Error (%s): %s\n", filename, Mix_GetError());
        SDL_Quit();
        exit(1);
    }
    return music;
}

Button initializeButton(int w, int h, int x, int y, const char* imageFile, const char* imageHoverFile) {
    Button button;
    button.rect.w = w;
    button.rect.h = h;
    button.rect.x = x;
    button.rect.y = y;
    button.image = loadImage(imageFile);
    button.imageHover = loadImage(imageHoverFile);
    if (button.image == NULL || button.imageHover == NULL) {
        printf("IMG_Load Error for button: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }
    return button;
}

bool isPointInsideButton(int x, int y, const Button* button) {
    return (x >= button->rect.x && x <= button->rect.x + button->rect.w &&
            y >= button->rect.y && y <= button->rect.y + button->rect.h);
}

// Function to draw a button with hover effect
void drawButton(SDL_Surface* screen, const Button* button, bool isHover) {
    if (button == NULL || button->image == NULL) {
        // Check if the button or its image is NULL
        printf("Error: Button or image is NULL\n");
        return;
    }

    // Choose the appropriate image based on hover state
    SDL_Surface* image = isHover ? button->imageHover : button->image;

    if (image == NULL) {
        // Check if the image is NULL
        printf("Error: Image is NULL\n");
        return;
    }

    // Update button image
    SDL_SetAlpha(image, SDL_SRCALPHA, 255);

    SDL_Rect dstRect;

    if (isHover) {
        dstRect.x = button->rect.x - (button->imageHover->w - button->image->w) / 2;
        dstRect.y = button->rect.y - (button->imageHover->h - button->image->h) / 2;
    } else {
        dstRect.x = button->rect.x;
        dstRect.y = button->rect.y;
    }

    dstRect.x += (button->rect.w - image->w) / 2;
    dstRect.y += (button->rect.h - image->h) / 2;

    SDL_BlitSurface(image, NULL, screen, &dstRect);
}

// Function to load image with case-insensitive file name
SDL_Surface* loadImage(const char* filename) {
    SDL_Surface* image = IMG_Load(filename);
    if (image == NULL) {
        // Try case-insensitive file name
        char lowercaseFilename[strlen(filename) + 1];
        for (size_t i = 0; i < strlen(filename) + 1; ++i) {
            lowercaseFilename[i] = tolower(filename[i]);
        }
        image = IMG_Load(lowercaseFilename);
    }

    if (image == NULL) {
        printf("IMG_Load Error: %s\n", IMG_GetError());
    }

    return image;
}

// Function to increase the volume
void increaseVolume() {
    int currentVolume = Mix_VolumeMusic(-1);
    Mix_VolumeMusic(currentVolume + MENU_VOLUME_STEP);
}

// Function to decrease the volume
void decreaseVolume() {
    int currentVolume = Mix_VolumeMusic(-1);
    Mix_VolumeMusic(currentVolume - MENU_VOLUME_STEP);
}

