BUILD_DIR := build

.PHONY: all cmake build clean

all: build

cmake:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_COLOR_MAKEFILE:BOOL=ON ..

build: cmake
	@$(MAKE) -C $(BUILD_DIR)

clean:
	@$(MAKE) -C $(BUILD_DIR) clean