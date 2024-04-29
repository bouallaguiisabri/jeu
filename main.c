#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"
#include "SDL/SDL_ttf.h"
#include "map.h"
#include "collision.h"
#include "savegame.h"
#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600
#define LARGEUR_CAMERA 320
#define HAUTEUR_CAMERA 240
#define REDUCTION_MINIMAP 10 
#define PLAYER_WIDTH 32      
#define PLAYER_HEIGHT 32 
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
const int MIN_VOLUME = 0;
const int MAX_VOLUME = 100;
const int VOLUME_STEP = 10;
bool mainScreenMusicPlaying = true;
int main() {
    TTF_Init();
      SDL_Surface* screen = NULL;
    Mix_Music* backgroundMusic = NULL;
    SDL_Surface* backgroundImage = NULL;
    if (!initializeResources(&screen, &backgroundMusic, &backgroundImage)) {
        return 1;
    }
    TTF_Font *font = TTF_OpenFont("DS-DIGI.TTF", 40);
    if (!font)
    {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
        
 Button playButton = initializeButton(300, 90, (SCREEN_WIDTH - 300) / 2, (SCREEN_HEIGHT - 90 * 3) / 2, "play.png", "play1.png");
Button settingsButton = initializeButton(300, 90, (SCREEN_WIDTH - 300) / 2, playButton.rect.y + playButton.rect.h + 20, "settings.png", "settings1.png");
Button shutdownButton = initializeButton(300, 90, (SCREEN_WIDTH - 300) / 2, settingsButton.rect.y + settingsButton.rect.h + 20, "shutdown.png", "shutdown1.png");
    bool quitMainScreen = false;
    SDL_Event eventMainScreen;
    bool playHover = false;
    bool settingsHover = false;
    bool shutdownHover = false;
    SDL_Surface* animationFrames[3];
animationFrames[0] = loadImage("NEXUS.png");
animationFrames[1] = loadImage("NEXUS1.png");
animationFrames[2] = loadImage("NEXUS2.png");
int currentFrame = 0;
int frameDuration = 100;
while (!quitMainScreen) {
        while (SDL_PollEvent(&eventMainScreen)) {
            if (eventMainScreen.type == SDL_QUIT) {
                quitMainScreen = true;
            } else if (eventMainScreen.type == SDL_MOUSEMOTION) {
                playHover = isPointInsideButton(eventMainScreen.motion.x, eventMainScreen.motion.y, &playButton);
                settingsHover = isPointInsideButton(eventMainScreen.motion.x, eventMainScreen.motion.y, &settingsButton);
                shutdownHover = isPointInsideButton(eventMainScreen.motion.x, eventMainScreen.motion.y, &shutdownButton);
            } else if (eventMainScreen.type == SDL_MOUSEBUTTONDOWN) {
                if (eventMainScreen.button.button == SDL_BUTTON_LEFT) {
                    if (isPointInsideButton(eventMainScreen.button.x, eventMainScreen.button.y, &playButton)) {
                        printf("Play button clicked!\n");
                        MapData mapData;
    initMap(&mapData);
    SDL_Surface *mask = IMG_Load("mask.png");
    if (!mask)
    {
        printf("Erreur lors du chargement de l'image du masque : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }
    int collisionFlag = 0;
    int running = 1;
     Button backButton = initializeButton(300, 90, SCREEN_WIDTH - 300 - 20, SCREEN_HEIGHT - 90 - 20, "back.png", "back1.png");
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                if (!collisionFlag)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        mapData.playerPosition.y -= 5;
                        if (collisionPP(mapData.playerPosition, mask))
                        {
                            printf("Collision detected\n");
                            collisionFlag = 1;
                        }
                        break;
                    case SDLK_DOWN:
                        mapData.playerPosition.y += 5;
                        if (collisionPP(mapData.playerPosition, mask))
                        {
                            printf("Collision detected\n");
                            collisionFlag = 1;
                        }
                        break;
                    case SDLK_LEFT:
                        mapData.playerPosition.x -= 5;
                        if (collisionPP(mapData.playerPosition, mask))
                        {
                            printf("Collision detected\n");
                            collisionFlag = 1;
                        }
                        break;
                    case SDLK_RIGHT:
                        mapData.playerPosition.x += 5;
                        if (collisionPP(mapData.playerPosition, mask))
                        {
                            printf("Collision detected\n");
                            collisionFlag = 1;
                        }
                        break;
                    case SDLK_s:
                        sauvegarder((Person){mapData.playerPosition.x, mapData.playerPosition.y, 100}, (Background){1}, "savegame.dat");
                        printf("Game saved.\n");
                        break;
                    case SDLK_l:
                        Person player;
charger(&player, &(Background){0}, "savegame.dat");
                        printf("Game loaded.\n");
                        break;
                    default:
                        break;
                    }
                }
                break;
            }
        }
        MAJMinimap(mapData.playerPosition, &mapData, (SDL_Rect){0, 0, 0, 0}, REDUCTION_MINIMAP);
        afficherMap(mapData, screen, font);
        SDL_Flip(screen);
        animerMinimap(&mapData, 7, 30);
        if (collisionFlag)
        {
            handleCollisionWindow(screen, &collisionFlag);
        }
    }
                      
                        
                        SDL_FreeSurface(backButton.image);
                        SDL_FreeSurface(backButton.imageHover);
                        mainScreenMusicPlaying = true;
                        Mix_PlayMusic(backgroundMusic, -1);
                        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
                        SDL_BlitSurface(backgroundImage, NULL, screen, NULL);
                        drawButton(screen, &playButton, playHover);
                        drawButton(screen, &settingsButton, settingsHover);
                        drawButton(screen, &shutdownButton, shutdownHover);
                        SDL_Flip(screen);
                    } else if (isPointInsideButton(eventMainScreen.button.x, eventMainScreen.button.y, &shutdownButton)) {
                        printf("Shutdown button clicked!\n");
                        quitMainScreen = true;
                    } else if (isPointInsideButton(eventMainScreen.button.x, eventMainScreen.button.y, &settingsButton)) {
                        Mix_HaltMusic();
                        bool quitOptionsScreen = false;
                        SDL_Event eventOptionsScreen;
                        SDL_Surface* screenOptions = createVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
                        Mix_Music* backgroundMusicOptions = loadMusic("music.mp3");
                        Mix_PlayMusic(backgroundMusicOptions, -1);
                        SDL_Surface* optionsScreenImage = loadImage("bg_option.jpg");
                        if (optionsScreenImage == NULL) {
                            printf("IMG_Load Error (bg2.png): %s\n", IMG_GetError());
                            Mix_FreeMusic(backgroundMusic);
                            Mix_FreeMusic(backgroundMusicOptions);
                            SDL_FreeSurface(backgroundImage);
                            SDL_Quit();
                            return 1;
                        }
bool volumeUpHover = false;
bool volumeDownHover = false;
bool backButtonHover = false;
bool fullscreenButtonHover = false;
Button volumeUpButton = initializeButton(100, 50, 50, 50, "plus.png", "plus1.png");
Button volumeDownButton = initializeButton(100, 50, 50, 180, "moins.png", "moins1.png");
Button backButton = initializeButton(100, 50, 700, 550, "back.png", "back1.png");
Button fullscreenButton = initializeButton(100, 50, 50, 390, "fullscreen.png", "fullscreen1.png");
    while (!quitOptionsScreen) {
        while (SDL_PollEvent(&eventOptionsScreen)) {
            if (eventOptionsScreen.type == SDL_MOUSEBUTTONDOWN) {
                if (eventOptionsScreen.button.button == SDL_BUTTON_LEFT) {
                    if (isPointInsideButton(eventOptionsScreen.button.x, eventOptionsScreen.button.y, &volumeUpButton)) {
                        printf("Volume Up button clicked!\n");
                        increaseVolume();
                    } else if (isPointInsideButton(eventOptionsScreen.button.x, eventOptionsScreen.button.y, &volumeDownButton)) {
                        printf("Volume Down button clicked!\n");
                        decreaseVolume();
                    } else if (isPointInsideButton(eventOptionsScreen.button.x, eventOptionsScreen.button.y, &backButton)) {
                        Mix_HaltMusic();
                        quitOptionsScreen = true;
                    } else if (isPointInsideButton(eventOptionsScreen.button.x, eventOptionsScreen.button.y, &fullscreenButton)) {
                        SDL_WM_ToggleFullScreen(screenOptions);
                    }
                }
            } else if (eventOptionsScreen.type == SDL_MOUSEMOTION) {
                volumeUpHover = isPointInsideButton(eventOptionsScreen.motion.x, eventOptionsScreen.motion.y, &volumeUpButton);
                volumeDownHover = isPointInsideButton(eventOptionsScreen.motion.x, eventOptionsScreen.motion.y, &volumeDownButton);
                backButtonHover = isPointInsideButton(eventOptionsScreen.motion.x, eventOptionsScreen.motion.y, &backButton);
                fullscreenButtonHover = isPointInsideButton(eventOptionsScreen.motion.x, eventOptionsScreen.motion.y, &fullscreenButton);
            } else if (eventOptionsScreen.type == SDL_KEYDOWN) {
                switch (eventOptionsScreen.key.keysym.sym) {
                    case SDLK_UP:
                        printf("Volume Up key pressed!\n");
                        increaseVolume();
                        break;
                         case SDLK_DOWN:
                        printf("Volume Down key pressed!\n");
                        decreaseVolume();
                        break;
                        case SDLK_ESCAPE:
                        Mix_HaltMusic();
                        quitOptionsScreen = true;
                        break;
                        case SDLK_f:
                        SDL_WM_ToggleFullScreen(screenOptions);
                        break;
                         default:
                        break;
                }
            }
        }
        SDL_FillRect(screenOptions, NULL, SDL_MapRGB(screenOptions->format, 0, 0, 0));
        SDL_BlitSurface(optionsScreenImage, NULL, screenOptions, NULL);
        drawButton(screenOptions, &volumeUpButton, volumeUpHover);
        drawButton(screenOptions, &volumeDownButton, volumeDownHover);
        drawButton(screenOptions, &backButton, backButtonHover);
        drawButton(screenOptions, &fullscreenButton, fullscreenButtonHover);
        SDL_Flip(screenOptions);
    }
                        SDL_FreeSurface(optionsScreenImage);
                        SDL_FreeSurface(backButton.image);
                        SDL_FreeSurface(backButton.imageHover);
                        Mix_FreeMusic(backgroundMusicOptions);
                        mainScreenMusicPlaying = true;
                        Mix_PlayMusic(backgroundMusic, -1);
                        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
                        SDL_BlitSurface(backgroundImage, NULL, screen, NULL);
                        drawButton(screen, &playButton, playHover);
                        drawButton(screen, &settingsButton, settingsHover);
                        drawButton(screen, &shutdownButton, shutdownHover);
                        SDL_Flip(screen);
                    }
                }
            } else if (eventMainScreen.type == SDL_KEYDOWN) {
                switch (eventMainScreen.key.keysym.sym) {
                    case SDLK_p:
                        printf("Key 'p' pressed: Opening second screen!\n");
                        Mix_HaltMusic();
                        bool quitSecondScreen = false;
                        SDL_Event eventSecondScreen;
                       SDL_Surface* screen2 = createVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
                        Mix_Music* backgroundMusic2 = loadMusic("music2.mp3");Mix_PlayMusic(backgroundMusic2, -1);
                        SDL_Surface* secondScreenImage = loadImage("bg_gameMenu.jpg");
                        if (secondScreenImage == NULL) {
                            printf("IMG_Load Error (bg1.png): %s\n", IMG_GetError());
                            Mix_FreeMusic(backgroundMusic);
                            Mix_FreeMusic(backgroundMusic2);
                            SDL_FreeSurface(backgroundImage);
                            SDL_Quit();
                            return 1;
                        }
                         Button backButton = initializeButton(300, 90, SCREEN_WIDTH - 300 - 20, SCREEN_HEIGHT - 90 - 20, "back.png", "back1.png");
                         while (!quitSecondScreen) {
                            while (SDL_PollEvent(&eventSecondScreen)) {
                                if (eventSecondScreen.type == SDL_MOUSEBUTTONDOWN && eventSecondScreen.button.button == SDL_BUTTON_LEFT) {
                                    if (isPointInsideButton(eventSecondScreen.button.x, eventSecondScreen.button.y, &backButton)) {
                                        Mix_HaltMusic();
                                        quitSecondScreen = true;
                                    }
                                }
                            }
                            SDL_FillRect(screen2, NULL, SDL_MapRGB(screen2->format, 0, 0, 0));
                            SDL_BlitSurface(secondScreenImage, NULL, screen2, NULL);
                        drawButton(screen2, &backButton, isPointInsideButton(eventSecondScreen.motion.x, eventSecondScreen.motion.y, &backButton));
                            SDL_Flip(screen2);
                        }
                        SDL_FreeSurface(secondScreenImage);
                        SDL_FreeSurface(backButton.image);
                        SDL_FreeSurface(backButton.imageHover);
                        Mix_FreeMusic(backgroundMusic2);
                        mainScreenMusicPlaying = true;
                        Mix_PlayMusic(backgroundMusic, -1);
                        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
                        SDL_BlitSurface(backgroundImage, NULL, screen, NULL);
                        drawButton(screen, &playButton, playHover);
                        drawButton(screen, &settingsButton, settingsHover);
                        drawButton(screen, &shutdownButton, shutdownHover);
                        SDL_Flip(screen);
                        break;
                        case SDLK_s:
                        printf("Key 's' pressed: Stopping music on the main screen!\n");
                        Mix_HaltMusic();
                        mainScreenMusicPlaying = false;
                        break;
                       case SDLK_r:
                        printf("Key 'r' pressed: Resuming music on the main screen!\n");
                        if (!mainScreenMusicPlaying) {
                            Mix_PlayMusic(backgroundMusic, -1);
                            mainScreenMusicPlaying = true;
                        }
                        break;

                    default:
                        break;
                }
            }
        }
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_BlitSurface(backgroundImage, NULL, screen, NULL);
    drawButton(screen, &playButton, playHover);
    drawButton(screen, &settingsButton, settingsHover);
    drawButton(screen, &shutdownButton, shutdownHover);
    SDL_Rect frameRect;
    frameRect.w = animationFrames[currentFrame]->w;
    frameRect.h = animationFrames[currentFrame]->h;
    frameRect.x = 0;  // Set X-coordinate to 0
    frameRect.y = 0;  // Set Y-coordinate to 0
    SDL_BlitSurface(animationFrames[currentFrame], NULL, screen, &frameRect);
    SDL_Flip(screen);
    SDL_Delay(frameDuration);
    currentFrame = (currentFrame + 1) % 3;
}
for (int i = 0; i < 3; ++i) {
    SDL_FreeSurface(animationFrames[i]);
}
    SDL_FreeSurface(backgroundImage);
    SDL_FreeSurface(playButton.image);
    SDL_FreeSurface(playButton.imageHover);
    SDL_FreeSurface(settingsButton.image);
    SDL_FreeSurface(settingsButton.imageHover);
    SDL_FreeSurface(shutdownButton.image);
    SDL_FreeSurface(shutdownButton.imageHover);
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

