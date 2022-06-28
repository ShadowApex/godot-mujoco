# Mujoco configuration
MUJOCO_REPO = https://github.com/deepmind/mujoco.git
MUJOCO_VERSION ?= 2.2.0
MUJOCO_SRC = tmp/mujoco
MUJOCO_BUILD_DIR = $(MUJOCO_SRC)/build
MUJOCO_LIB_DIR = $(MUJOCO_BUILD_DIR)/lib
MUJOCO_HEADERS_DIR = $(MUJOCO_SRC)/include

# The static mujoco libraries to build
MUJOCO_LIBRARY_FILES := libccd.a liblodepng.a libmujoco.a libqhullstatic_r.a libtinyobjloader.a libtinyxml2.a
MUJOCO_LIBRARIES := $(addprefix $(MUJOCO_LIB_DIR)/,$(MUJOCO_LIBRARY_FILES))

# Output configuration
MUJOCO_DIR = mujoco
MUJOCO_SRC_DIR = $(MUJOCO_DIR)/src
HEADERS = $(addprefix $(MUJOCO_DIR)/include/mujoco/,mjdata.h mjexport.h mjmodel.h mjrender.h mjtnum.h mjui.h mjvisualize.h mjxmacro.h mujoco.h)
LIBRARIES = $(addprefix libpath/,$(MUJOCO_LIBRARIES))

.PHONY: build
build: $(HEADERS) $(MUJOCO_SRC_DIR) $(LIBRARIES)

# Download the mujoco source code
$(MUJOCO_SRC):
	@echo "Cloning mujoco source..."
	git clone -b $(MUJOCO_VERSION) --single-branch $(MUJOCO_REPO) $(MUJOCO_SRC)
	@echo "Patching CMakeLists.txt for static compilation..."
	patch -u $(MUJOCO_SRC)/CMakeLists.txt -i ./CMakeLists.txt.patch

$(MUJOCO_LIBRARIES): $(MUJOCO_SRC)
	@echo "Builing mujoco static libraries..."
	mkdir -p $(MUJOCO_BUILD_DIR)
	cd $(MUJOCO_BUILD_DIR) && cmake -DMUJOCO_BUILD_EXAMPLES=OFF -DMUJOCO_BUILD_TESTS=OFF -DMUJOCO_TEST_PYTHON_UTIL=OFF ..
	cd $(MUJOCO_BUILD_DIR) && cmake --build .

$(HEADERS): $(MUJOCO_SRC)
	@echo "Copying mujoco headers..."
	mkdir -p $(MUJOCO_DIR)
	cp -r $(MUJOCO_HEADERS_DIR) $(MUJOCO_DIR)/include

$(MUJOCO_SRC_DIR): $(MUJOCO_SRC)
	@echo "Copying mujoco source files..."
	mkdir -p $(MUJOCO_DIR)
	cp -r $(MUJOCO_SRC)/src $(MUJOCO_DIR)

$(LIBRARIES): $(MUJOCO_LIBRARIES)
	@echo "Copying mujoco libraries..."
	mkdir -p libpath
	cp -r $(MUJOCO_LIB_DIR)/*.a libpath

.PHONY: clean
clean:
	rm -rf $(MUJOCO_SRC)

.PHONY: debug
debug:
	@echo "Mujoco"
	@echo "  Repo:      $(MUJOCO_REPO)"
	@echo "  Version:   $(MUJOCO_VERSION)"
	@echo "  Src Dir:   $(MUJOCO_SRC)"
	@echo "  Build Dir: $(MUJOCO_BUILD_DIR)"
	@echo "  Lib Dir:   $(MUJOCO_LIB_DIR)"
	@echo "  Headers:   $(MUJOCO_HEADERS_DIR)"
	@echo "  Libraries: $(MUJOCO_LIBRARIES)"
