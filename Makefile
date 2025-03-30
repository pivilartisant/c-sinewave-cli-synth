CC = gcc
CFLAGS = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lsoundio -lm

sinewave: 
	$(CC) -o ./build/sinewave1 sinewave1.c $(CFLAGS) $(LDFLAGS) && $(CC) -o ./build/sinewave2 sinewave2.c $(CFLAGS) $(LDFLAGS)

clean:
	cd ./build && rm -f sinewave1 && rm -rf sinewave2

play:
	make clean && make sinewave && ./build/sinewave2
