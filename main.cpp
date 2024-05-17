#include<random>
#include<iostream>
#include "ifs.hpp"

int main(){
	std::mt19937 rng(42);
	auto ifs = rand_sigma_factor_ifs(rng);
	std::cout << ifs.transforms[0].W << ifs.transforms[1].b << std::endl;
};
