#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
#include "enemy.h"
#include "gameplay.h"
using namespace std;
const Uint8* state = SDL_GetKeyboardState(NULL);
void destroy(draw &nv,enemy &slime)
{
    int x_mid=nv.print.x;
    int y_mid=nv.print.y;
    for(int i=0;i<slime.num;i++)
    {
        if(nv.movex>0)
        {
            if(slime.printf[i].x<=x_mid+range_attack
            &&slime.printf[i].x>=x_mid
            &&slime.printf[i].y<=y_mid+range_attack
            &&slime.printf[i].y>=y_mid-range_attack/3)
            {
                slime.printf[i]={0,0,0,0};
                slime.check[i]=0;
            }
        }
        else
        {
            if(slime.printf[i].x>=x_mid-range_attack
            &&slime.printf[i].x<=x_mid+range_attack/2
            &&slime.printf[i].y<=y_mid+range_attack
            &&slime.printf[i].y>=y_mid-range_attack/3)
            {
                slime.printf[i]={0,0,0,0};
                slime.check[i]=0;
            }
        }
    }
    cout<<nv.movex;
}
void sword(enemy &slime, draw &game)
{
    game.action =1;
    game.cc_rect.x=0;
    destroy(game,slime);
}
void charmove(SDL_Event e, draw &game,int &sword_time,enemy &slime,enemy &ghost)
{
    SDL_PollEvent(&e);
    if(game.action==1)
    {
        game.nextframe();
        return ;
    }
    if(sword_time<clock()-500)
        if(e.type==SDL_MOUSEBUTTONDOWN)
        {
            sword_time=clock();
            sword(slime , game);
            sword(ghost,game);
        }
    if (state[SDL_SCANCODE_LEFT])
    {
        if(game.print.x>=Left)
            game.left(slime,ghost);
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        if(game.print.x<Right)
        {
            game.right(slime,ghost);
        }
    }
    if (state[SDL_SCANCODE_UP])
    {
        if(game.print.y>Up)
            game.up(slime, ghost);
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        if(game.print.y<Down)
            game.down(slime,ghost);
    }
    if(SDL_PollEvent(&e))
        if(e.type==SDL_QUIT)
            exit(0);

}

void collision (draw &nv, enemy &slime)
{
    for(int i=1;i<=slime.num;i++);
}
