SRC_DIR=src
SRC_FILES=$(SRC_DIR)/main.c $(SRC_DIR)/distribute.c $(SRC_DIR)/distribute_internal.c
all: cls build
build:
	gcc -std=c11 -g -O0 -Wall -Werror $(SRC_FILES) -lmpfr -lgmp -o ./build/a.out
cls:
	tput reset
.PHONY: cls build
