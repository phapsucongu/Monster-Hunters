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
void draw::nextframe()
{
    if(action==1)
    {
        cc_rect.y=48*6-5;
        cc_rect.x+=48;
        if(cc_rect.x>=4*48)
        {
            action=0;
            cc_rect.y=0;
            cc_rect.x=0;
        }
        //cout<<cc_rect.x<<" "<<cc_rect.y<<endl;
        return ;
    }
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
void draw::left(enemy &slime, enemy &ghost)
{
    for(int i=0;i<=e_num;i++)
    {
        if(slime.check[i])
        {
            slime.printf[i].x+=step;
        }
        if(ghost.check[i])
        {
            slime.printf[i].x+=step;
        }
    }
    movex--;
    if(movex<=-5)
    {
        movex=-1;
        movey=-1;
        nextframe();
    }
}
void draw::right(enemy &slime, enemy &ghost)
{
    for(int i=0;i<=e_num;i++)
    {
        if(slime.check[i])
        {
            slime.printf[i].x-=step;
        }
        if(ghost.check[i])
        {
            slime.printf[i].x-=step;
        }
    }
    movex++;
    if(movex>=5)
    {
        movex=1;
        movey=1;
        nextframe();
    }
}
void draw::up(enemy &slime, enemy &ghost)
{
    for(int i=0;i<=e_num;i++)
    {
        if(slime.check[i])
        {
            slime.printf[i].y+=step;
        }
        if(ghost.check[i])
        {
            slime.printf[i].y+=step;
        }
    }
    movey--;
    if(movey<=-5)
    {
        movex=movex/abs(movex);
        movey=-1;
        nextframe();
    }
}
void draw::down(enemy &slime, enemy &ghost)
{
    for(int i=0;i<=e_num;i++)
    {
        if(slime.check[i])
        {
            slime.printf[i].y-=step;
        }
        if(ghost.check[i])
        {
            slime.printf[i].y-=step;
        }
    }
    movey++;
    if(movey>=5)
    {
        movex=movex/abs(movex);
        movey=1;
        nextframe();
    }
}


