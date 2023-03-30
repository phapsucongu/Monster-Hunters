#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "enemy.h"
//#include "draw.h"
#define fi first
#define se second
using namespace std;
SDL_Rect char_rect,enemy_rect[50];
void enemy::spawn(SDL_Rect print,int i)
{
    printf[i]={0,0,64,24};
    int x2=0,y2=0;
    while(1)
    {
        x2=rand()% 1200+40;
        y2=rand()% 700+10;
        if(x2!=print.x||y2!=print.y)
            if(abs(x2-print.x)>=50&&abs(y2-print.y)>=30&&(x2<=300||x2>=900)&&(y2<=200||y2>=500))
                break;
    }
    printf[i].x=x2;
    printf[i].y=y2;
    if(num<=e_num)
        num++;
    //num+=1;
    check[i]=1;
}
void enemy::emove(SDL_Rect print)
{
    for(int i=0;i<num;i++)
    {

        e_rect[i].x+=576/6;
        if(e_rect[i].x>=576)
            e_rect[i].x=0;
        //enemy_rect[i]=printf[i]
        if(1)
        {
            if(printf[i].x>=print.x&&e_vs_e(i,1))
            printf[i].x-=e_step;
            if(printf[i].x<=print.x&&e_vs_e(i,2))
            printf[i].x+=e_step;
            if(printf[i].y>=print.y+30&&e_vs_e(i,3))
                printf[i].y-=e_step/2;
            if(printf[i].y<=print.y+30&&e_vs_e(i,4))
                printf[i].y+=e_step/2;
        }
    }
}
int enemy::e_vs_e(int i,int k)
{
    //cout<<i<<" "<<k<<endl;
    if(k==1)
    {
        //if(printf[i].x-e_step-printf[j].x)
        for(int j=1;j<num;j++)
            if(j!=i&&abs(printf[i].x-e_step-printf[j].x)<=30&&abs(printf[i].y-printf[j].y)<=15)
                return 0;
    }
    if(k==2)
    {
        for(int j=1;j<num;j++)
            if(j!=i&&(abs(printf[i].x+e_step-printf[j].x)<=30)&&abs(printf[i].y-printf[j].y)<=15)
                return 0;
    }
    if(k==3)
    {
        for(int j=1;j<num;j++)
            if(j!=i&&abs(printf[i].y-e_step/2-printf[j].y)<=15&&abs(printf[i].x-printf[j].x)<=30)
                return 0;
    }
    if(k==4)
    {
        for(int j=1;j<num;j++)
            if(j!=i&&abs(printf[i].y+e_step/2-printf[j].y)<=15&&abs(printf[i].x-printf[j].x)<=30)
                return 0;
    }
    //cout<<" 1"<<endl;
    return 1;
}

int main()
{
    return 0;
}
