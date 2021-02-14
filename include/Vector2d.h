#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

struct Vector2d {
  double x;
  double y;

  Vector2d(): x(0.0), y(0.0) {}
  Vector2d(double x, double y): x(x), y(y) {}
  ~Vector2d(){}
  Vector2d operator + (Vector2d const &v2) {
    Vector2d result;
    result.x = x + v2.x;
    result.y = y + v2.y;
    return result;
  }

  Vector2d operator - () {
    Vector2d v_inverse;
    v_inverse.x = -x;
    v_inverse.y = -y;
    return v_inverse;
  }

  Vector2d operator - (Vector2d const &v2) {
    Vector2d result;
    result.x = x - v2.x;
    result.y = y - v2.y;
    return result;
  }

  double mgn() const {
    return sqrt(x*x + y*y);
  }

};

Vector2d operator * (double scale, Vector2d const &v);

#endif