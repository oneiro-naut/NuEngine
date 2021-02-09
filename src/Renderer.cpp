#include <iostream>

#include "Renderer.h"
#include "Rectangle.h"

//who will call the constructor tho i think from the Game class idk
Renderer::Renderer(SDL_Window* win): _pwin(win) {
  createRenderer();
  //call it man
}

//can add options here this will be the default tho
void Renderer::createRenderer() { 
  _renderer= SDL_CreateRenderer(_pwin, -1, SDL_RENDERER_ACCELERATED);
  if (_renderer == nullptr) {
      std::cerr << "Failed to create renderer\n";
      return;
  }
  std::cout << "Created Renderer...\n";
}

bool Renderer::initComplete() const {
  return !(_renderer == nullptr);
}

void Renderer::renderTexture(SDL_Texture* texture, SDL_Rect srcrect, SDL_Rect drect, double angle, SDL_Point* center, SDL_RendererFlip flip) {
  if (SDL_RenderCopyEx(this->_renderer, texture, &srcrect, &drect, angle, center, flip))
    fprintf(stderr, "[%s: %d]Warning: Could not render copy, error: %s\n",__FILE__, __LINE__, SDL_GetError());
}

void Renderer::renderTexture(SDL_Texture* texture, int x, int y) {
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  SDL_Rect drect = {x, y, w, h};
  if (SDL_RenderCopyEx(this->_renderer, texture, NULL, &drect, 0.0, NULL, SDL_FLIP_NONE));
    fprintf(stderr, "[%s: %d]Warning: Could not render copy, error: %s\n",__FILE__, __LINE__, SDL_GetError());  
}

void Renderer::addColor(std::string colorname, SDL_Color color) {
  if (color_map.find(colorname) == color_map.end())
    color_map.insert(std::make_pair(colorname, color));
}

void Renderer::renderSprite(Sprite* sprite, float x, float y, float scale, double angle, SDL_Point* center, SDL_RendererFlip flip) {
  //get current frame to render == get source rectangle and image
  SDL_Rect frame = sprite->getCurrentFrame();
  SDL_Texture* src_img = sprite->getTexture();
  //get destination 
  SDL_Rect drect = getDestinationRect(x,y,frame.w,frame.h,scale);
  renderTexture(src_img, frame, drect, angle, center, flip);
  //TaDaaa...anyway
}

void Renderer::renderTile(Tile* tile, Tilemap* tilemap) {
  SDL_Texture* texture = tile->getTileset()->getTexture();
  SDL_Rect srect = tile->getTileset()->getBaseFrameByTileID(tile->getTID());
  SDL_Rect drect = {
    (tile->getGID() % tilemap->_n_rows) * tilemap->_grid_w,
    (tile->getGID() / tilemap->_n_rows) * tilemap->_grid_h,
    tilemap->_grid_w,
    tilemap->_grid_h  
  };
  renderTexture(texture, srect, drect, 0.0, NULL, SDL_FLIP_NONE);
}

// simplest
void Renderer::renderSprite(Sprite* sprite,float x,float y) {
  renderSprite(sprite, x, y, 1.0, 0.0, NULL, SDL_FLIP_NONE);
}

void Renderer::renderSprite(Sprite* sprite,float x,float y,float scale) {
  renderSprite(sprite, x, y, scale, 0.0, NULL, SDL_FLIP_NONE);
}

void Renderer::renderSprite(Sprite* sprite,float x,float y,float scale,SDL_RendererFlip flip) {
  renderSprite(sprite, x, y, scale, 0.0, NULL, flip);
}

SDL_Rect Renderer::getDestinationRect(float x, float y, int width, int height, float scale) {   
  //relying on implicit type casting NO
  SDL_Rect drect = {
      static_cast<int>(x),
      static_cast<int>(y),
      width,
      height
  };    
  drect.w *= scale;
  drect.h *= scale;
  return drect;
}

void Renderer::renderText(const char* text, int x, int y, TTF_Font* font, SDL_Color color) {
  SDL_Surface* message = TTF_RenderText_Solid(font, text, color);
  SDL_Rect drect = { x, y, message->w, message->h };
  apply_text(message, drect);
}

void Renderer::apply_text(SDL_Surface* surface, SDL_Rect destRect) {
  SDL_Texture* texture = nullptr;
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x0, 0x0, 0x0));
  texture = SDL_CreateTextureFromSurface(_renderer, surface);
  SDL_RenderCopy(_renderer, texture, NULL, &destRect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);//should i?
}

//i think i need a separate class for text

void Renderer::clear() {
  SDL_RenderPresent(_renderer);
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  SDL_RenderClear(_renderer);
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(_renderer);
}

void Renderer::renderRect(float x, float y, int w, int h, std::string color) {
  SDL_Rect rect = { static_cast<int>(x), static_cast<int>(y), w, h };
  SDL_Color rgbacolor = color_map[color];
  //SDL_RenderClear(_renderer);
  SDL_SetRenderDrawColor(_renderer, rgbacolor.r, rgbacolor.g, rgbacolor.b, rgbacolor.a);
  SDL_RenderDrawRect(_renderer, &rect);
}

//its render fill rect actually
void Renderer::renderFillRect(int x, int y, int w, int h, std::string color) {
  SDL_Rect rect = { x, y, w, h };
  SDL_Color rgbacolor = color_map[color];
  //SDL_RenderClear(_renderer);
  SDL_SetRenderDrawColor(_renderer, rgbacolor.r, rgbacolor.g, rgbacolor.b, rgbacolor.a);
  SDL_RenderFillRect(_renderer, &rect);
}

SDL_Renderer* Renderer::getRenderer() {
  return _renderer;
}