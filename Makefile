# Makefile for C++ std::set Examples
# Demonstrates compilation and execution of std::set and iterator examples

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
SRCDIR = examples
BINDIR = bin

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
# Binary names (without .cpp extension)
BINARIES = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%,$(SOURCES))

# Default target
.PHONY: all
all: $(BINDIR) $(BINARIES)

# Create bin directory
$(BINDIR):
	mkdir -p $(BINDIR)

# Rule to compile each source file
$(BINDIR)/%: $(SRCDIR)/%.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Run all examples
.PHONY: run-all
run-all: all
	@echo "=== Running Basic Set Usage Example ==="
	@./$(BINDIR)/basic_set_usage
	@echo ""
	@echo "=== Running Advanced Iteration Example ==="
	@./$(BINDIR)/advanced_iteration
	@echo ""
	@echo "=== Running Custom Comparators Example ==="
	@./$(BINDIR)/custom_comparators

# Individual run targets
.PHONY: run-basic
run-basic: $(BINDIR)/basic_set_usage
	@echo "=== Running Basic Set Usage Example ==="
	@./$(BINDIR)/basic_set_usage

.PHONY: run-advanced
run-advanced: $(BINDIR)/advanced_iteration
	@echo "=== Running Advanced Iteration Example ==="
	@./$(BINDIR)/advanced_iteration

.PHONY: run-comparators
run-comparators: $(BINDIR)/custom_comparators
	@echo "=== Running Custom Comparators Example ==="
	@./$(BINDIR)/custom_comparators

# Clean compiled binaries
.PHONY: clean
clean:
	rm -rf $(BINDIR)

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all            - Compile all examples"
	@echo "  run-all        - Compile and run all examples"
	@echo "  run-basic      - Compile and run basic set usage example"
	@echo "  run-advanced   - Compile and run advanced iteration example"
	@echo "  run-comparators - Compile and run custom comparators example"
	@echo "  clean          - Remove compiled binaries"
	@echo "  help           - Show this help message"

# Show compiler and flags info
.PHONY: info
info:
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Source directory: $(SRCDIR)"
	@echo "Binary directory: $(BINDIR)"
	@echo "Source files:"
	@for src in $(SOURCES); do echo "  $$src"; done