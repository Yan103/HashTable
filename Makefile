CC        = g++
AS        = nasm
CFLAGS    = -O3 -I$(INC_DIR)
ASFLAGS   = -f elf64
SRC_DIR   = src
INC_DIR   = include
OBJ_DIR   = obj
BIN_DIR   = build
SOURCES   = $(wildcard $(SRC_DIR)/*.cpp)
ASMSRCS   = $(wildcard $(SRC_DIR)/*.asm)
INCLUDES  = $(wildcard $(INC_DIR)/*.h)
OBJECTS   = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
ASMOBJS   = $(ASMSRCS:$(SRC_DIR)/%.asm=$(OBJ_DIR)/%.o)
EXECUTABLE= $(BIN_DIR)/hashtable

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(ASMOBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(OBJ_DIR)
	@$(AS) $(ASFLAGS) $< -o $@

run: $(EXECUTABLE)
	@./$(EXECUTABLE)

clean:
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)