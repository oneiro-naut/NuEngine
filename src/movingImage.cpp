#include "movingImage.h"

movingImage::movingImage(double xpos, double ypos, int w, int h, double vx, double vy, SDL_Texture* texture): _velocity(vx, vy), Image(xpos, ypos, w, h, texture)
{}

movingImage::~movingImage()
{}

void movingImage::update() {
  _position.x += _velocity.x;
  _position.y += _velocity.y;
}
