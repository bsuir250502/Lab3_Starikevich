all:
	gcc -Wall -o lab3.bin lab3.c mylib.c -lm && ./lab3.bin
clean: 
	rm lab3.bin
