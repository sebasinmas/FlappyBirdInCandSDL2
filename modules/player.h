#include <stdbool.h>
#include <SDL2/SDL.h>
typedef struct{
    SDL_Texture *birdTexture;
    SDL_Rect *bird;
    double gravity;
    double Ypos;
    bool isJumping;
    double acceleration;
    double acceleration2;
    int animationTimer;
    
}Player;

bool initPlayer(Player *player,SDL_Texture *texture,SDL_Rect*rect){
    player->birdTexture = texture;
    player->bird = rect;
    player->gravity = 0.2;
    player->isJumping = false;
    player->acceleration = 0;
    player->acceleration2 = 0;
    player->animationTimer = 1;


    return true;
}

void gravity(Player *player){
    if(player->isJumping == false){
        player->acceleration += player->gravity;
        player->Ypos += player->acceleration;
    }
}



void renderPlayer(SDL_Renderer *renderer, Player *player){
    SDL_RenderCopy(renderer,player->birdTexture,NULL,player->bird);
}