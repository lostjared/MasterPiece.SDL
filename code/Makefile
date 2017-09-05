all: mpsdl

main.o: main.cpp
	$(CXX) -Wall -std=c++98  -I/usr/local/include -g -c `sdl-config --cflags` main.cpp

mpsdl: main.o 
	$(CXX) -g -std=c++98 `sdl-config --libs` -lSDL_ttf `pkg-config freetype2 --libs`  main.o -o mpsdl

clean:
	rm -f *.o mpsdl
