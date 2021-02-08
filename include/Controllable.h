#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H
#include "GameObject.h"

// Player class derives from this class

class Controllable : public GameObject {
 public:
  Controllable(Game &g, ObjectType otype, float x, float y, int w, int h, Tileset* ss);
  ~Controllable();
  virtual void getInput(SDL_Event* e) override;

 protected:
  virtual void onUserInput(SDL_Event* e);

};
#endif