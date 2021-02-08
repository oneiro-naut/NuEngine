#include <iostream>
#include <SDL2/SDL_image.h>

#include "TextureManager.h"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {
}

SDL_Texture* TextureManager::loadFromFile(std::string path, SDL_Renderer* renderer) {
  const char* image = path.c_str();
  SDL_Surface* surface = NULL;
  SDL_Texture* texture = NULL;
  surface = IMG_Load(image);
  if (surface == NULL) {
    //fprintf(stderr, "[%s: %d]Warning: Could not load image %s into surface, error: %s\n", __FILE__, __LINE__, image, SDL_GetError());
    return NULL;
  }
  if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x0, 0x0, 0x0))) {
    //fprintf(stderr, "[%s: %d]Warning: Could not set color key for image %s, error: %s\n", __FILE__, __LINE__, image, SDL_GetError());
    return NULL;
  }
  texture = SDL_CreateTextureFromSurface(renderer, surface);  
  SDL_FreeSurface(surface);
  if (!texture)
    std::cerr << "Couldn't create texture.\n";
  return texture;
}