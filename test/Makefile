PRODUCT=SluiceTest

CFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -Iproduct -Itest

SOURCES=$(wildcard *.cpp)
        

HEADERS=$(wildcard /*.h)
        

TEST_LIBS=-lgtest -lgmock -lgmock_main -lpthread

CC=g++

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS) Makefile
	@$(CC) $(CFLAGS) $(SOURCES) -o $@ $(TEST_LIBS)

clean:
	@rm -rf $(PRODUCT)

test: $(PRODUCT)
	@./$(PRODUCT)