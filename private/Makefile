CXX = g++
CXXFLAGS = -Wall -O2 -std=c++11
LFLAGS = 

SOURCES = example.cc
OBJECTS = $(SOURCES:.cc=.o)

all: holding.o

	
holding.o: holding.hh
	$(CXX) $(CXXFLAGS) -c -o $@ $^
	
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJECTS) holding.o example.o
	
objects:
	@echo "$(OBJECTS)"
	
.PHONY: all clean
