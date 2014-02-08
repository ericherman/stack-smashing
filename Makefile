#

EXECUTABLE=stack-smash
SOURCES=stack-smash.c

DANGER_CFLAGS=-fno-stack-protector

# Marks the object as requiring executable stack.
# see also https://en.wikipedia.org/wiki/NX_bit
DANGER_LFLAGS=-zexecstack

CC=gcc
STD_CFLAGS=--std=c89
NOISY_CFLAGS=-Werror -Wall -Wextra -pedantic
OPTIMIZER_CFLAGS=-ggdb -O0

CFLAGS=$(DANGER_CFLAGS) $(STD_CFLAGS) $(OPTIMIZER_CFLAGS) $(NOISY_CFLAGS)

LDFLAGS=$(DANGER_LFLAGS)

OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) -S $(CFLAGS) $^ -o $^.s
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o *.c.s $(EXECUTABLE)

INPUT_4=ABCD
INPUT_66=ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxzy-1234567890+=

check: $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT_4)
	./$(EXECUTABLE) $(INPUT_66)
