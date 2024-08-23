.PHONY: build clean

build:
	@echo "Building wrapit..."
	CXXWRAP_PREFIX=`julia --project -e 'using CxxWrap; CxxWrap.prefix_path() |> print'`
	cmake -S $(CURDIR) -B $(CURDIR)/build -DCMAKE_PREFIX_PATH=$(CXXWRAP_PREFIX)
	cmake --build $(CURDIR)/build

clean:
	$(RM) -r $(CURDIR)/build
