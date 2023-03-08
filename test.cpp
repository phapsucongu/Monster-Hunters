#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std ;
const Uint8* state = SDL_GetKeyboardState(NULL);
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
SDL_Window* gWindow =NULL;
SDL_Renderer* renderer=NULL;
SDL_Texture* bg=NULL;
bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ||IMG_Init(IMG_INIT_JPG) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    return success;
}

void event(SDL_Event e)
{
    SDL_PollEvent(&e);
    if(SDL_PollEvent(&e))
        if(e.type==SDL_QUIT)
            exit(0);
    if(e.type==SDL_MOUSEBUTTONDOWN)
    {
         bg=IMG_LoadTexture(renderer,"char.png");
        SDL_RenderCopy(renderer,bg,NULL,NULL);
    }
    if (state[SDL_SCANCODE_LEFT])
    {
         bg=IMG_LoadTexture(renderer,"blue_slime1.png");
        SDL_RenderCopy(renderer,bg,NULL,NULL);
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
         bg=IMG_LoadTexture(renderer,"blue_slime2.png");
        SDL_RenderCopy(renderer,bg,NULL,NULL);
    }
    if (state[SDL_SCANCODE_UP])
    {
         bg=IMG_LoadTexture(renderer,"blue_slime3.png");
        SDL_RenderCopy(renderer,bg,NULL,NULL);
    }
    if (state[SDL_SCANCODE_DOWN])
    {
         bg=IMG_LoadTexture(renderer,"blue_slime3.png");
        SDL_RenderCopy(renderer,bg,NULL,NULL);
    }
}
int main( int argc, char* args[] )
{
    init();
    renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* bgg=IMG_LoadTexture(renderer,"bgg.png");        SDL_Event e;
    SDL_RenderCopy(renderer,bgg,NULL,NULL);
    SDL_Rect rect={0,0,500,500};
    while(1)
    {
        SDL_RenderCopy(renderer,bgg,NULL,&rect);
        SDL_RenderCopy(renderer,bg,NULL,NULL);
        event(e);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        rect.x+=10;
        rect.y+=10;
        SDL_Delay(10);
    }

    return 0;
}
