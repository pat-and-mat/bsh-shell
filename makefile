NAME = shell

TARGET_DIR = bin
OBJ_DIR = obj

MAIN_SRC = src/main.c
MAIN_OBJ = $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(MAIN_SRC)))

SRC = $(filter-out $(MAIN_SRC),$(wildcard src/*.c) $(wildcard src/*/*.c))
OBJ = $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRC)))
HEADERS = $(wildcard include/*.h) $(wildcard include/*/*.h)
TARGET = $(TARGET_DIR)/$(NAME)

TESTS_NAME = tests
TESTS_DIR = tests
TESTS_SRC_ = $(wildcard $(TESTS_DIR)/*.c) $(wildcard $(TESTS_DIR)/*/*.c)
TESTS_SRC = $(TESTS_SRC_:$(TESTS_DIR)/%=%)
TESTS_OBJ = $(addprefix $(TESTS_DIR)/$(OBJ_DIR)/, $(patsubst %.c, %.o, $(TESTS_SRC)))
TESTS_TARGET = $(TESTS_DIR)/$(TARGET_DIR)/$(TESTS_NAME)

NECESSARY_DIRS = $(dir $(OBJ) $(TARGET)) 
TESTS_NECESSARY_DIRS = $(dir $(TESTS_OBJ) $(TESTS_TARGET))

CC = gcc
CFLAGS = -c -Iinclude

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

$(TARGET): $(OBJ) $(MAIN_OBJ)
	$(CC) $^ -o $@

$(sort $(NECESSARY_DIRS)):
	mkdir -p $@

$(sort $(TESTS_NECESSARY_DIRS)):
	mkdir -p $@

$(TESTS_DIR)/$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

$(TESTS_TARGET): $(TESTS_OBJ) $(OBJ)
	$(CC) $^ -o $@

.PHONY: compile run clean dirs

compile: $(NECESSARY_DIRS) $(TARGET)

run: compile
	./$(TARGET)

test: $(NECESSARY_DIRS) $(TESTS_NECESSARY_DIRS) $(TESTS_TARGET)
	./$(TESTS_TARGET)

clean:
	rm -rf obj bin
	rm -rf tests/obj tests/bin
