CPPFLAGS=-Wall -Wextra -std=c++11
TEST_INCLUDES=-I../../include -I../dependencies/ansa/include
TEST_SOURCES=../../src/util/*.cpp dummy-api/*.cpp build/ansa/*.o build/assert.o
ARCH_FLAG ?= -D__ANARCH_TARGET_X64__

all: build/assert build/stream build/critical

build/assert: ../dependencies build/ansa build/assert.o
	$(CXX) $(ARCH_FLAG) $(CPPFLAGS) $(TEST_INCLUDES) $(TEST_SOURCES) test-assert.cpp -o build/assert

build/stream: ../dependencies build/ansa build/assert.o
	$(CXX) $(ARCH_FLAG) $(CPPFLAGS) $(TEST_INCLUDES) $(TEST_SOURCES) test-stream.cpp -o build/stream

build/critical: ../dependencies build/ansa build/assert.o
	$(CXX) $(ARCH_FLAG) $(CPPFLAGS) $(TEST_INCLUDES) $(TEST_SOURCES) test-critical.cpp -o build/critical

build/ansa: ../dependencies build
	mkdir build/ansa
	../build-objects $(CXX) $(CPPFLAGS) -I../dependencies/ansa/include -c ../dependencies/ansa/src/*.cpp -o build/ansa
	../build-objects $(CC) -I../dependencies/ansa/include -c ../dependencies/ansa/dependencies/anlock/src/*.c -o build/ansa

build/assert.o:
	g++ -c ../assert.cpp -o build/assert.o

../dependencies:
	mkdir ../dependencies
	git clone https://github.com/unixpickle/ansa.git ../dependencies/ansa;

build:
	mkdir build

clean:
	rm -rf build

clean-all:
	rm -rf build
	rm -rf dependencies