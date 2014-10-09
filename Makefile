#

EXECUTABLE=stack-smash
SOURCES=stack-smash.c

DANGER_CFLAGS=-fno-stack-protector

# Marks the object as requiring executable stack.
# see also https://en.wikipedia.org/wiki/NX_bit
DANGER_LFLAGS=-zexecstack

CC=gcc
AS=as
LD=ld

STD_CFLAGS=-std=c89
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
	rm -rf *.o *.c.s $(EXECUTABLE) example3 c-shellcode shellcode \
		shellcode.o.objdump test-shellcode

INPUT_4=ABCD
INPUT_66=ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxzy-1234567890+=

check: $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT_4)
	./$(EXECUTABLE) $(INPUT_66)

EXAMPLE3_SOURCES=example3.c
EXAMPLE3_OBJS=$(EXAMPLE3_SOURCES:.c=.o)
example3: $(EXAMPLE3_OBJS)
	$(CC) $(EXAMPLE3_OBJS) -o $@ $(LDFLAGS)
	./example3

c-shellcode:
	$(CC) -S -fPIC $(CFLAGS) -Wno-multichar $@.c -o $@.c.s
	$(CC) -c -fPIC $(CFLAGS) -Wno-multichar $@.c -o $@.o
	$(CC) -static $@.o -o $@ $(LDFLAGS)
	./c-shellcode

shellcode:
	$(AS) shellcode.s -o shellcode.o
	objdump -D shellcode.o > shellcode.o.objdump
	$(LD) shellcode.o -o shellcode
	./shellcode

TEST_SHELLCODE_SOURCES=test-shellcode.c
TEST_SHELLCODE_OBJS=$(TEST_SHELLCODE_SOURCES:.c=.o)
test-shellcode: $(TEST_SHELLCODE_OBJS)
	$(CC) $(TEST_SHELLCODE_OBJS) -o $@ $(LDFLAGS)
	./test-shellcode
