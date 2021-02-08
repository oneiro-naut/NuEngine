#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <SDL2/SDL.h>

//Texture wrapper class
class TextureManager {
 public:
  //Initializes variables
  TextureManager();
  ~TextureManager();
  static SDL_Texture* loadFromFile(std::string path, SDL_Renderer* renderer);
};
#endif