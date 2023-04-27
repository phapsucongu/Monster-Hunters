#ifndef draw_h_
#define draw_h_
#include "enemy.h"
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int step = 5;
bool init();
class draw
{
public :
    void left(enemy &slime, enemy &ghost,enemy &ghost2);
    void right(enemy &slime, enemy &ghost,enemy &ghost2);
    void up(enemy &slime, enemy &ghost,enemy &ghost2);
    void down(enemy &slime, enemy &ghost,enemy &ghost2);
    void die();
    void nextframe();
    void reset();
    SDL_Rect cc_rect={0,0,55,55},print={640,360,96,96};
    int movex =1,movey=1;
    int action =0;
    double health =50;
    int score = 0;
    int play =0;
    int t=100;
};

#endif draw_h_h;
