all: build run

IMAGE = i8080_test

ifeq ($(OS),Windows_NT)
  EXE = .exe
  CC = cl /O2 -Fe$(IMAGE).exe
else
  RUN_PREFIX = ./
  CC = cc -O3 -o $(IMAGE)
endif

FILES = \
  i8080.c \
  i8080_hal.c \
  i8080_test.c

build:
	$(CC) $(FILES)

run:
	$(RUN_PREFIX)$(IMAGE)$(EXE)

clean:
	-rm $(IMAGE)$(EXE)

include Makefile.wasm
