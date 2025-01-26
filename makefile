SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = headers

CC = gcc
CFLAGS = -I$(INCLUDE_DIR) `sdl2-config --libs --cflags` -ggdb3 -O2 -std=c99 -Wall
LIBS = -lm -lSDL2_image -lSDL2_ttf

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

TARGET = a

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(CFLAGS) $(LIBS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
