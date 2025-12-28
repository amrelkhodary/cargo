# Project Configuration
PROJECT_NAME = cargo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -O2
DEBUG_FLAGS = -g -DDEBUG -O0
INCLUDE_FLAGS = -Iheaders -Iheaders/extract -Iheaders/validate

# Directory Structure
SRC_DIR = src
HEADER_DIR = headers
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj
DOCS_DIR = docs

# Source Files
MAIN_SRC = $(SRC_DIR)/main.c
CARGO_SRC = $(SRC_DIR)/cargo_errors.c
EXTRACT_SRC = $(wildcard $(SRC_DIR)/extract/*.c)
VALIDATE_SRC = $(wildcard $(SRC_DIR)/validate/*.c)

# All source files
SRCS = $(MAIN_SRC) $(CARGO_SRC) $(EXTRACT_SRC) $(VALIDATE_SRC)

# Object files (derived from source files)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Header files for dependency tracking
HEADERS = $(wildcard $(HEADER_DIR)/*.h) \
          $(wildcard $(HEADER_DIR)/extract/*.h) \
          $(wildcard $(HEADER_DIR)/validate/*.h)

# Target executable
TARGET = $(BIN_DIR)/$(PROJECT_NAME)

# Phony targets
.PHONY: all clean debug release install uninstall docs help test run

# Default target
all: release

# Release build
release: CFLAGS += -DNDEBUG
release: $(TARGET)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

# Link the executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	@echo "Linking $@..."
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "Build successful: $@"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# Create necessary directories
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/extract
	@mkdir -p $(OBJ_DIR)/validate

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BIN_DIR)
	@rm -f $(TARGET)
	@echo "Clean complete."

# Generate documentation with Doxygen
docs:
	@echo "Generating documentation..."
	@if [ -f Doxyfile ]; then \
		doxygen Doxyfile; \
		echo "Documentation generated in $(DOCS_DIR)"; \
	else \
		echo "Error: Doxyfile not found"; \
		exit 1; \
	fi

# Run the program
run: $(TARGET)
	@echo "Running $(PROJECT_NAME)..."
	@./$(TARGET)

# Install (adjust PREFIX as needed)
PREFIX ?= /usr/local
install: release
	@echo "Installing $(PROJECT_NAME) to $(PREFIX)/bin..."
	@install -d $(PREFIX)/bin
	@install -m 755 $(TARGET) $(PREFIX)/bin/
	@echo "Installation complete."

# Uninstall
uninstall:
	@echo "Uninstalling $(PROJECT_NAME) from $(PREFIX)/bin..."
	@rm -f $(PREFIX)/bin/$(PROJECT_NAME)
	@echo "Uninstall complete."

# Test target (placeholder - add your test commands)
test: $(TARGET)
	@echo "Running tests..."
	@# Add your test commands here
	@echo "Tests complete."

# Display help information
help:
	@echo "Available targets:"
	@echo "  all (default) - Build release version"
	@echo "  release       - Build optimized release version"
	@echo "  debug         - Build debug version with symbols"
	@echo "  clean         - Remove build artifacts"
	@echo "  docs          - Generate documentation with Doxygen"
	@echo "  run           - Build and run the program"
	@echo "  test          - Run tests"
	@echo "  install       - Install to $(PREFIX)/bin"
	@echo "  uninstall     - Remove from $(PREFIX)/bin"
	@echo "  help          - Show this help message"
	@echo ""
	@echo "Variables:"
	@echo "  CC            - Compiler (default: gcc)"
	@echo "  CFLAGS        - Compilation flags"
	@echo "  PREFIX        - Install prefix (default: /usr/local)"

# Show compilation database info
print-%:
	@echo $* = $($*)