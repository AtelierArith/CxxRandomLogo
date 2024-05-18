#include "jlcxx/jlcxx.hpp"
#include "jlcxx/stl.hpp"
#include "point_generation.hpp"

JLCXX_MODULE define_julia_module(jlcxx::Module &mod){
  mod.method("generate_points", [](jlcxx::ArrayRef<double> xs, jlcxx::ArrayRef<double> ys){
    int N = xs.size();
    generate_points(xs.data(), ys.data(), N);
  });
}
