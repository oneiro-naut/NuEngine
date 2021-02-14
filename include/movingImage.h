#ifndef MOVING_IMAGE_H
#define MOVING_IMAGE_H

#include "Image.h"

class movingImage : public Image {
 protected:
  Vector2d _velocity;
 public:
  movingImage(double xpos, double ypos, int w, int h, double vx, double vy, SDL_Texture* texture);
  ~movingImage();
  virtual void update() override;
};

#endif