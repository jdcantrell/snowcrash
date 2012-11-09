CFLAGS = `sdl-config --cflags` -g
LFLAGS = `sdl-config --libs` -lSDL -lm
CXX = clang

all: sdl_test

sdl_test: sdl_test.o
	$(CXX) sdl_test.o -o sdl_test $(LFLAGS)

sdl_test.o: sdl_test.c
	$(CXX) $(CFLAGS) -c sdl_test.c

clean:
	rm -rf *.o sdl_test
