#ifndef enemy_h_
#define enemy_h_
//#include "draw.h"
const int e_step=2;
static const int e_num=1000;
static int time_spawn =2000;
static int e_w=672,e_h=32;
class enemy
{
public :
    void spawn(SDL_Rect print,int i);
    void emove(SDL_Rect print,int &health);
    int x,y,num=0;
    SDL_Rect e_rect[e_num+1],printf[e_num+1];
    int check[e_num+1]={0};
    int e_vs_e(int i,int k);
    bool cmp(int a,int b);
    bool collision (SDL_Rect a,SDL_Rect b);
};
//class ghost: public enemy
#endif enemy_h_h;

