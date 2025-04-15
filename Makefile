CC       = gcc
ASM      = nasm
CFLAGS   = -g -O0 -Wall -I$(INC_DIR) -fPIE
ASMFLAGS = -f elf64 -g
LDFLAGS  = -no-pie -lc
SRC_DIR  = src
INC_DIR  = include
OBJ_DIR  = obj
BIN_DIR  = build

C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
#ASM_SOURCES = $(SRC_DIR)/HashTableFind.asm
C_OBJECTS = $(C_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
ASM_OBJECTS = $(ASM_SOURCES:$(SRC_DIR)/%.asm=$(OBJ_DIR)/%.o)
OBJECTS = $(C_OBJECTS) #$(ASM_OBJECTS)
EXECUTABLE = $(BIN_DIR)/hashtable

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) $< -o $@

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
#	@mkdir -p $(@D)
#	@$(ASM) $(ASMFLAGS) $< -o $@

run: $(EXECUTABLE)
	@./$(EXECUTABLE)

clean:
	@rm -rf $(BIN_DIR) $(OBJ_DIR)
