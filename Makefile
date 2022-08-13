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

TEST_OBJ = testbyte.o testcpu.o
TESTOBJ = $(patsubst %,$(TESTODIR)/%,$(TEST_OBJ))
TESTEXEC = $(patsubst %.o,$(TESTODIR)/%,$(TEST_OBJ))

$(TESTODIR)/%.o: $(TESTIDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# $(wordlist 2,$(words $(OBJ)),$(OBJ)) gets objects without main.o object
$(TESTEXEC): %: %.o $(wordlist 2,$(words $(OBJ)),$(OBJ))
	$(CC) -o $@ $^ $(CFLAGS) $(TESTLIBS) $(LIBS)

.PHONY: clean
.PHONY: format
.PHONY: test_build
.PHONY: test_run
.PHONY: test
.PHONY: all
.PHONY: dummy

# just a dummy target to suppress 'Nothing to be done' message
dummy:
	@:

clean:
	rm -rf main $(ODIR)/*.o $(TESTODIR)/* *~ $(IDIR)/*~ $(TESTIDIR)/*~

format: dummy
	$(shell sed -i 's/\s*$$//g' $(IDIR)/*)
	$(shell sed -i 's/\s*$$//g' $(TESTIDIR)/*)
	$(info Removing trailing whitespaces in source and test files)

test_build: $(TESTEXEC)
define log_and_run =
	$(info Running test cases from executable $1)
	$1
endef
test_run:
	$(foreach testfile,$(TESTEXEC),$(call log_and_run,$(testfile)))
test: test_build test_run

all: main test
