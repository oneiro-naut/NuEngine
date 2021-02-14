#include "Vector2d.h"

Vector2d operator * (double scale, Vector2d const &v) {
  Vector2d scaled_v;
  scaled_v.x = v.x * scale;
  scaled_v.y = v.y * scale;
  return scaled_v;
}
