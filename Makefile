# CC=ccache gcc
CC=gcc
CFLAGS=-Wall -Wextra -O2 --std=c11

BIN=a.elf

HEADERDIR=.
SOURCEDIR=.
BUILDDIR=build


SOURCES= $(wildcard *.c)\
	$(wildcard src/*.c)\
	$(wildcard src/ds18b20/src/*.c)\
	$(wildcard src/read_thread/src/*.c)\
	$(wildcard src/utils/src/*.c)


OBJECTS= $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SOURCES)) )


all: bin run

# all: 
# 	@echo $(SOURCES)
# 	@echo $(OBJECTS)

nrun: bin

bin: $(BIN)

run: $(BIN)
	./$(BIN)

$(BIN): $(OBJECTS)
	@echo "linking..."
	@$(CC) $(CFLAGS) -o $@ $^ -lm -lpthread

$(BUILDDIR)/%.o: ./%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: src/ds18b20/src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: src/read_thread/src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: src/utils/src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

