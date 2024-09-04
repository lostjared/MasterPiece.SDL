CXX=em++

OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

CFLAGS= -std=c++11 -s USE_SDL=2 -s USE_SDL_TTF=2 -DSTB_IMAGE=1
#`sdl2-config --cflags`
LDFLAGS= -s USE_SDL=2 -s USE_SDL_TTF=2  --preload-file assets
#`sdl2-config --libs` -lSDL2_ttf
PROGRAM=MasterPiece.html

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(PROGRAM): $(OBJ)
	$(CXX) -o $(PROGRAM)  $(OBJ) $(LDFLAGS)

all: $(PROGRAM)

.PHONY: clean clear
clean:
	rm -f $(PROGRAM)  *.o

