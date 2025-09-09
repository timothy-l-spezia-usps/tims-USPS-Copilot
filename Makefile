# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2
INCLUDES = -I.

# Source files and targets
HEADERS = set_iterables.hpp
SOURCES = main.cpp basic_examples.cpp advanced_examples.cpp test_functionality.cpp
TARGETS = main basic_examples advanced_examples test_functionality

# Default target
all: $(TARGETS)

# Individual targets
main: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $<

basic_examples: basic_examples.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $<

advanced_examples: advanced_examples.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $<

test_functionality: test_functionality.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $<

# Run targets
run_all: $(TARGETS)
	@echo "=== Running Basic Examples ==="
	./basic_examples
	@echo ""
	@echo "=== Running Advanced Examples ==="
	./advanced_examples

demo: main
	./main

# Test compilation only
test_compile: $(TARGETS)
	@echo "All examples compiled successfully!"

# Run tests
test: test_functionality
	./test_functionality

# Clean up
clean:
	rm -f $(TARGETS)

# Install (simple version)
install: $(TARGETS)
	mkdir -p bin include
	cp $(TARGETS) bin/
	cp $(HEADERS) include/

# Show help
help:
	@echo "Available targets:"
	@echo "  all           - Build all examples"
	@echo "  main          - Build interactive demo"
	@echo "  basic_examples- Build basic examples"
	@echo "  advanced_examples - Build advanced examples"
	@echo "  run_all       - Build and run all examples"
	@echo "  demo          - Build and run interactive demo"
	@echo "  test_compile  - Test that everything compiles"
	@echo "  clean         - Remove all built files"
	@echo "  install       - Install binaries and headers"
	@echo "  help          - Show this help message"
	@echo "  test          - Build and run functionality tests"

.PHONY: all run_all demo test_compile test clean install help