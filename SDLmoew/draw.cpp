#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
using namespace std;


SDL_Window* gWindow = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect C_rect;
SDL_Texture* bg[12];

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

SDL_Surface* loadMedia(string path)
{
    SDL_Surface* image =IMG_Load(path.c_str());
    return image;
}

void loadrect(SDL_Surface* sur,SDL_Texture* tex,int x,int y)
{
    SDL_Rect dest = {x, y,sur->w,sur->h};
    SDL_RenderCopy(renderer, tex, NULL, &dest);
}

void charmove(SDL_Event e)
{
    SDL_PollEvent(&e);
    if (state[SDL_SCANCODE_LEFT])
    {
        print.x -= step;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        print.x += step;
    }
    if (state[SDL_SCANCODE_UP])
    {
        print.y -= step;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        print.y += step;
    }
    //if (!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN]) { idle(render); }
    if(SDL_PollEvent(&e))
        if(e.type==SDL_QUIT)
            exit(0);
}
void loadbg()
{
    for(int i=0;i<5;i++)
    {
        bg[i*2]=IMG_LoadTexture(renderer,bgname[i].c_str());
        bg[i*2+1]=IMG_LoadTexture(renderer,bgname[i].c_str());
    }
}
void bgmove()
{


}

int main( int argc, char* args[] )
{

    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        SDL_Texture* bgg =IMG_LoadTexture( renderer,"bg1.png");
        SDL_RenderCopy(renderer, bgg, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Texture* character =IMG_LoadTexture(renderer,"char.png");
        cout<<C_rect.h<<" "<<C_rect.w;
        SDL_QueryTexture(character,0,0,&C_rect.w,&C_rect.h);
        C_rect.w*=2;
        C_rect.h*=2;
        SDL_Event e;
        while(1)
        {
            SDL_RenderCopy(renderer, bgg, NULL, NULL);
            SDL_RenderCopy(renderer, character, &cc_rect,&print);
            SDL_RenderPresent(renderer);
            cc_rect.x+=48;
            if(cc_rect.x>48*5)
            {
                cc_rect.x=0;
                cc_rect.y+=48;
            }
            cout<< cc_rect.x<< " "<< cc_rect.y<<" "<<C_rect.w<<" "<<endl;
            if(cc_rect.y>=48*1&&cc_rect.x>=48*5)
            {
                cc_rect.x=0;
                cc_rect.y=0;
            }
            charmove(e);
            SDL_Delay(5);
            SDL_RenderClear(renderer);
        }


    }

    return 0;
}

