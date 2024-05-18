#include <iostream>
#include <random>
#include "point_generation.hpp"

int main() {
  auto xy = generate_points();
  auto xs = xy.first;
  auto ys = xy.second;
  // header
  std::cout << "x,y" << std::endl;
  // contents
  for (int i = 0; i < xs.size(); i++) {
    auto x = xs[i];
    auto y = ys[i];
    std::cout << x << "," << y << std::endl;
  }
  return 0;
};
