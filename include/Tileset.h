#ifndef TILESET_H
#define TILESET_H
#include <string>
#include <SDL2/SDL.h>

#include "Rectangle.h"

class Tileset {
 private:
  const int _tileW;
  const int _tileH;
  const int _n_rows;
  const int _n_cols;
  const int _tileset_size;
  const std::string _name;
  SDL_Texture* _texture;

 public:
  Tileset(int tile_w, int tile_h, int n_rows, int n_cols, std::string name, SDL_Texture* texture);
  ~Tileset();
  int getTileWidth() const { return _tileW; }
  int getTileHeight() const { return _tileH; }
  int getNumRows() const { return _n_rows; }
  int getNumCols() const { return _n_cols; }
  int getSize() const { return _tileset_size; }
  std::string getName() const { return _name; }
  SDL_Texture* getTexture() const { return _texture; }
  SDL_Rect getBaseFrameByTileID(int tid);
};
#endif