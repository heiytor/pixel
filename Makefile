build:
	g++ -Wall -Wextra -std=c++17 -I"./libs/" src/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.4 -o pixel;

run:
	./pixel

clean:
	rm -f ./pixel
