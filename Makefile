build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -lSDL2_image -o renderer 

run:
	./renderer

clean:
	rm renderer