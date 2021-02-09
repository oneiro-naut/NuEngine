#ifndef TILEMAP_H
#define TILEMAP_H

struct Tilemap {
  const int _n_rows;
  const int _n_cols;
  const int _grid_w;
  const int _grid_h;
  const int _grid_size;
  Tilemap(int nrows, int ncols, int gridw, int gridh): _n_rows(nrows), _n_cols(ncols), _grid_w(gridw), _grid_h(gridh), _grid_size(nrows * ncols)
  {}
  ~Tilemap()
  {}
};
#endif