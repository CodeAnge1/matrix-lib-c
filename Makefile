CC = gcc
FLAGS = -Wall -Wextra -g -std=c11 -DDEBUG

INCLUDE_DIR = ./include
SRC_DIR = ./src
TEST_DIR = ./tests
BUILD_DIR = ./build
BIN_DIR = ./bin
BUILD_SRC_DIR = $(BUILD_DIR)/src
BUILD_TEST_DIR = $(BUILD_DIR)/tests

LIB_SRC := $(shell find $(SRC_DIR) -name "*.c" ! -name "main.c")
TEST_SRC := $(shell find $(TEST_DIR) -name "*.c")
MAIN_SRC = $(shell find $(SRC_DIR) -name "main.c")
ALL_SRC = $(LIB_SRC) $(TEST_SRC) $(MAIN_SRC)

LIB_OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_SRC_DIR)/%.o,$(LIB_SRC))
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c,$(BUILD_TEST_DIR)/%.o,$(TEST_SRC))
MAIN_OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_SRC_DIR)/%.o,$(MAIN_SRC))
ALL_OBJ := $(LIB_OBJ) $(TEST_OBJ) $(MAIN_OBJ)

TARGET = $(BIN_DIR)/MatrixLib
TEST_TARGET = $(BIN_DIR)/MatrixLibTest

all: prepare-dirs $(TARGET)

rebuild: cleanf all

prepare-dirs: $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(LIB_OBJ) $(MAIN_OBJ) | prepare-dirs
	$(CC) $(FLAGS) $^ -o $@

test: $(LIB_OBJ) $(TEST_OBJ) | prepare-dirs
	$(CC) $(FLAGS) $^ -o $(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR)/*

cleanf:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

check-format:
	@echo "Checking code style..."
	@find $(INCLUDE_DIR) $(SRC_DIR) $(TEST_DIR) \
	-name '*.c' -o -name '*.h' | \
	xargs clang-format --style=file --dry-run -Werror

format:
	@echo "Reformatting code..."
	@find $(INCLUDE_DIR) $(SRC_DIR) $(TEST_DIR) \
	-name '*.c' -o -name '*.h' | \
	xargs clang-format --style=file -i -Werror

.PHONY: all rebuild test clean cleanf check-format format