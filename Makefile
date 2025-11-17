ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_DIR := $(ROOT_DIR)/build
NPROC := $(shell nproc)

conan_deps_release:
	conan install $(ROOT_DIR)/conanfile.txt --build=missing --output-folder=$(BUILD_DIR) -s build_type=Release

conan_deps_debug:
	conan install $(ROOT_DIR)/conanfile.txt --build=missing --output-folder=$(BUILD_DIR) -s build_type=Debug

build_debug: conan_deps_debug
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug
	cmake --build $(BUILD_DIR) -j $(NPROC)

build_release: conan_deps_release
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release
	cmake --build $(BUILD_DIR) -j $(NPROC)
	
install: build
	cmake --install $(BUILD_DIR)

all: build_release

clean:
	rm -rf $(BUILD_DIR)
#   rm $(ROOT_DIR)/CMakeUserPresets.json
