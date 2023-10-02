SRC_DIR = src
BUILD_DIR = build
CC = clang++
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJ_NAME = chip8

INCLUDE_PATHS = -I/Library/Frameworks/SDL2.framework/Headers
FRAMEWORKS_PATHS = -F/Library/Frameworks
COMPILER_FLAGS = -std=c++20 -Wall -O0 -g
FRAMEWORKS_FLAGS = -framework SDL2

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(FRAMEWORKS_PATHS) $(FRAMEWORKS_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)