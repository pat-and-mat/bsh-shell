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
TESTS_SRC_ = $(wildcard $(TESTS_DIR)/*.test.c) \
				$(wildcard $(TESTS_DIR)/*/*.test.c) \
				$(wildcard $(TESTS_DIR)/*/*/*.test.c)
TESTS_SRC = $(TESTS_SRC_:$(TESTS_DIR)/%=%)
TESTS_OBJ = $(addprefix $(TESTS_DIR)/$(OBJ_DIR)/, $(patsubst %.c, %.o, $(TESTS_SRC)))
TESTS_TARGETS = $(addprefix $(TESTS_DIR)/$(TARGET_DIR)/, $(patsubst %.c, %, $(TESTS_SRC)))
TESTS_TARGETS_ = $(TESTS_TARGETS:$(TESTS_DIR)/$(TARGET_DIR)/%=%)

NECESSARY_DIRS = $(dir $(OBJ) $(TARGET)) 
TESTS_NECESSARY_DIRS = $(dir $(TESTS_OBJ) $(TESTS_TARGETS)) $(TESTS_DIR)/log

CC = gcc
CFLAGS = -c -Iinclude

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

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

clean:
	rm -rf obj bin
	rm -rf tests/obj tests/bin tests/log

compile: $(NECESSARY_DIRS) $(TARGET)

run: compile
	./$(TARGET)

test: $(NECESSARY_DIRS) $(TESTS_NECESSARY_DIRS) $(TESTS_TARGETS)
	@for target in $(TESTS_TARGETS_) ; do \
		echo; \
		echo -----------------------------------------; \
		if ./$(TESTS_DIR)/$(TARGET_DIR)/$$target; then \
			echo; \
			echo Test on $$target succeded; \
		else \
			echo; \
			echo Test on $$target failed; \
		fi; \
		echo Running memory test on $$target; \
		install -D /dev/null $(TESTS_DIR)/log/$$target.log; \
		$(VALGRIND) --log-file=$(TESTS_DIR)/log/$$target.log ./$(TESTS_DIR)/$(TARGET_DIR)/$$target > /dev/null; \
		echo; \
	done;
