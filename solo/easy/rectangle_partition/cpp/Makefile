SRC_DIRS := ./src
BUILD_DIRS := ./build

main: $(SRC_DIRS/main.cpp) $(SRC_DIRS)/input.cpp $(SRC_DIRS)/output.cpp
	mkdir -p ./build
	g++ $(SRC_DIRS)/main.cpp $(SRC_DIRS)/input.cpp $(SRC_DIRS)/output.cpp \
	-o $(BUILD_DIRS)/main

clean:
	rm -rf build/