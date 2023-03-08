#ifndef draw_h_
#define draw_h_
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int Up=135;
const int Down=540;
const int Left=-40;
const int Right=1200;
//const std::string bgname[6]={"bg1.png","bg2.png","bg3.png","bg4.png","bg5.png","bg6.png"};
const int step = 2;
bool init();
class draw
{
public :
    bool init();
    //SDL_Surface* loadMedia(std::string path);
    void bgmove();
    void left();
    void right();
    void up();
    void down();
    void sit();
    void nextframe();
//private :
    SDL_Rect cc_rect={0,0,55,55},print={640,360,144,144};
    int movex =1,movey=1;
    void sword();

};

#endif draw_h_h;
