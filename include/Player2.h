#ifndef PLAYER_2_H
#define PLAYER_2_H

#include "Player.h"

class Player2 : public Player {
 protected:
  virtual void updateCoordinates() override;
 public:
  Player2(Game &g, ObjectType otype, float x, float y, int w, int h, Tileset* ts);
  ~Player2();
  
};

#endif