#pragma once

#include <random>
#include <Eigen/Dense>
Eigen::MatrixXd sample_svs(std::mt19937 &rng, double α, int N);
