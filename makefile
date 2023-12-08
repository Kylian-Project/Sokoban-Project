CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lncurses
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Crée les dossiers obj et bin s'ils n'existent pas
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard include/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXEC = $(BIN_DIR)/sokoban

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC) -r $(BIN_DIR) $(OBJ_DIR)