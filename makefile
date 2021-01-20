SRC := $(shell find src -name '*.c' -type f)
CC := gcc

all: build
	gcc $(SRC) -Iinc -o build/test

build:
	mkdir -p build

clean:
	rm -rf build