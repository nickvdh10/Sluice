BINARIES=sluice
CXX=g++ -std=c++11
CXXFLAGS=-g -Wall
LDFLAGS=-lrt -lpthread
SOURCES=$(wildcard Code/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
LIB_OBJECTS=$(wildcard Objects/*.o)

.PHONY: all clean

all:sluice
	@echo "Building All\n"

sluice:$(OBJECTS) $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Building Sluice\n"

cleanandmake:clean sluice
	@echo "Cleaning and Building Automagically\n"

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I.

clean: 
	@rm -rf $(BINARIES) Code/*.o test/*.o
	@echo "Cleaning Build\n"
