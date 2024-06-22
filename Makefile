.PHONY: all build test

all: build

build:
	julia --project -e 'using Pkg; Pkg.build()'

