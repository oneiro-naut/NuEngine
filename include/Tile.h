#ifndef _TILE_H
#define _TILE_H

#include <string>
#include "Tileset.h"
#include "Collision.h"

class Tile {
 protected:
  bool _visible;
  bool _active;
  std::string _type; // if tile is associated with some object
  int _tid;
  /*collision_flags _collision_flags;*/
  Tileset* _tileset;
  int _grid_id; // equivalent to position
 public:
  Tile(int tid, Tileset* tileset, int gid/*, collision_flags cf*/);
  Tile(int tid, Tileset* tileset, int gid,/*, collision_flags cf*/ bool visible, bool active);
  ~Tile();
  virtual void draw() const;
  bool isVisible() const { return _visible; }
  bool isActive() const { return _active; }
  int getTID() const { return _tid; }
  int getGID() const { return _grid_id; }
  Tileset* getTileset() const { return _tileset; }
};

#endif