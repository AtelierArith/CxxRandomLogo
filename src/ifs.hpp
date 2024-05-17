#pragma once
#include <random>

#include "affine.hpp"

class SigmaFactorIFS {
public:
  // constructor
  SigmaFactorIFS(std::vector<Affine> transforms,
                 std::discrete_distribution<int> catdist);
  std::vector<Affine> transforms;
  std::discrete_distribution<int> catdist;
};

SigmaFactorIFS rand_sigma_factor_ifs(std::mt19937 &rng);
