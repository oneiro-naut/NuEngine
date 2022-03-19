#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "Game.h"

int main(int argc, char* argv[])
{ 
  Game *game = new Game();  

  // the game loop
  while(game->isRunning()) {
    // get input 
    game->pollEvents();    
    
    // update game state
    game->update();
    
    // draw graphics
    game->draw();
  }  
  return 0;
}
