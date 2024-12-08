CC = gcc
IN_DATA = input
OUT = prog
SRC = main.c

all: $(OUT)

$(OUT): main.c $(IN_DATA) Makefile
	$(CC) $(SRC) -o $(OUT)
	./$(OUT) $(IN_DATA)