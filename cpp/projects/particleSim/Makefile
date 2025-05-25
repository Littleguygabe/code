# Makefile for compiling a raylib app on macOS with Homebrew

CXX = clang++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

SRC = main.cpp
OUT = particleSim 
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(OUT)
