NAME = shell

TARGET_DIR = bin
OBJ_DIR = obj

MAIN_SRC = src/main.c
MAIN_OBJ = $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(MAIN_SRC)))

SRC = $(filter-out $(MAIN_SRC),$(wildcard src/*.c) $(wildcard src/*/*.c))
OBJ = $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRC)))
HEADERS = $(wildcard include/*.h) $(wildcard include/*/*.h)
TARGET = $(TARGET_DIR)/$(NAME)

TESTS_DIR = tests
TESTS_SRC_ = $(wildcard $(TESTS_DIR)/*_test.c) $(wildcard $(TESTS_DIR)/*/*_test.c) \
				$(wildcard $(TESTS_DIR)/*_tests.c) $(wildcard $(TESTS_DIR)/*/*_tests.c)
TESTS_SRC = $(TESTS_SRC_:$(TESTS_DIR)/%=%)
TESTS_OBJ = $(addprefix $(TESTS_DIR)/$(OBJ_DIR)/, $(patsubst %.c, %.o, $(TESTS_SRC)))
TESTS_TARGETS = $(addprefix $(TESTS_DIR)/$(TARGET_DIR)/, $(patsubst %.c, %, $(TESTS_SRC)))

NECESSARY_DIRS = $(dir $(OBJ) $(TARGET)) 
TESTS_NECESSARY_DIRS = $(dir $(TESTS_OBJ) $(TESTS_TARGETS))

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

$(TESTS_DIR)/$(TARGET_DIR)/%: $(TESTS_DIR)/$(OBJ_DIR)/%.o $(OBJ)
	$(CC) $^ -o $@

.PHONY: compile run clean dirs test

compile: $(NECESSARY_DIRS) $(TARGET)

run: compile
	./$(TARGET)

test: $(NECESSARY_DIRS) $(TESTS_NECESSARY_DIRS) $(TESTS_TARGETS)
	@for target in $(TESTS_TARGETS) ; do \
		echo Running tests in $(subst $(TARGET_DIR),,$$target) ; \
		./$$target; \
	done

clean:
	rm -rf obj bin
	rm -rf tests/obj tests/bin
