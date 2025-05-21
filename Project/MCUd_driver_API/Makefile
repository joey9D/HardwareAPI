

BUILD_DIR ?= build
BUILD_TYPE ?= Debug

all:
#	cd build && cmake -S .. -B . -G "Ninja" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	cd build && cmake -S .. -B . -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=cmake/arm_none_eabi_gcc.cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	cmake --build $(BUILD_DIR) -j

flash erase reset debug:
	cmake --build $(BUILD_DIR) --target $@

clean:
	@cmake -E rm -rf $(BUILD_DIR)

dependency:
# for macos
	cd build && cmake ..
# --graphviz=graph.dot && dot -Tpng graph.dot -o graphImage.png

# for windows
#	cd build && cmake -S .. -B . -G "Ninja"

prepare:
	rm -rf build
	mkdir build
