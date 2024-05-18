#include <iostream>
#include <random>
#include <vector>
#include <utility>

#include "ifs_sigma_factor.hpp"
#include "ifs.hpp"
#include "point_generation.hpp"

void generate_points(double* xs, double* ys, int N){
  std::random_device seed_gen;
  std::mt19937 rng(seed_gen());
  auto ifs = rand_sigma_factor_ifs(rng);

  double x = 0.0;
  double y = 0.0;
  int c = 0;
  for (int i = 0; i < N; i++) {
    c = ifs.catdist(rng);
    auto aff = ifs.transforms[c];
    Eigen::Vector2d xy({x, y});
    xy = aff.transform(xy);
    xs[i] = x;
    ys[i] = y;
    x = xy[0];
    y = xy[1];
  }
};

void generate_points(std::vector<double> &xs, std::vector<double> &ys){
  int N = xs.size();
  generate_points(xs.data(), ys.data(), N);
};

std::pair<std::vector<double>, std::vector<double>> generate_points() {
  const int N = 100000;
  std::vector<double> xs(N, 0.0);
  std::vector<double> ys(N, 0.0);
  generate_points(xs.data(), ys.data(), N);
  return std::make_pair(xs, ys);
}

