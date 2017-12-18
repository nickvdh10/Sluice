CFLAGS=-Wall -Werror -Wextra -pedantic -O3 -ggdb -fopenmp -std=c++98 -Icode
LDDFLAGS=-lmyhash -lmyfilestructure -lpthread

MAIN_SOURCES=$(wildcard code/*.cpp)
MAIN_LIBS=-Llib

TEST_LIBS=-lgtest -lgtest_main -lpthread

CC=g++

.phony: all clean install submit

sluice: $(MAIN_OBJECTS) 
	@$(CC) $(CFLAGS) $(MAIN_LIBS) $(MAIN_SOURCES) -o $@ $(LDDFLAGS)
	
all: sluice

clean:
	@rm -rf sluice code/*.o test/*.o *.bin

