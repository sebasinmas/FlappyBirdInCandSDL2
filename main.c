#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#include"modules/initAndViews.h"
#include"modules/physicsAndCollissions.h"
#include"modules/player.h"
#include"modules/pipes.h"
// Flappy bird in SDL2 version




int main(int argc, char const *argv[])
{
    const unsigned int FPS= 60;
    int SCREEN_WIDTH=640;
    int SCREEN_HEIGHT=480;
    short quit=0;
    enum view {menu, game};
    unsigned short view=menu;
    bool pause=true;
    //Initializating libraries
    if(init() == -1)
    {
        printf("Error initializing SDL2\n");
        return -1;
    }
    //Setup the window
    SDL_Window *gWindow = NULL;
    gWindow = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    //Setup the renderer
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        printf("Error creating renderer\n");
        return -1;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);


    //Setting up sounds
    Mix_Chunk *crash=NULL;
    crash = Mix_LoadWAV("assets/crash.mp3");
    if (crash == NULL)
    {
        printf("Error loading crash.mp3\n");
    } 

    //Setup the textures
    SDL_Surface *gBackgroundSurface = NULL;
    SDL_Texture *gBackgroundTexture = NULL;
    gBackgroundSurface = IMG_Load("assets/menuBackground.jpg");
    gBackgroundTexture = SDL_CreateTextureFromSurface(renderer, gBackgroundSurface);
    SDL_FreeSurface(gBackgroundSurface);

    SDL_Surface *gBackgroundSurface2 = NULL;
    SDL_Texture *gBackgroundTexture2 = NULL;
    gBackgroundSurface2 = IMG_Load("assets/background.png");
    gBackgroundTexture2 = SDL_CreateTextureFromSurface(renderer, gBackgroundSurface2);
    SDL_FreeSurface(gBackgroundSurface2);

    SDL_Surface *gBirdSurface = NULL;
    SDL_Texture *gBirdTexture = NULL;
    gBirdSurface = IMG_Load("assets/player.png");
    gBirdTexture = SDL_CreateTextureFromSurface(renderer, gBirdSurface);
    SDL_FreeSurface(gBirdSurface);

    SDL_Event e;
    SDL_Rect birdRect;
    birdRect.x = 100; //My image has 28 dead pixels on the left
    birdRect.y = 200; //My domain is [-52 , 372]
    birdRect.w = 150;
    birdRect.h = 150;

    Player player;
    initPlayer(&player,gBirdTexture,&birdRect);
    //Setup the font
    TTF_Font *gFont = NULL;
    gFont = TTF_OpenFont("assets/font.ttf", 28);

    //game loop
    while(quit == 0)
    {   
            if(view == menu)
            {   
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = 1;
                    }                
                    if(e.type == SDL_KEYDOWN && e.key.repeat==0)
                    {
                        if(e.key.keysym.sym == SDLK_SPACE)
                        {
                            view = game;
                        }
                        if (e.key.keysym.sym == SDLK_ESCAPE)
          
                        {
                            quit = 1;
                        }
                        
                        
                    }
                    
                    
                }           
                
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, gBackgroundTexture, NULL, NULL);
                renderMenuAuto(renderer,gFont);
                SDL_RenderPresent(renderer);
            }
            if(view == game)
            {   //Controls
                GetJumpTime(&player);
                while (SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = 1;
                    }
                    if(e.type == SDL_KEYDOWN && e.key.repeat== 0)
                    {
                        if(e.key.keysym.sym == SDLK_SPACE)
                        {
                            if(pause == true){
                                pause = false;
                            }else{

                                if (player.isJumping == false){                                
                                    Jump(&player);
                                }
                                
                                
                            }
                        }

                        if (e.key.keysym.sym == SDLK_ESCAPE)
                        {
                            quit = 1;
                        }    


                    }
                    
                   
                }
                if (pause != true)
                {
                    Gravity(&player);
                }
                
                
                    
                
                
                
                
                //Render
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, gBackgroundTexture2, NULL, NULL);
                renderPlayer(renderer, &player);
                renderPause(renderer,gFont,pause);
                SDL_RenderPresent(renderer);
    
            }
                SDL_Delay(1000/FPS);
    }
    
    

    //Free resources and close SDL
    SDL_DestroyTexture(gBackgroundTexture);
    SDL_DestroyTexture(gBirdTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(gFont);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();

    
    SDL_Quit();

    return 0;
}
