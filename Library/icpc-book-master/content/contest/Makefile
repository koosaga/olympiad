CXX = g++
CXXFLAGS = -O2 -std=gnu++14 -Wall -Wextra -Wno-unused-result -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align
# pause:#pragma GCC diagnostic {ignored|warning} "-Wshadow"
DEBUGFLAGS = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -D_FORTIFY_SOURCE=2
CXXFLAGS += $(DEBUGFLAGS) # flags with speed penalty
TARGET := $(notdir $(CURDIR))
EXECUTE := ./$(TARGET)
CASES := $(sort $(basename $(wildcard *.in)))
TESTS := $(sort $(basename $(wildcard *.out)))
all: $(TARGET)
clean:
	-rm -rf $(TARGET) *.res
%: %.cpp
	$(LINK.cpp) $< $(LOADLIBES) $(LDLIBS) -o $@
run: $(TARGET)
	time $(EXECUTE)
%.res: $(TARGET) %.in
	time $(EXECUTE) < $*.in > $*.res
%.out: %
test_%: %.res %.out
	diff $*.res $*.out
runs: $(patsubst %,%.res,$(CASES))
test: $(patsubst %,test_%,$(TESTS))
.PHONY: all clean run test test_% runs
.PRECIOUS: %.res
