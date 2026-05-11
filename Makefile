CXX = g++
CXXFLAGS = -Ilibs/glad/include
LIBS = -lglfw -lGL -ldl

SRC = $(wildcard *.cpp entities/*.cpp systems/*.cpp guidance/*.cpp physics/*.cpp math/*.cpp renderer/*.cpp targeting/*.cpp) libs/glad/src/glad.c

OUT = sim

all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LIBS) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)