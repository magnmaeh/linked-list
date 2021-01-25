SRC := $(shell find src -name '*.c' -type f)
SRC += $(shell find examples -name '*.c' -type f)

CC := gcc

all: build
	gcc $(SRC) -Iinc -Iexamples -o build/test

build:
	mkdir -p build

clean:
	rm -rf build