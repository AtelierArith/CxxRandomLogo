- Install
    - Julia
    - CxxWrap 0.16
    - Install EasyEigenInterface
    - WrapIt.jl wrapit
    - CMake

```bash
$ CXXWRAP_PREFIX=`julia --project -e 'using CxxWrap; CxxWrap.prefix_path() |> print'`
$ cmake -S . -B ./build
$ cmake --build ./build
```