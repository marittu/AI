CC = g++
CFLAGS = -c -std=c++11
LDFLAGS = -std=c++11
SOURCES =board.cpp node.cpp main.cpp
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = astar

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o