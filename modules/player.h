#include <stdbool.h>
#include <SDL2/SDL.h>
typedef struct{
    SDL_Texture *birdTexture;
    SDL_Rect *bird;
    double gravity;
    int Ypos;
    bool isJumping;
    double acceleration;
    double acceleration2;
    double jumpHeight;
    double lastJump;
    double jumpTimer;
    int animationTimer;
    
}Player;

bool initPlayer(Player *player,SDL_Texture *texture,SDL_Rect*rect){
    player->birdTexture = texture;
    player->bird = rect;
    player->gravity = 0.2;
    player->isJumping = false;
    player->acceleration = 0;
    player->acceleration2 = 0;
    player->animationTimer;
    player->Ypos = player->bird->y;
    player->jumpHeight = -6;
    player->lastJump = 0;
   
    return true;
}
void Gravity(Player *player);
void GetJumpTime(Player *player);
void Jump(Player *player);
bool JumpState(Player *player);
void renderPlayer(SDL_Renderer *renderer,Player *player); 
void UpdatePlayer(Player *player);





void Gravity(Player *player){
    
    if (player->isJumping== true)
    {        
        player->acceleration += 0.035; //Increments acceleration1
        player->acceleration2 += 0.035; //Increments acceleration2
        player->jumpHeight += player->gravity;
        player->Ypos += player->gravity + player->acceleration + player->acceleration2 +player->jumpHeight;
        UpdatePlayer(player);
        if (player->jumpHeight > 0)
        {
            player->isJumping = false;
            player->jumpHeight = -6;
           
        }
    }else{
        player->acceleration += 0.035; //Increments acceleration1
        player->acceleration2 += 0.035; //Increments acceleration2
        player->Ypos += player->gravity + player->acceleration + player->acceleration2;

        UpdatePlayer(player);
    }
}

void GetJumpTime(Player *player){
    player->jumpTimer = SDL_GetTicks();
}



void Jump(Player *player){
    if(player->jumpTimer - player->lastJump > 180){
        player->acceleration = 0;
        player->acceleration2 = 0;
        player->isJumping = true;
        player->lastJump = player->jumpTimer;

        
    }else{
        Gravity(player);
    }
}


void UpdatePlayer(Player *player){
    player->bird->y = player->Ypos;
}
void renderPlayer(SDL_Renderer *renderer, Player *player){

    SDL_RenderCopy(renderer,player->birdTexture,NULL,player->bird);
}