OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

CFLAGS= -std=c++11 `sdl2-config --cflags`
LDFLAGS= `sdl2-config --libs` -lSDL2_ttf
PROGRAM=MasterPiece.SDL

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(PROGRAM): $(OBJ)
	$(CXX) -o $(PROGRAM)  $(OBJ) $(LDFLAGS)

all: $(PROGRAM)

.PHONY: clean clear
clean:
	rm -f $(PROGRAM)  *.o

