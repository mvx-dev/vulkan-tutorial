CXX := g++
CXXFLAGS := -std=c++17 -Wall -g \
  -Ithird_party/lwlog/include

LDFLAGS := -Lthird_party/lwlog/lib \
  -llwlog_lib -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SRC_DIR := src
BUILD_DIR := build
BIN := bin/VulkanTutorial

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: compile-commands
	compile-commands: compile-commands.json

all: $(BIN)

$(BIN): $(OBJ) | $(BUILD_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

compile-commands.json:
	compiledb make all
