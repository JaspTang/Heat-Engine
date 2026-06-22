CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O0 -fsanitize=address
INCLUDES = -Isrc/computation -Isrc/visualization

SDLFLAGS = $(shell sdl2-config --cflags --libs)

GLLIBS = -lGLEW -lGL

SRC = \
src/computation/Grid.cpp \
src/computation/HeatCompute.cpp \
src/visualization/Renderer.cpp \
src/visualization/Shader.cpp

APP = build/heat_engine

all:
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDES) \
	src/app/main.cpp \
	$(SRC) \
	-o $(APP) \
	$(SDLFLAGS) \
	$(GLLIBS)

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

test_visualization:
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDES) \
	tests/test_visualization.cpp \
	$(SRC) \
	-o build/test_visualization \
	$(SDLFLAGS) \
	$(GLLIBS)

run_test_visualization: test_visualization
	./build/test_visualization

clean:
	rm -rf build/*
