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
//int cnt_time, sword_time;
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


