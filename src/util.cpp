#include <random>
#include "util.hpp"

double uniform(std::mt19937 &rng, double a, double b) {
  std::uniform_real_distribution<double> u;
  return (b - a) * u(rng) + a;
}


