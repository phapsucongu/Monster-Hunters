#ifndef draw_h_
#define draw_h_
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const Uint8* state = SDL_GetKeyboardState(NULL);
const std::string bgname[6]={"bg1.png","bg2.png","bg3.png","bg4.png","bg5.png","bg6.png"};
const int step = 1;
SDL_Rect cc_rect={0,0,55,55},print={0,400,192,192};
//SDL_Rect print=(0,400,192,192);
bool init();
    SDL_Surface* loadMedia(std::string path);
    void loadrect(SDL_Surface sur,SDL_Texture tex,int x,int y);
    void bgmove();
    void jump();
    void left();
    void right();
    void sit();
class draw
{
public :

private :

};

#endif draw_h_h;
