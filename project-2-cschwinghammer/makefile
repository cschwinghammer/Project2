# Macros ========================================
# - Name ========================================
EXE:=cachelist
TEST_EXE:=$(EXE)-test

# - Compilers Versions ==========================
CC:=clang-10
CXX:=clang++-10

# - Language Versions ===========================
CC_VERSION:=c11
CXX_VERSION:=c++11

# - Compilers Flags & Options ===================
CFLAGS:=-Wall -Wextra -std=$(CC_VERSION) -pedantic -g -O2 -Werror
CXXFLAGS:=-Wall -Wextra -std=$(CXX_VERSION) -g -O2 -Werror -x c++
LFLAGS:=-lpthread
VALIGRIND_OPTIONS:=-q --leak-check=full --show-reachable=yes --tool=memcheck

# - Directories =================================
OUT:=out
BIN:=bin
DOCS:=docs
SRC:=src
TEST:=$(SRC)/test

# - Files =======================================
TEST_FILES=$(SRC)/test/tests.cpp
SRC_FILES=$(SRC)/cachelist.c $(SRC)/PRNG.c
OBJS=$(OUT)/cachelist.o $(OUT)/sample-driver.o $(OUT)/PRNG.o

# - Commands ====================================
ERASE=rm


# VERIFY COMPILERS ==============================
$(call check_defined, CC, no C compiler set)
$(call check_defined, CXX, no C++ compiler set)


# PHONY TARGETS ================================= 
#   These don't have output files associated with the exact target name
.PHONY: $(EXE) $(TEST_EXE) test list clean run diff valgrind doxygen


# BUILD TARGETS =================================
all : $(EXE) $(TEST_EXE)

do-everything : run/0 test/0

$(OUT)/ :
	mkdir -p $(OUT)
	mkdir -p $(OUT)
	mkdir -p $(DOCS)
	mkdir -p $(DOCS)

$(EXE) : $(OUT)/$(EXE)
	
$(OUT)/$(EXE) : $(OBJS)
	$(CC) $(OBJS) -o $(OUT)/$(EXE) $(LFLAGS) 
	cp ./$(OUT)/$(EXE) ./$(BIN)/$(EXE)

$(OUT)/sample-driver.o : $(SRC)/sample-driver.c $(SRC)/cachelist.h $(SRC)/PRNG.h $(OUT)/
	$(CC) $(CFLAGS) -c $(SRC)/sample-driver.c -o $(OUT)/sample-driver.o

$(OUT)/cachelist.o : $(SRC)/cachelist.c $(SRC)/cachelist.h $(OUT)/
	$(CC) $(CFLAGS) -c $(SRC)/cachelist.c -o $(OUT)/cachelist.o

$(OUT)/PRNG.o : $(SRC)/PRNG.c $(SRC)/PRNG.h $(OUT)/
	$(CC) $(CFLAGS) -c $(SRC)/PRNG.c -o $(OUT)/PRNG.o

# TEST BUILD TARGETS ============================
$(TEST_EXE) : $(OUT)/$(TEST_EXE)
	 
$(OUT)/$(TEST_EXE) : $(TEST_FILES) $(SRC_FILES) $(OUT)/ 
	$(CXX) $(CXXFLAGS) $(TEST_FILES) $(SRC_FILES) -o $(OUT)/$(TEST_EXE) -I$(TEST)/infrastructure -I$(SRC) $(LFLAGS)

# RUN/COMMAND TARGETS ===========================
run : run/0

test : test/all

diff : diff/0

run/% : $(OUT)/$(EXE) 
	./$(OUT)/$(EXE) $(subst run/,,$(subst .o,0,$@))

diff/% : $(OUT)/$(EXE)
	./$(OUT)/$(EXE) $(subst diff/,,$(subst .o,0,$@)) > $(OUT)/_out-$(subst diff/,,$(subst .o,0,$@)).txt
	diff .grading/test-out/$(OUT_$(subst diff/,,$(subst .o,0,$@))).txt $(OUT)/_out-$(subst diff/,,$(subst .o,0,$@)).txt > $(OUT)/_diff-$(subst diff/,,$(subst .o,0,$@)).txt

test/% : $(OUT)/$(TEST_EXE)  # add the "-s" option to enable displaying passed test information
	./$(OUT)/$(TEST_EXE) "$(subst [],,[$(subst test/,,$(subst .o,,$@))])" # -s

list/test-tags test/test-names : $(OUT)/$(TEST_EXE)
	./$(OUT)/$(TEST_EXE) --list-$(subst test/list/,,$@)

valgrind/$(EXE) : $(OUT)/$(EXE)
	valgrind $(VALIGRIND_OPTIONS) ./$(OUT)/$(EXE)

valgrind/$(TEST_EXE) : $(OUT)/$(TEST_EXE)
	valgrind $(VALIGRIND_OPTIONS) ./$(OUT)/$(TEST_EXE)

doxygen : $(OUT)/
	doxygen
	cd latex && $(MAKE) && cp refman.pdf ../$(DOCS)/refman.pdf

clean :
	$(ERASE) -rf ./$(OUT)/* ./$(BIN)/* ./latex/

do-everything: diff/0 test/all valgrind/$(EXE) valgrind/$(TEST_EXE) doxygen



# Output Files Lookup ==========================================
OUT_0=output-all
OUT_1=output-add_front
OUT_2=output-add_end
OUT_3=output-remove1
OUT_4=output-remove2
OUT_5=output-insert_before1
OUT_6=output-insert_after1
OUT_7=output-find1
OUT_8=output-find2
OUT_9=output-find_stress1
OUT_10=output-find_stress2
OUT_11=output-test_stress1
OUT_12=output-test_a_lot
OUT_13=output-all
