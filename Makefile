CC = gcc
CFLAGS = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lsoundio -lm

main: 
	$(CC) -o ./build/main main.c $(CFLAGS) $(LDFLAGS)

clean:
	cd ./build && rm -f main

play:
	make clean && make main && ./build/main
