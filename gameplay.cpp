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
void thanks_mau(SDL_Renderer* renderer,draw &game, SDL_Rect &mau,SDL_Rect &thanh_mau)
{
    if(game.movex > 0){
        mau.x=game.print.x+6;
        thanh_mau.x=game.print.x+5;
    }
    else{
        mau.x=game.print.x+19;
        thanh_mau.x=game.print.x+18;
    }
    mau.y=game.print.y+game.print.h-29;
    mau.h=4;
    mau.w=game.print.w*game.health/1000-20-10;
    thanh_mau.h=6;
    thanh_mau.y=game.print.y+game.print.h-30;
    thanh_mau.w=game.print.w-18-10;
    if(mau.w<0){
        mau.w = 0;
    }
    SDL_SetRenderDrawColor(renderer,255,255,255,0);
    SDL_RenderFillRect(renderer,&thanh_mau);
    SDL_SetRenderDrawColor(renderer,255,0,0,0);
    SDL_RenderFillRect(renderer,&mau);
    //cout<<thanh_mau.h<<" "<<thanh_mau.w<<" "<<thanh_mau.x<<" "<<thanh_mau.y<<endl;
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
}
void destroy(draw &nv,enemy &slime)
{
    int x_mid=nv.print.x;
    int y_mid=nv.print.y;
    for(int i=0;i<slime.num;i++)
    {
//        if(slime.printf[i].x >= x_mid - 15 && slime.printf[i].y <= y_mid +1 ){
//                nv.health = nv.health- 10;
//        }
        if(nv.movex>0)
        {
            if(slime.printf[i].x<=x_mid+range_attack
            &&slime.printf[i].x>=x_mid
            &&slime.printf[i].y<=y_mid+range_attack
            &&slime.printf[i].y>=y_mid-range_attack/3
            && nv.action ==1 && slime.check[i] == 1)
            {
                slime.printf[i]={0,0,0,0};
                slime.check[i]=2;
            }
        }
        else
        {
            if(slime.printf[i].x>=x_mid-range_attack
            &&slime.printf[i].x<=x_mid+range_attack/2
            &&slime.printf[i].y<=y_mid+range_attack
            &&slime.printf[i].y>=y_mid-range_attack/3
            &&nv.action ==1&& slime.check[i] == 1)
            {
                slime.printf[i]={0,0,0,0};
                slime.check[i]=2;
            }
        }
        if(slime.check[i]== 2){
            nv.score ++;
            slime.check[i] = 0;
        }
    }
}
void sword(enemy &slime, draw &game)
{
    game.action =1;
    game.cc_rect.x=0;
    destroy(game,slime);
}
void charmove(SDL_Event e, draw &game,int &sword_time,enemy &slime,enemy &ghost, enemy &ghost2)
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
            sword(slime,game);
            sword(ghost,game);
            sword(ghost2,game);
        }
    if (state[SDL_SCANCODE_LEFT])
    {
        if(game.print.x>=Left)
            game.left(slime,ghost,ghost2);
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        if(game.print.x<Right)
        {
            game.right(slime,ghost,ghost2);
        }
    }
    if (state[SDL_SCANCODE_UP])
    {
        if(game.print.y>Up)
            game.up(slime, ghost,ghost2);
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        if(game.print.y<Down)
            game.down(slime,ghost,ghost2);
    }
    if(SDL_PollEvent(&e))
        if(e.type==SDL_QUIT)
            exit(0);

}
