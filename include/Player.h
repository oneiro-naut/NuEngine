#ifndef PLAYER_H
#define PLAYER_H
#include "Controllable.h"
#include <array>

#define KEYARRSIZE 4

class Player : public Controllable {
 public:
  enum KeyCode {
    left = 0,
    right,
    up,
    down
  };
  Player(Game &g, ObjectType otype, float x, float y, int w, int h, Tileset* ts);
  ~Player();
  virtual void update() override;
  //virtual void draw() override;
  virtual void hasCollided(ObjectType withtype,SDL_Rect overlap_r) override;

 protected:
  std::array<bool, KEYARRSIZE> _keystate; 

  virtual void updateState() override;
  virtual void onUserInput(SDL_Event* e) override;
  virtual bool initSprites() override;
  virtual void checkBoundaryCollision() override;
  //umm this is redundant
  virtual void resolveCollision(ObjectType withtype,SDL_Rect overlap_r) override;
  virtual void updateCoordinates() override;
};
#endif