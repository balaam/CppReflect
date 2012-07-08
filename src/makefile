CC=g++
CFLAGS=-c -Wall
LDFLAGS=-L/usr/local/lib -static-libgcc -static-libstdc++ -lws2_32
SOURCES=main.cpp reflect.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=reflect

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm *.o *.exe

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $? $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@