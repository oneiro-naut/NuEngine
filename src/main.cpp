#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "Game.h"

int main(int argc,char* argv[]) { 
  Game *game = new Game();  

  // frame rate = 60 fps
  const float FPS = 1000 / 60;
  Uint32 timer;
  Uint32 start_time;
  Uint32 delay;
  // the game loop
  while(game->isRunning()) {
    start_time = SDL_GetTicks();
    
    // get input 
    game->pollEvents();    
    
    // update game state
    game->update();
    
    // draw graphics
    game->draw();
    
    timer = SDL_GetTicks();
    delay = timer - start_time;
    if (delay < FPS) {
      SDL_Delay(FPS - delay);
    }
  }  
  return 0;
}