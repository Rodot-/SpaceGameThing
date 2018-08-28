
CXX = g++
CPPFLAGS = -Iinclude
LDLIBS = -lsfml-graphics -lsfml-system -lsfml-window

BIN_DIR = ./bin
BUILD_DIR = ./build
SRC_DIR = ./src


FILES = $(notdir $(wildcard $(SRC_DIR)/*.cpp))

SRC_LIST = $(patsubst %,$(SRC_DIR)/%,$(FILES))
OBJ_LIST = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(FILES))


.PHONY: clean compile

all: compile 

compile: $(BUILD_DIR) $(OBJ_LIST)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp

	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR):

	mkdir $(BUILD_DIR)

clean:

	rm -r $(BUILD_DIR)

test: $(OBJ_LIST)

	$(CXX) $(CPPFLAGS) test/worldTesting.cpp $(OBJ_LIST) -o testing.out $(LDLIBS)

force: clean compile test
