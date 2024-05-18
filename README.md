# CxxRandomLogo
Port RandomLogos.jl written Julia to C++

# Setup

```console
$ bash build.sh
$ julia --project -e 'using Pkg; Pkg.instantiate()'
```

```julia
julia> using ImageInTerminal, CxxRandomLogo; CxxRandomLogo.draw()
```