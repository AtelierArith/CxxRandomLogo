# CxxRandomLogo

Port [AtelierArith/RandomLogos.jl](https://github.com/AtelierArith/RandomLogos.jl) written in Julia to C++.

## Requirements

- CMake
- Julia

# Setup

```console
$ julia -e 'using Pkg; Pkg.activate(); Pkg.add("CxxWrap.jl")'
$ bash build.sh
$ julia --project -e 'using Pkg; Pkg.instantiate()'
```

# How to use

## C++ Application

```console
$ bash build.sh
$ ./build/bin/CxxRandomLogo > out.csv
$ julia vis.jl
```

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
