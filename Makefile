#-------------------------------------------------------------------------
#      --- Makefile used for building and testing datastructs lib ---
# 
# Use: make [targets] (options)
#
# Targets:
#	   <FILE.o> - Build <FILE.o> object file
#      lib      - Builds and generates libdatastructs.a library
#      test     - Builds and run unit tests (run all tests by default)
#      debug    - Create objects files with debug information
#      doc      - Generate Doxygen documentation (in doc/ folder)
#      clean    - Removes all generated files
#
# Options:
#      COV - Generate code coverage info
#
# Author: agnavarro (rtlogik) - contact@rtlogik.com
#-------------------------------------------------------------------------

# Compiler Defines:
CC       = gcc
LINK     = gcc
ARCHIVE  = ar cr
CPPFLAGS = -I. -I$(UNITY_PATH) -Iinclude
CFLAGS   = -c -Wall -O2
DBGFLAGS = -g -O0 
LDFLAGS  =
ifdef COV
   LDFLAGS += --coverage
   CFLAGS  += --coverage
endif

# Specify Paths:
SRC_PATH   = src/
TESTS_PATH = tests/
UNITY_PATH = tests/unity/
BUILD_PATH = build/
OBJS_PATH  = build/objs/
RES_PATH   = build/results/
DEBUG_PATH = debug/
DOC_PATH   = doc/

BUILD_DIRS = $(BUILD_PATH) $(OBJS_PATH) $(RES_PATH)

# Specify Targets:
TARGET          = $(BUILD_PATH)libdatastructs.a
TEST_TARGET     = $(BUILD_PATH)run_tests.out
TEST_TARGET_DBG = $(DEBUG_PATH)run_tests.out

# Specify Source Files:
SRC       = $(wildcard $(SRC_PATH)*.c)
TEST_SRC  = $(wildcard $(TESTS_PATH)*.c)

# Specify Objects:
OBJS_SRC   = $(patsubst $(SRC_PATH)%.c,$(OBJS_PATH)%.o,$(SRC))
OBJS_TEST  = $(patsubst $(TESTS_PATH)%.c,$(OBJS_PATH)%.o,$(TEST_SRC))
OBJS_UNITY = $(OBJS_PATH)unity.o $(OBJS_PATH)unity_fixture.o $(OBJS_PATH)unity_memory.o

OBJS     = $(OBJS_SRC) $(OBJS_TEST) $(OBJS_UNITY)
OBJS_DBG = $(patsubst $(OBJS_PATH)%.o,$(DEBUG_PATH)%.o,$(OBJS))

# Tests results are stored in test_info.txt:
RESULTS = $(RES_PATH)test_info.txt

# Search the test results for passed, failed and ignored tests:
PASSED = `grep -s PASS $(RES_PATH)test_info.txt`
FAIL   = `grep -s FAIL $(RES_PATH)test_info.txt`
IGNORE = `grep -s IGNORE $(RES_PATH)test_info.txt`

#--------------------------------------#
#                 RULES                #
#--------------------------------------#

#
# Library build settings:
#
.PHONY: lib
lib: $(BUILD_DIRS) $(OBJS_SRC)
	$(ARCHIVE) $(TARGET) $(OBJS_SRC)

$(OBJS_PATH)%.o:: $(SRC_PATH)%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

# Create needed directories (if they aren't made):
$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)


#
# Test build settings:
#
.PHONY: test
test: $(BUILD_DIRS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "\nDONE"

$(RESULTS): $(TEST_TARGET)
	-./$< -v > $@ 2>&1

$(TEST_TARGET): $(OBJS)
	$(LINK) $(LDFLAGS) -o $@ $^

$(OBJS_PATH)%.o:: $(TESTS_PATH)%.c		          # COMPROBAR SI PUEDO QUITAR EL TEST_
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

#$(OBJS_PATH)run_test.o:: $(TESTS_PATH)run_test.c    # COMPROBAR SI PUEDO BORRAR!! Y LOS ::
#	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

$(OBJS_PATH)%.o:: $(UNITY_PATH)%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

$(RES_PATH):
	mkdir -p $(RES_PATH)


#
# Debug build settings:
#
.PHONY: debug
debug: $(DEBUG_PATH) $(TEST_TARGET_DBG)

$(TEST_TARGET_DBG): $(OBJS_DBG)
	$(LINK) $(LDFLAGS) -o $@ $^

$(DEBUG_PATH)%.o:: $(TESTS_PATH)%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DBGFLAGS) $< -o $@

$(DEBUG_PATH)%.o:: $(SRC_PATH)%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DBGFLAGS) $< -o $@

$(DEBUG_PATH)%.o:: $(UNITY_PATH)%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DBGFLAGS) $< -o $@

$(DEBUG_PATH):
	mkdir -p $(DEBUG_PATH)


#
# Doxygen documentation build settings:
#
.PHONY: doc
doc: $(DOC_PATH)Doxyfile
	doxygen $(DOC_PATH)Doxyfile


#
# Clean settings:
#
.PHONY: clean
clean:
	rm -rf $(BUILD_PATH)* && rmdir $(BUILD_PATH)
	rm -rf $(DEBUG_PATH)* && rmdir $(DEBUG_PATH)
	rm -rf $(DOC_PATH)html/* && rmdir $(DOC_PATH)html/


# Tell Make not to erase intermediate files:
.PRECIOUS: $(BUILD_PATH)%.out
.PRECIOUS: $(OBJS_PATH)%.o
.PRECIOUS: $(RES_PATH)%.txt
.PRECIOUS: $(DEBUG_PATH)%.o

