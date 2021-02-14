#ifndef _CORE_IMAGE_H
#define _CORE_IMAGE_H

#include <SDL2/SDL.h>
#include "Vector2d.h"

class Image {
  Vector2d _position;
  int _img_w;
  int _img_h;
  SDL_Texture* _texture;
  float _scale;
  bool _visible;

 public:
  Image(double xpos, double ypos, int w, int h, SDL_Texture* texture);
  ~Image();
  virtual void update();
  int getXpos() const { return static_cast<int>(_position.x); }
  int getYpos() const { return static_cast<int>(_position.y); }
  int getW() const { return _img_w; }
  int getH() const { return _img_h; }
  void changeX(double newx) { _position.x = newx; }
  void changeY(double newy) { _position.y = newy; }
  SDL_Texture* getTexture() const { return _texture; }
};

#endif