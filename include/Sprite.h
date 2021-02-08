#ifndef SPRITE_H
#define SPRITE_H
#include "SDL2/SDL.h"

/*
* speed is relative to game frame rate 
* sprite fps cant be greater than game frame rate
* speed = game_fps / sprite_fps
*/

class Sprite {
 public:
  Sprite(int n_frame, int n_loop, float FPS, float scale, SDL_Rect base, SDL_Texture* img, bool isanim);
  ~Sprite();
  SDL_Rect getCurrentFrame();
  SDL_Texture* getTexture();
  bool isOver() { return _OVER;}
  void update();
  //void draw();
  void stop();//will internally reset the curr animation state

 private:
  //SDL_RenderFlip FLIP;
  bool _isAnimated;
  bool _OVER;
  int FRAME_COUNT;
  //current frame
  int N_FRAMES;
  //total frames
  int COUNT;
  //loop count 
  int MAX_COUNT;
  //max no of loops -1 for indefinite
  float FPS;
  //animation speed NOTE: THIS WILL ONLY WORK TO SLOW DOWN THE ANIMATION COMPARED TO THE GAME FRAME RATE(60 in our case)
  Uint32 CLOCK;
  float scale;
  SDL_Rect BASE_FRAME;
  //base frame 
  SDL_Rect CUR_FRAME;
  //current frame
  SDL_Texture* IMG;
  //image to render

  //yes it can draw they have access to the global renderer 
  void resetTimer();
  void startTimer();
  void reset();
  void animate();
  void start();
  void updateFrame();
  void updateClock();
};
#endif