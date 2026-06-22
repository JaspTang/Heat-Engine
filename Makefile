CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O0
INCLUDES = -Isrc/computation -Isrc/visualization

SDLFLAGS = $(shell sdl2-config --cflags --libs)

SRC = \
src/computation/Grid.cpp \
src/computation/HeatCompute.cpp \
src/visualization/Renderer.cpp

APP = build/heat_engine

all:
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDES) \
	src/app/main.cpp \
	$(SRC) \
	-o $(APP) \
	$(SDLFLAGS)

run: all
	./$(APP)

test_grid:
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDES) \
	tests/test_grid.cpp \
	$(SRC) \
	-o build/test_grid

run_test_grid: test_grid
	./build/test_grid

clean:
	rm -rf build/*
