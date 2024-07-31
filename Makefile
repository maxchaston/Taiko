all:
	gcc -g3 -lSDL2 -lm main.c -o mouse-taiko

run: all
	./mouse-taiko
