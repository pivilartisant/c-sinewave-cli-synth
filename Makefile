CC = gcc
CFLAGS = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lsoundio -lm

sinewave: 
	$(CC) -o sinewave1 sinewave1.c $(CFLAGS) $(LDFLAGS) && $(CC) -o sinewave2 sinewave2.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f sinewave1 && rm -rf sinewave2

play:
	make clean && make sinewave && ./sinewave2
