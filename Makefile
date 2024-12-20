# Nome do executável
EXEC = build/jogo.exe

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Flags do compilador
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

# Busca todos os arquivos .c no diretório src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Regra padrão
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LDFLAGS)

# Regra para compilar os arquivos .c em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)

# Limpar tudo (executável e diretório build)
dist-clean: clean
	rm -rf $(BUILD_DIR)

.PHONY: all clean dist-clean
