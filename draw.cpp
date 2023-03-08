#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
#include "enemy.h"
#include "gameplay.h"
#include <ctime>
using namespace std;
const Uint8* state = SDL_GetKeyboardState(NULL);
SDL_Window* gWindow = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect C_rect;
SDL_Texture* character;
SDL_Texture* bgg;
SDL_Texture* e_slime=NULL;
draw game;
enemy slime;
int cnt_time, sword_time;
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

void draw::nextframe()
{
    cc_rect.x+=48;
    if(cc_rect.x>48*5)
    {
        cc_rect.x=0;
        cc_rect.y+=48;
    }
    //cout<< cc_rect.x<< " "<< cc_rect.y<<" "<<C_rect.w<<" "<<endl;
    if(cc_rect.y>=48*1&&cc_rect.x>=48*5)
    {
        cc_rect.x=0;
        cc_rect.y=0;
    }
}
void draw::left()
{
    print.x -=step;
    movex--;
    if(movex<=-5)
    {
        movex=-1;
        movey=-1;
        nextframe();
    }
}
void draw::right()
{
    print.x +=step;
    movex++;
    if(movex>=5)
    {
        movex=1;
        movey=1;
        nextframe();
    }
}
void draw::up()
{
    print.y -=step;
    movey--;
    if(movey<=-5)
    {
        movex=movex/abs(movex);
        movey=-1;
        nextframe();
    }
}
void draw::down()
{
    print.y +=step;
    movey++;
    if(movey>=5)
    {
        movex=movex/abs(movex);
        movey=1;
        nextframe();
    }
}
void draw::sword()
{
    sword_time=1;
    SDL_Rect act= {0,48*6,50,50};
    for(int i=1; i<=5; i++)
    {
        for(int k=1;k<=3;k++)
        {
            SDL_RenderCopy(renderer, bgg, NULL, NULL);
            for(int j=0; j<9; j++)
            {
                SDL_RenderCopy(renderer, e_slime, &slime.e_rect[j],&slime.printf[j]);
                slime.e_rect[j].x+=C_rect.w/6;
                if(slime.e_rect[j].x>=C_rect.w)
                    slime.e_rect[j].x=0;
            }
            SDL_Delay(10);
            if(game.movex>0)
            SDL_RenderCopy(renderer, character, &act,&game.print);
            else
                SDL_RenderCopyEx( renderer,character, &act, &game.print, 0, NULL, SDL_FLIP_HORIZONTAL);
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            slime.emove(game,i);
        }
        act.x+=48;

    }
    destroy(game,slime);
}
void charmove(SDL_Event e)
{
    SDL_PollEvent(&e);
    if(e.type==SDL_MOUSEBUTTONDOWN&&sword_time==0)
    {
        game.sword();
        sword_time=0;
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        if(game.print.x>=Left)
            game.left();
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        if(game.print.x<Right)
        {
            game.right();
        }
    }
    if (state[SDL_SCANCODE_UP])
    {
        if(game.print.y>Up)
            game.up();
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        if(game.print.y<Down)
            game.down();
    }
    if(SDL_PollEvent(&e))
        if(e.type==SDL_QUIT)
            exit(0);
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
        bgg =IMG_LoadTexture( renderer,"bgg.png");
        character =IMG_LoadTexture(renderer,"char.png");
        e_slime =IMG_LoadTexture(renderer,"blue_slime3.png");
        SDL_QueryTexture(e_slime,0,0,&C_rect.w,&C_rect.h);
        SDL_Event e;
        //cout<<C_rect.h<<" "<<C_rect.w;
        for(int i=0; i<10; i++)
        {
            slime.e_rect[i]= {0,0,C_rect.w/6,C_rect.h};
        }
        while(1)
        {
            SDL_RenderCopy(renderer, bgg, NULL, NULL);
            if(game.movex>0)
                SDL_RenderCopy(renderer, character, &game.cc_rect,&game.print);
            else
                SDL_RenderCopyEx( renderer,character, &game.cc_rect, &game.print, 0, NULL, SDL_FLIP_HORIZONTAL);
            if(clock()%40==0)
            {
                for(int i=0; i<=9; i++)
                {
                    if(slime.check[i]==0)
                    {
                        slime.spawn(game,i);
                        break;
                    }
                }
            }
            if(clock()%5==0)
            {
                for(int i=0; i<slime.num; i++)
                {
                    slime.e_rect[i].x+=C_rect.w/6;
                    if(slime.e_rect[i].x>=C_rect.w)
                        slime.e_rect[i].x=0;
                }
                    for(int i=0; i<slime.num; i++)
                        slime.emove(game,i);
            }
            for(int i=0; i<slime.num; i++)
                SDL_RenderCopy(renderer, e_slime, &slime.e_rect[i],&slime.printf[i]);
            SDL_RenderPresent(renderer);
            charmove(e);
            SDL_Delay(10);
            SDL_RenderClear(renderer);
            cnt_time++;
            //cout << clock() << " " << cnt_time << endl;
        }
    }

    return 0;
}

