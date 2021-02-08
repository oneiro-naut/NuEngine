#include "Controllable.h"

Controllable::Controllable(Game &g, ObjectType otype, float x, float y, int w, int h, Tileset* ts): GameObject(g, otype,
        x, y, w, h, ts) 
{}

Controllable::~Controllable() 
{}

void Controllable::getInput(SDL_Event* e) {
  if (e == NULL)
    return;
  onUserInput(e);
}

void Controllable::onUserInput(SDL_Event* e) {

}