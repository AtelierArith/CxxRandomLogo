# CxxRandomLogo

Port AtelierArith/RandomLogos.jl written Julia to C++.

## Requirements

- CMake
- Julia

# Setup

```console
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

## Pluto demo

```julia
julia> using Pluto; Pluto.run()
```

Then open playground/pluto/notebook.jl from Pluto Web UI