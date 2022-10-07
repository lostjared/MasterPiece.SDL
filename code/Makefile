OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

CFLAGS= -std=c++98 `sdl-config --cflags`
LDFLAGS= `sdl-config --libs` -lSDL_ttf
PROGRAM=MasterPiece.SDL

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

per.test: $(OBJ)
	$(CXX) -o $(PROGRAM)  $(OBJ) $(LDFLAGS)

all: example

.PHONY: clean clear
clean:
	rm -f $(PROGRAM)  *.o

