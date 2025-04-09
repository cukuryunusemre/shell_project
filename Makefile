CC=gcc
CFLAGS=-Wall -g `pkg-config --cflags gtk+-3.0`
LIBS=`pkg-config --libs gtk+-3.0` -lrt -pthread

TARGET=main
SRC=src/main.c src/model.c src/view.c src/controller.c
BIN=bin/$(TARGET)

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) $(LIBS)

clean:
	rm -f $(BIN)

run: $(BIN)
	./$(BIN)

