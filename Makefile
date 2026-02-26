# Compiler and flags
CC = mingw64\bin\g++
CFLAGS = -Wall -Werror -Wextra -Iinclude -ISFML-2.6.1\include -LSFML-2.6.1\lib -mwindows -g

# SFML libraries (adjust the path if needed)
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories and files
SRC_DIRS = src gui
SRC_FILES = main.cpp $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Output target
TARGET = main.exe

# Build target
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(SFML_FLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean command for Windows (use cmd-compatible command)
clean:
	del /Q $(subst /,\,$(OBJ_FILES)) $(TARGET) 2> NUL || exit 0
	del .\info\*.txt

# Run the program
run: all
	$(TARGET)

# Rebuild target
rebuild: clean all
