# CxxRandomLogo

Port [AtelierArith/RandomLogos.jl](https://github.com/AtelierArith/RandomLogos.jl) written in Julia to C++.

## Requirements

- CMake
- Julia
  - See https://github.com/JuliaLang/juliaup to install Julia

# Setup

```console
$ git clone https://github.com/AtelierArith/CxxRandomLogo.git
$ cd CxxRandomLogo
$ make
```

# How to use

## C++ Application

Our C++ implementation provides point generation features that can be accessed from `generate_points`.

```cpp
// main.cpp
#include <iostream>
#include <random>
#include "point_generation.hpp"

int main() {
  // 100000 points
  auto xy = generate_points();
  auto xs = xy.first; // x coordinates
  auto ys = xy.second; // y coordinates
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
```

To build our C++ code, just run `make`.

```console
$ make
```

We'll see that `./build/bin` is generated and the executable file `CxxRandomLogo` corresponds to `main.cpp` is generated. To store results as a CSV file, just run the following command:

```console
$ ./build/bin/CxxRandomLogo > out.csv
$ head out.csv
x,y
0,0
-0.380685,0.692171
-1.09698,0.779349
-1.61693,0.45568
0.489574,-0.189705
-0.893767,-0.739919
-0.0128572,-1.12225
-0.594527,-1.4382
-0.226511,-1.66354
```

We can visalize the result using Julia script named `vis.jl`.

```console
$ julia vis.jl # out.png
```

This generates `out.png`

## Julia Interface

```julia
$ julia
               _
   _       _ _(_)_     |  Documentation: https://docs.julialang.org
  (_)     | (_) (_)    |
   _ _   _| |_  __ _   |  Type "?" for help, "]?" for Pkg help.
  | | | | | | |/ _` |  |
  | | |_| | | | (_| |  |  Version 1.10.3 (2024-04-30)
 _/ |\__'_|_|_|\__'_|  |  Official https://julialang.org/ release
|__/                   |


julia> using ImageInTerminal
julia> using CxxRandomLogo: draw
julia> [draw() draw() draw(); draw() draw() draw()]
```

<img width="1033" alt="image" src="https://github.com/AtelierArith/CxxRandomLogo/assets/16760547/f9074553-dd6a-413d-8642-bbb38fe6da49">

## Pluto demo

```julia
julia> using Pluto; Pluto.run()
```

Then open playground/pluto/notebook.jl from Pluto Web UI
