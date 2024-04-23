CC=gcc

all: build run

build:
	$(CC) -Wall -Wextra -std=c17 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer src/*.c -o pixel

run:
	./pixel

clean:
	rm pixel
