SRC = AllTests.cpp
CPPUTEST_DIR = /path/to/CppUTest
CPPFLAGS = -I$(CPPUTEST_DIR)/include
LDFLAGS = -L$(CPPUTEST_DIR)/lib -lCppUTest

all: test

test: $(SRC)
	g++ $(CPPFLAGS) -o test $(SRC) $(LDFLAGS)

clean:
	rm -f test