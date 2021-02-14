#include "Image.h"

Image::Image(double xpos, double ypos, int w, int h, SDL_Texture* texture): _position(xpos, ypos), _img_w(w), _img_h(h), _texture(texture), _scale(1.0), _visible(true)
{}

Image::~Image() {
  SDL_DestroyTexture(_texture);
}

void Image::update() {
  _position.x -= 1;
}