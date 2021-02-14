#include "../include/Vector2d.h"
#include <iostream>

int main() {
  Vector2d v1(2.0, 1.0);
  Vector2d v2(1.0, 2.0);
  std::cout << "mgn of v1 = " << v1.mgn() << "\n";
  std::cout << "mgn of v2 = " << v2.mgn() << "\n";
  std::cout << "v3 = v1 + v2\n";
  Vector2d v3 = v1 + v2;
  std::cout << "v3.x = " << v3.x << " v3.y = " << v3.y << "\n";
  std::cout << "mgn of v3 = " << v3.mgn() << "\n";
  v3 = 2 * v3;
  std::cout << "mgn of v3 after scaling 2 times = " << v3.mgn() << "\n";
  v3 = -v3;
  std::cout << "v3 = -v3\n";
  std::cout << "v3.x = " << v3.x << " v3.y = " << v3.y << "\n";
  v3 = v3 - v1;
  std::cout << "v3 = v3 - v1\n";
  std::cout << "v3.x = " << v3.x << " v3.y = " << v3.y << "\n";
  return 0;
}