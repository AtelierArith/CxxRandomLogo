.PHONY: build clean

build:
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release
	cmake --build ./build --config Release -j `nproc`

clean:
	$(RM) -r $(CURDIR)/build
