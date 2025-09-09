# C++ Set Iterables

A comprehensive C++ library and examples demonstrating various iteration patterns and operations with `std::set` and other STL containers. This project showcases practical techniques for working with set data structures, including filtering, transformation, range queries, and set operations.

## Features

- **Comprehensive Set Operations**: Union, intersection, difference, and more
- **Multiple Iteration Patterns**: Forward, reverse, iterator-based, conditional
- **Filtering and Transformation**: Apply predicates and functions during iteration
- **Range Queries**: Efficient iteration over subsets of data
- **Container Conversion**: Easy conversion between different STL containers
- **Custom Type Support**: Works with user-defined types
- **Performance Optimized**: Demonstrates efficient algorithms and patterns

## Project Structure

```
├── set_iterables.hpp      # Main header with SetIterator class and utilities
├── main.cpp               # Interactive demonstration program
├── basic_examples.cpp     # Basic usage examples
├── advanced_examples.cpp  # Advanced techniques and patterns
├── CMakeLists.txt         # CMake build configuration
├── Makefile              # Simple make-based build
└── README.md             # This file
```

## Building the Project

### Using Make (Recommended)

```bash
# Build all examples
make all

# Build and run all examples
make run_all

# Build and run interactive demo
make demo

# Test compilation
make test_compile

# Show help
make help
```

### Using CMake

```bash
# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run examples
./basic_examples
./advanced_examples
./main
```

### Manual Compilation

```bash
# Compile individual examples
g++ -std=c++17 -Wall -O2 -o main main.cpp
g++ -std=c++17 -Wall -O2 -o basic_examples basic_examples.cpp
g++ -std=c++17 -Wall -O2 -o advanced_examples advanced_examples.cpp
```

## Usage Examples

### Basic Set Operations

```cpp
#include "set_iterables.hpp"
using namespace set_iterables;

// Create a set with some numbers
SetIterator<int> numbers{5, 2, 8, 1, 9, 3, 7};

// Different iteration methods
numbers.iterate_forward();      // Forward iteration
numbers.iterate_reverse();      // Reverse iteration
numbers.iterate_with_iterators(); // Explicit iterator usage
```

### Conditional Iteration

```cpp
// Iterate over even numbers only
numbers.iterate_conditional([](int x) { return x % 2 == 0; }, "Even numbers");

// Apply transformation during iteration
numbers.iterate_and_apply([](int x) { return x * x; }, "Squared values");
```

### Container Conversion

```cpp
// Convert vector to set (removes duplicates, sorts)
std::vector<int> vec{3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
SetIterator<int> from_vector(vec);

// Convert back to vector
auto sorted_unique = from_vector.copy_to_container<std::vector<int>>();
```

### Set Operations

```cpp
SetIterator<int> set1{1, 2, 3, 4, 5, 6};
SetIterator<int> set2{4, 5, 6, 7, 8, 9};

// Demonstrates union, intersection, and difference
set1.demonstrate_set_operations(set2);
```

## Key Classes and Functions

### `SetIterator<T>`

The main class that wraps `std::set<T>` with additional functionality:

- `iterate_forward()` - Range-based forward iteration
- `iterate_reverse()` - Reverse iteration using reverse iterators
- `iterate_conditional(predicate)` - Conditional iteration with filtering
- `iterate_and_apply(function)` - Apply transformation during iteration
- `iterate_range(start, end)` - Iterate over a specific range
- `filter_to_vector(predicate)` - Filter elements to a new vector
- `demonstrate_set_operations(other)` - Show set operations with another set

### Utility Functions

- `utils::iterable_to_set<T>(container)` - Convert any iterable to set
- `utils::print_iterable(container)` - Print any iterable container
- `utils::merge_iterables(containers...)` - Merge multiple iterables into one set

## Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Standard Template Library (STL)

## Running the Examples

### Interactive Demo
```bash
make demo
# Or directly: ./main
```

### All Examples
```bash
make run_all
```

### Individual Examples
```bash
./basic_examples      # Basic iteration patterns
./advanced_examples   # Advanced operations and custom types
```

## Educational Value

This project demonstrates:

- Modern C++ practices and STL usage
- Template programming techniques
- Iterator patterns and algorithms
- Memory-efficient operations with sets
- Custom comparators and user-defined types
- Performance considerations for large datasets

## License

This project is for educational purposes and demonstrates C++ STL container usage patterns.
