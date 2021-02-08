#include "Tileset.h"

Tileset::Tileset(int tile_w, int tile_h, int n_rows, int n_cols, std::string name, SDL_Texture* texture): _tileW(tile_w), _tileH(tile_h), _n_rows(n_rows), _n_cols(n_cols), _name(name), _texture(texture), _tileset_size(n_rows * n_cols)  
{}


Tileset::~Tileset()
{}

SDL_Rect Tileset::getBaseFrameByTileID(int tid) {
  SDL_Rect base_f = {
    (tid % _n_cols) * _tileW,
    (tid / _n_cols) * _tileH,
    _tileW,
    _tileH
  };
  return base_f;
}