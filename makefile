NAME = shell

TARGETDIR = bin
OBJDIR = obj

SRC = $(wildcard src/*.c) $(wildcard src/*/*.c)
OBJ = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(SRC)))
HEADERS = $(wildcard include/*.h) $(wildcard include/*/*.h)
TARGET = $(TARGETDIR)/$(NAME)

NECESSARY_DIRS = $(dir $(OBJ) $(TARGET)) 

CC = gcc
CFLAGS = -c $(addprefix -I, $(dir $(HEADERS)))

$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $^ -o $@

.PHONY: compile run clean dirs

dirs:
	mkdir -p $(NECESSARY_DIRS)

compile: dirs $(TARGET)

run: compile
	./$(TARGET)

clean:
	rm -rf obj bin
