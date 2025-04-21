CC = gcc
FLAGS = -Wall -Wextra -g -std=c11 -DDEBUG

DATA_DIR = ./data
INCLUDE_DIR = ./include
SRC_DIR = ./src
TEST_DIR = ./tests
BUILD_DIR = ./build
BIN_DIR = ./bin
BUILD_SRC_DIR = $(BUILD_DIR)/src
BUILD_TEST_DIR = $(BUILD_DIR)/tests

LIB_SRC := $(shell find $(SRC_DIR) -name "*.c" ! -name "main.c")
TEST_RUNNER_SRC :=  $(TEST_DIR)/test_runner.c
TEST_SRC := $(shell find $(TEST_DIR) -name "*.c" ! -name "*_runner*")
MAIN_SRC := $(shell find $(SRC_DIR) -name "main.c")
ALL_SRC := $(LIB_SRC) $(TEST_SRC) $(TEST_RUNNER_SRC) $(MAIN_SRC)

LIB_OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_SRC_DIR)/%.o,$(LIB_SRC))
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c,$(BUILD_TEST_DIR)/%.o,$(TEST_SRC))
TEST_RUNNER_OBJ := $(patsubst $(TEST_DIR)/%.c,$(BUILD_TEST_DIR)/%.o,$(TEST_RUNNER_SRC))
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

test: $(TEST_TARGET) $(TARGET) | prepare-dirs
	$(TEST_TARGET)

$(TEST_TARGET): $(LIB_OBJ) $(TEST_OBJ) $(TEST_RUNNER_OBJ) | prepare-dirs
	$(CC) $(FLAGS) $^ -o $@ -lcunit

$(BUILD_TEST_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

init-data:
	@mkdir -p $(DATA_DIR)/input $(DATA_DIR)/output
	@printf "2 2\n1 2\n3 4" > $(DATA_DIR)/input/A.txt
	@printf "2 2\n5 6\n7 8" > $(DATA_DIR)/input/B.txt
	@printf "2 2\n1 1\n1 1" > $(DATA_DIR)/input/C.txt
	@printf "2 2\n1 2\n4 5" > $(DATA_DIR)/input/D.txt
	@echo "Тестовые данные созданы в $(DATA_DIR)/input/"

clean:
	rm -rf $(BUILD_DIR)/*

cleanf:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

check-format:
	@echo "Checking code style..."
	@find "./" -name '*.c' -o -name '*.h' | \
	xargs clang-format --style=file --dry-run -Werror

format:
	@echo "Reformatting code..."
	@find "./" -name '*.c' -o -name '*.h' | \
	xargs clang-format --style=file -i -Werror

.PHONY: all rebuild test clean cleanf check-format format
