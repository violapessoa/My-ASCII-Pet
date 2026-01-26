CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = main.o pet.o petart.o rps.o
TARGET = bin/myasciipet

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

main.o: src/main.c src/pet.h
	$(CC) $(CFLAGS) -c src/main.c

pet.o: src/pet.c src/pet.h
	$(CC) $(CFLAGS) -c src/pet.c

petart.o: src/petart.c src/pet.h
	$(CC) $(CFLAGS) -c src/petart.c

rps.o: src/rps.c src/pet.h
	$(CC) $(CFLAGS) -c src/rps.c

clean:
	rm -f $(OBJFILES) $(TARGET) *~


