IDIR = src
CC = gcc
CFLAGS = -I$(IDIR) -Wall -Wpedantic

OBJDIR = obj

ODIR = $(OBJDIR)/$(IDIR)
$(info $(shell mkdir -p $(ODIR)))

LIBS = 

_DEPS = dasm.h cpu.h byte.h memory.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o dasm.o cpu.o byte.o memory.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(IDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

TESTIDIR = test

TESTODIR = $(OBJDIR)/$(TESTIDIR)
$(info $(shell mkdir -p $(TESTODIR)))

TESTLIBS = -lcmocka

TEST_OBJ = testbyte.o
TESTOBJ = $(patsubst %,$(TESTODIR)/%,$(TEST_OBJ))
TESTEXEC = $(patsubst %.o,$(TESTODIR)/%,$(TEST_OBJ))

$(TESTODIR)/%.o: $(TESTIDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# $(wordlist 2,$(words $(OBJ)),$(OBJ)) gets objects without main.o object
$(TESTEXEC): %: $(TESTOBJ) $(wordlist 2,$(words $(OBJ)),$(OBJ))
	$(CC) -o $@ $^ $(CFLAGS) $(TESTLIBS) $(LIBS)

.PHONY: clean
.PHONY: format
.PHONY: test_build
.PHONY: test_run
.PHONY: test

clean:
	rm -rf main $(ODIR)/*.o $(TESTODIR)/* *~ $(IDIR)/*~ $(TESTIDIR)/*~

format:
	$(shell sed -i 's/\s*$$//g' $(IDIR)/*)
	$(shell sed -i 's/\s*$$//g' $(TESTIDIR)/*)

test_build: $(TESTEXEC)
test_run:
	$(foreach testfile,$(TESTEXEC),$(testfile);)
test: test_build test_run
