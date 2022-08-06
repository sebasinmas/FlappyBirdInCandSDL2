#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

bool init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }


   
    return true;
}
//Renders main menu screen
void renderMenuAuto(SDL_Renderer *renderer,TTF_Font *gFont){
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Color textColor = {255, 255, 255};
    SDL_Color textColor2 = {0, 0, 0};
    SDL_Surface *gSurfaceMessage = TTF_RenderText_Solid(gFont, "Press Space to Play", textColor);
    if (SDL_GetTicks() % 1000 < 500) {
        gSurfaceMessage = TTF_RenderText_Solid(gFont, "Press Space to Play", textColor2);
    }
    
    SDL_Texture *gMessage = SDL_CreateTextureFromSurface(renderer, gSurfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = SCREEN_WIDTH/2 - gSurfaceMessage->w/2;
    Message_rect.y = ((SCREEN_HEIGHT/2)-30) - gSurfaceMessage->h/2;
    Message_rect.w = gSurfaceMessage->w;
    Message_rect.h = gSurfaceMessage->h;
    SDL_RenderCopy(renderer, gMessage, NULL, &Message_rect);
    SDL_FreeSurface(gSurfaceMessage);
    SDL_DestroyTexture(gMessage);
}

void renderPause(SDL_Renderer *renderer,TTF_Font *gFont,bool pause){
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Color textColor = {255, 255, 255};
    SDL_Color textColor2 = {0, 0, 0};
    
    SDL_Surface *gSurfaceMessage = TTF_RenderText_Solid(gFont, "Press Space to Start", textColor);
    if (SDL_GetTicks() % 1000 < 500) {
        gSurfaceMessage = TTF_RenderText_Solid(gFont, "Press Space to Start", textColor2);
    }
    //Half transparent black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
 
    
    SDL_Texture *gMessage = SDL_CreateTextureFromSurface(renderer, gSurfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = SCREEN_WIDTH/2 - gSurfaceMessage->w/2;
    Message_rect.y = ((SCREEN_HEIGHT/2)-30) - gSurfaceMessage->h/2;
    Message_rect.w = gSurfaceMessage->w;
    Message_rect.h = gSurfaceMessage->h;
    if (pause == true) {
        SDL_RenderCopy(renderer, gMessage, NULL, &Message_rect);
    }
     SDL_FreeSurface(gSurfaceMessage);
    SDL_DestroyTexture(gMessage);
}
