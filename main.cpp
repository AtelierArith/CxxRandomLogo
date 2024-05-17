#include <iostream>
#include <random>
#include "ifs_sigma_factor.hpp"
#include "ifs.hpp"

int main() {
  std::random_device seed_gen;
  std::mt19937 rng(seed_gen());
  auto ifs = rand_sigma_factor_ifs(rng);

  const int N = 100000;
  std::vector<double> xs, ys;
  xs.reserve(N);
  ys.reserve(N);

  double x = 0.0;
  double y = 0.0;
  int c = 0;
  for (int i = 0; i < N; i++) {
    c = ifs.catdist(rng);
    auto aff = ifs.transforms[c];
    Eigen::Vector2d xy({x, y});
    xy = aff.transform(xy);
    xs.push_back(x);
    ys.push_back(y);
    x = xy[0];
    y = xy[1];
  }

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
