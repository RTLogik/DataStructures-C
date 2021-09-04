#-------------------------------------------------------------------------
#      --- Makefile used for building and testing datastr-lib ---
# 
# Use: make [targets] (test-option)
#
# Targets:
#	   <FILE.o> - Build <FILE.o> object file
#      build    - Builds and generates libdata.a library
#      test     - Run unit tests (run all tests by default)
#      clean    - Removes all generated files
#
# Test options:
#      lifo - Run lifo tests
#
# By rtlogik
#-------------------------------------------------------------------------

# Specify Paths:
PATHS = src/
PATHT = tests/
PATHU = tests/unity/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

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
CPPFLAGS = -I. -I$(PATHU) -I$(PATHS)include
LDFLAGS = --coverage

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL   = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

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
	-./$< > $@ 2>&1

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

# Tell Make not to erase intermediate files:
.PRECIOUS: $(PATHB)%.out
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

