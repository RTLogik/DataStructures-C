#-------------------------------------------------------------------------
#      --- Makefile used for building and testing datastructs lib ---
# 
# Use: make [targets] (test-option)
#
# Targets:
#	   <FILE.o> - Build <FILE.o> object file
#      build    - Builds and generates libdatastructs.a library
#      test     - Run unit tests (run all tests by default)
#      doc      - Generate Doxygen documentation (in doc/ folder)
#      all      - Builds the library, run tests and generate documentation
#      clean    - Removes all generated files
#
# Test options:
#      lifo - Run lifo tests
#
# Author: agnavarro (rtlogik) - contact@rtlogik.com
#-------------------------------------------------------------------------

# Specify Paths:
PATHS = src/
PATHT = tests/
PATHU = tests/unity/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/
PATHDOC = doc/

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

# Specify Targets, Source Files and Objects:
TARGET = $(PATHB)libdatastr.a
TEST_TARGET = $(PATHB)test_runner.out
SRC   = $(wildcard $(PATHS)*.c)
SRCT  = $(wildcard $(PATHT)*.c)
OBJS  = $(patsubst $(PATHS)%.c,$(PATHO)%.o,$(SRC))
OBJST = $(patsubst $(PATHT)%.c,$(PATHO)%.o,$(SRCT))
OBJSU = $(PATHO)unity.o $(PATHO)unity_fixture.o $(PATHO)unity_memory.o
RESULTS = $(PATHR)test_info.txt

# Compiler Defines:
CC = gcc
LINK = gcc
DEPEND = gcc -MM -MG -MF
CFLAGS = -c -Wall --coverage
CPPFLAGS = -I. -I$(PATHU) -Iinclude
LDFLAGS = --coverage

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL   = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

.PHONY: all
all: doc test

.PHONY: doc
doc: $(PATHDOC)Doxyfile
	doxygen $(PATHDOC)Doxyfile

.PHONY: test
test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"


$(RESULTS): $(TEST_TARGET)
	-./$< -v > $@ 2>&1

$(TEST_TARGET): $(OBJS) $(OBJST) $(OBJSU) #$(PATHD)test_%.d
	$(LINK) $(LDFLAGS) -o $@ $^

$(PATHO)test_%.o:: $(PATHT)test_%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c 
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

#$(PATHD)%.d: $(PATHT)%.c
#	$(DEPEND) $@ $<

# Create build folders (if they aren't made):
$(PATHB):
	mkdir -p $(PATHB)

$(PATHD):
	mkdir -p $(PATHD)

$(PATHO):
	mkdir -p $(PATHO)

$(PATHR):
	mkdir -p $(PATHR)

.PHONY: clean
clean:
	rm -f $(PATHO)*
	rm -f $(PATHB)*.out
	rm -f $(PATHR)*
	rm -rf $(PATHDOC)html/* && rmdir $(PATHDOC)html/


# Tell Make not to erase intermediate files:
.PRECIOUS: $(PATHB)%.out
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

