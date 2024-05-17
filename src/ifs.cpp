#include <Eigen/Dense>
#include <cmath>
#include <random>

#include "ifs.hpp"
#include "ifs_sigma_factor.hpp"
#include "util.hpp"

SigmaFactorIFS::SigmaFactorIFS(std::vector<Affine> transforms,
                               std::discrete_distribution<int> catdist)
    : transforms(transforms), catdist(catdist) {};

Eigen::Matrix2d rand_rotmat(std::mt19937 &rng) {
  std::uniform_real_distribution<double> u(0.0, 2.0);
  auto theta = u(rng);
  Eigen::MatrixXd R(2, 2);
  R << std::cos(theta), -std::sin(theta), std::sin(theta), std::cos(theta);
  return R;
}

Eigen::Matrix2d diagm(double d1, double d2) {
  Eigen::Matrix2d D;
  D << d1, 0, d2, 0;
  return D;
}

SigmaFactorIFS rand_sigma_factor_ifs(std::mt19937 &rng) {
  std::uniform_int_distribution<> dist_n(1, 4);
  std::uniform_int_distribution<> dist_b(0, 1);
  int N = dist_n(rng);
  auto αₗ = 0.5 * (5 + N);
  auto αᵤ = 0.5 * (6 + N);
  auto σfactor = uniform(rng, αₗ, αᵤ);
  Eigen::MatrixXd svs = sample_svs(rng, σfactor, N);
  std::vector<Affine> transforms;
  std::vector<double> probs;
  for (int k = 0; k < svs.rows(); k++) {
    auto σ1 = svs(k, 0);
    auto σ2 = svs(k, 1);
    auto Rtheta = rand_rotmat(rng);
    auto Rphi = rand_rotmat(rng);
    auto Σ = diagm(σ1, σ2);
    auto D = diagm(2 * dist_b(rng) - 1, 2 * dist_b(rng) - 1);
    auto W = Rtheta * Σ * Rphi * D;
    auto b1 = uniform(rng, -1.0, 1.0);
    auto b2 = uniform(rng, -1.0, 1.0);
    Eigen::Vector2d b = {b1, b2};
    probs.push_back(std::abs(W.determinant()));
    transforms.push_back(Affine(W, b));
  }

  std::discrete_distribution<int> catdist(probs.begin(), probs.end());

  return SigmaFactorIFS(transforms, catdist);
}
