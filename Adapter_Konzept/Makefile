#
# Makefile adapter_konzept (Adapter for tools - Linux) 
#

GXX := g++

CXXFLAGS := -IInc -Ilibs/external/include -Wall -Wextra -std=c++17

SRC_DIR := Src
INC_DIR := Inc
BUILD_DIR := target

TARGET := $(BUILD_DIR)/myTools.out

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking..."
# Für dynamische Bibliotheken (shared libs .so):
	$(GXX) $^ -Llibs/external/bin -lmylib -o $@
# Für statische Bibliotheken (.a):
# $(GXX) $^ -Llibs/external/lib -lexternal -o $@
#	$(GXX) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR)

.PHONY: all clean
