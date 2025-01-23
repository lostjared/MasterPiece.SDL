CXX=em++
OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

CFLAGS= -s USE_SDL=2 -s USE_SDL_TTF=2
LDFLAGS= --preload-file assets -s USE_SDL=2 -s USE_SDL_TTF=2
PROGRAM=MasterPiece.html

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(PROGRAM): $(OBJ)
	$(CXX) -o $(PROGRAM)  $(OBJ) $(LDFLAGS)

all: $(PROGRAM)

.PHONY: clean clear
clean:
	rm -f $(PROGRAM) *.html *.js *.wasm *.data *.o

