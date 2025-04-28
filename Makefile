CC        = g++
CFLAGS    = -DDEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations   \
            -Wc++14-compat -Wmissing-declarations -Wcast-align -Wchar-subscripts                   \
            -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal  \
            -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline          \
            -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked            \
            -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo  \
            -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn                \
            -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default      \
            -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast           \
            -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing   \
            -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation    \
            -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wstack-usage=8192         \
            -fsanitize=address -fsanitize=undefined -fPIE -Werror=vla
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