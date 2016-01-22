CC = g++
CFLAGS = -g
PROG = bubbleTrouble

SRCS = main.cpp collision.cpp structure.cpp

LIBS = -lglut -lGLU -lGL -lm

all: $(PROG) collision.h structure.h

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
