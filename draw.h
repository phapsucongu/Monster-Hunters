#ifndef draw_h_
#define draw_h_
#include "enemy.h"
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int Up=135;
const int Down=540;
const int Left=-40;
const int Right=1200;
//const std::string bgname[6]={"bg1.png","bg2.png","bg3.png","bg4.png","bg5.png","bg6.png"};
const int step = 3;
bool init();
class draw
{
public :
    void bgmove();
    void left();
    void right();
    void up();
    void down();
    void sit();
    void nextframe();
    void charmove(SDL_Event e);
    SDL_Rect cc_rect={0,0,55,55},print={640,360,96,96};
    int movex =1,movey=1;
    int action =0;
    int health =10;
};

#endif draw_h_h;
