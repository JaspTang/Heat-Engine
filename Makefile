CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O0
INCLUDES = -Isrc/computation -Isrc/visualization

SRC = \
src/app/main.cpp \
src/computation/Grid.cpp \
src/computation/HeatCompute.cpp \
src/visualization/Renderer.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = build/heat_engine

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf build/*.o $(TARGET)
