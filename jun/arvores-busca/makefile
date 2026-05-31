CC      = gcc
CFLAGS  = -Wall -Wextra -O2
SRC_DIR = src
SRCS    = $(SRC_DIR)/main.c $(SRC_DIR)/arvore.c $(SRC_DIR)/buscas.c
TARGET  = experimento

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean