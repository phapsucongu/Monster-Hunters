#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
#include "enemy.h"
#include "gameplay.h"
using namespace std;
void destroy(draw nv,enemy &slime)
{
    //int x_mid=nv.print.x+nv.print.w/2;
    //int y_mid=nv.print.y+nv.print.h/2;
    int x_mid=nv.print.x;
    int y_mid=nv.print.y;
    for(int i=0;i<slime.num;i++)
    {
        if(nv.movex>0)
        {
            if(slime.printf[i].x<=x_mid+range_attack*3/2
            &&slime.printf[i].x>=x_mid
            &&slime.printf[i].y<=y_mid+range_attack
            &&slime.printf[i].y>=y_mid-range_attack)
            {
                slime.printf[i]={0,0,0,0};
                slime.check[i]=0;
                break;
            }
        }
        else
        {
            if(slime.printf[i].x>=x_mid-range_attack*3/2
            &&slime.printf[i].x<=x_mid+range_attack
            &&slime.printf[i].y<=y_mid+range_attack
            &&slime.printf[i].y>=y_mid-range_attack)
            {
                slime.printf[i]={0,0,0,0};
                slime.check[i]=0;
                break;
            }
        }
    }
}

