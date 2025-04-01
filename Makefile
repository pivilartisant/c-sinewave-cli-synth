CC = gcc
CFLAGS = -I/opt/homebrew/include -I./include
LDFLAGS = -L/opt/homebrew/lib -lsoundio -lm

# Add object files
OBJECTS = main.o sinewave.o scales.o octave.o

# Target to build the program
main: $(OBJECTS)
	$(CC) -o ./bin/main $(OBJECTS) $(LDFLAGS)

# Compile main.c
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Compile src/sinewave.c
sinewave.o: src/sinewave.c
	$(CC) $(CFLAGS) -c src/sinewave.c

# Compile src/scales.c
scales.o: src/scales.c
	$(CC) $(CFLAGS) -c src/scales.c

# Compile src/octave.c
octave.o: src/octave.c
	$(CC) $(CFLAGS) -c src/octave.c

# Clean up object files
clean:
	rm -f ./bin/main *.o

# Play target to build and run the program
play: main
	make clean && make && ./bin/main
