CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lm
	SDL_INCLUDE = -I/usr/include/SDL/

all: game

game: main.o menu.o map.o collision.o savegame.o
	$(CC) $(CFLAGS) main.o menu.o map.o collision.o savegame.o -o game $(LIBS)

main.o: main.c menu.h map.h collision.h savegame.h
	$(CC) $(CFLAGS) $(SDL_INCLUDE) -c main.c -o main.o
	
menu.o: menu.c menu.h
	$(CC) $(CFLAGS) $(SDL_INCLUDE) -c menu.c -o menu.o

map.o: map.c map.h
	$(CC) $(CFLAGS) $(SDL_INCLUDE) -c map.c -o map.o

collision.o: collision.c collision.h
	$(CC) $(CFLAGS) $(SDL_INCLUDE) -c collision.c -o collision.o

savegame.o: savegame.c savegame.h
	$(CC) $(CFLAGS) $(SDL_INCLUDE) -c savegame.c -o savegame.o

clean:
	rm -f *.o game

