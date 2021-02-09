#include "Tile.h"

Tile::Tile(int tid, Tileset* tileset, int gid) : _tid(tid), _tileset(tileset), _grid_id(gid), _active(true), _visible(true)
{}

Tile::Tile(int tid, Tileset* tileset, int gid, bool active, bool visible) : _tid(tid), _tileset(tileset), _grid_id(gid), _active(active), _visible(visible)
{}

Tile::~Tile()
{}

void Tile::draw() const {
  
}