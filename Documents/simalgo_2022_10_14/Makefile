CC = gcc
OBJFLAGS = 
WFLAGS = -Wall
OBJS = io.o simulator.o
DFLAGS = -g

CFLAGS = $(WFLAGS) $(DFLAGS)

simulator: $(OBJS)
	$(CC) $(OBJS) -o simulator

simulator.o: simulator.c simulator.h
	$(CC) $(CFLAGS) -c $< -o $@
	
io.o: io.c io.h
	$(CC) $(CFLAGS) -c $< -o $@

make clean:
	rm simulator
	rm simulator.o 
	rm io.o