#Kamil Zielinski
#make dla server

CC=gcc
CXX=g++
CFLAGS=-c
CXXFLAGS=-c
LDFLAGS=
CSOURCES=server.cpp connection.cpp  game.cpp karta.cpp chat.cpp chatKomentowanie.cpp log.cpp
SOURCES=$(CSOURCES)
OBJECTS=$(CSOURCES:.c=.o) 
EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -pthread -std=c++11 -o  $@ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $< -o  $@

clean:
	rm *.o
