#include <random>
#include <Eigen/Dense>

#include "util.hpp"
#include "ifs_sigma_factor.hpp"

Eigen::MatrixXd sample_svs(std::mt19937 &rng, double α, int N) {

  Eigen::MatrixXd singular_values;
  // set the rows and columns of a MatrixXd at runtime
  singular_values.resize(N, 2);

  auto bₗ = α - 3 * N + 3;
  auto bᵤ = α;
  double half = 0.5;
  double third = 3.0;
  for (int k = 0; k < N - 1; k++) {
    double σk1 = uniform(rng, std::max(0., bₗ / third), std::min(1., bᵤ));
    bₗ = bₗ - σk1;
    bᵤ = bᵤ - σk1;
    double σk2 =
        uniform(rng, std::max(0., half * bₗ), std::min(σk1, half * bᵤ));
    bₗ = bₗ - 2 * σk2 + 3;
    bᵤ = bᵤ - 2 * σk2;
    singular_values(k, 0) = σk1;
    singular_values(k, 1) = σk2;
  }

  double σ2 = uniform(rng, std::max(0., half * (bᵤ - 1.)), bᵤ / third);
  double σ1 = bᵤ - 2 * σ2;
  singular_values(N - 1, 0) = σ1;
  singular_values(N - 1, 1) = σ2;
  return singular_values;
};
