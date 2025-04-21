CC        = g++
 CFLAGS    = -g -O0 -Wall 
 SRC_DIR   = src
 INC_DIR   = include
 OBJ_DIR   = obj
 BIN_DIR   = build
 SOURCES   = $(wildcard $(SRC_DIR)/*.c)
 INCLUDES  = $(wildcard $(INC_DIR)/*.h)
 OBJECTS   = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
 EXECUTABLE= $(BIN_DIR)/hashtable
 
 all: $(EXECUTABLE)
 
 $(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@
 
 $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -I$(INC_DIR) $< -o $@
 
 run: $(EXECUTABLE)
	@./$(EXECUTABLE)
 
 clean:
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)