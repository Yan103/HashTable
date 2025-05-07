CC        = g++
CFLAGS    = -O2
            
#-fsanitize=address -fsanitize=undefined -fPIE -Werror=vla
SRC_DIR   = src
INC_DIR   = include
OBJ_DIR   = obj
BIN_DIR   = build
SOURCES   = $(wildcard $(SRC_DIR)/*.cpp)
INCLUDES  = $(wildcard $(INC_DIR)/*.h)
OBJECTS   = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE= $(BIN_DIR)/hashtable

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -I$(INC_DIR) $< -o $@

run: $(EXECUTABLE)
	@./$(EXECUTABLE)

clean:
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)