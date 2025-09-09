# C++ std::set Examples and Iterable Elements

This directory contains practical examples demonstrating C++ `std::set` and its iterable properties.

## Files Overview

### 1. `basic_set_usage.cpp`
**Purpose**: Fundamental introduction to std::set operations and iteration patterns

**Key Concepts Demonstrated:**
- Basic set creation and element insertion
- Automatic sorting behavior
- Multiple iteration methods (range-based, traditional iterators, const iterators)
- Reverse iteration capabilities
- Search operations (`find()`)
- Range queries (`lower_bound()`, `upper_bound()`)

**Example Output:**
```
=== Basic std::set Operations ===
Set size: 5
Elements are automatically sorted!

=== Different Iteration Methods ===
Range-based for loop: apple banana cherry date 
Traditional iterator: apple banana cherry date 
Const iterator: apple banana cherry date 
Reverse iteration: date cherry banana apple 
```

### 2. `advanced_iteration.cpp`
**Purpose**: Advanced iteration techniques and STL algorithm integration

**Key Concepts Demonstrated:**
- STL algorithm usage (`std::for_each`, `std::count_if`, `std::find_if`, `std::accumulate`)
- Conditional iteration and filtering
- Safe element erasure during iteration
- Iterator arithmetic limitations and solutions (`std::advance`, `std::distance`)
- Iterator invalidation rules
- Bidirectional iterator features

**Important Patterns:**
```cpp
// Safe erasure during iteration
for (auto it = numbers.begin(); it != numbers.end();) {
    if (*it % 2 == 0) {
        it = numbers.erase(it); // erase returns next iterator
    } else {
        ++it;
    }
}
```

### 3. `custom_comparators.cpp`
**Purpose**: Custom ordering and comparison strategies with iterable elements

**Key Concepts Demonstrated:**
- Default vs custom comparators
- Case-insensitive string comparison
- Custom object comparators
- Lambda comparators (C++11)
- Impact of comparators on iteration order
- Iterator consistency across different orderings

**Example Comparators:**
- Age-then-name sorting for Person objects
- String length-based sorting
- Last character-based sorting
- Case-insensitive string sorting

## Compilation and Execution

### Using the Makefile

```bash
# Compile all examples
make all

# Run all examples in sequence
make run-all

# Run individual examples
make run-basic
make run-advanced
make run-comparators

# Clean compiled files
make clean

# Show help
make help
```

### Manual Compilation

```bash
# Individual compilation
g++ -std=c++11 -Wall -Wextra -O2 -o basic_set_usage examples/basic_set_usage.cpp
g++ -std=c++11 -Wall -Wextra -O2 -o advanced_iteration examples/advanced_iteration.cpp
g++ -std=c++11 -Wall -Wextra -O2 -o custom_comparators examples/custom_comparators.cpp

# Execute
./basic_set_usage
./advanced_iteration
./custom_comparators
```

## Key Learning Points

### 1. Iterator Types and Capabilities
- **Bidirectional Iterators**: Can move forward and backward, but not by arbitrary amounts
- **Iterator Invalidation**: Only the erased element's iterator becomes invalid
- **Const Correctness**: Use `const_iterator` when not modifying elements

### 2. Iteration Patterns
```cpp
// Range-based for loop (preferred for simple cases)
for (const auto& element : mySet) {
    // Process element
}

// Traditional iterator (more control)
for (auto it = mySet.begin(); it != mySet.end(); ++it) {
    // Process *it
}

// Reverse iteration
for (auto it = mySet.rbegin(); it != mySet.rend(); ++it) {
    // Process *it in reverse order
}
```

### 3. STL Algorithm Integration
std::set iterators work seamlessly with STL algorithms:
```cpp
// Count elements matching criteria
auto count = std::count_if(mySet.begin(), mySet.end(), predicate);

// Transform elements (read-only)
std::for_each(mySet.begin(), mySet.end(), [](const auto& elem) {
    std::cout << elem << " ";
});

// Find specific elements
auto found = std::find_if(mySet.begin(), mySet.end(), predicate);
```

### 4. Custom Comparators Impact
- Comparators only affect the **ordering** of elements
- All **iteration interfaces remain identical**
- Different comparators can create completely different orderings from the same data

## Best Practices Demonstrated

1. **Safe Iteration**: Proper handling of iterator invalidation
2. **Efficient Search**: Using set-specific methods like `find()`, `lower_bound()`, `upper_bound()`
3. **Range Operations**: Leveraging iterator ranges for partial set operations
4. **Algorithm Integration**: Using STL algorithms for complex operations
5. **Custom Ordering**: Implementing comparators for domain-specific sorting requirements

## Compatibility

- **C++ Standard**: C++11 and later (for range-based for loops and lambda expressions)
- **Compiler**: Any standards-compliant C++ compiler (g++, clang++, MSVC)
- **STL**: Standard Template Library (included with standard C++ implementations)

These examples provide a comprehensive foundation for understanding how std::set implements iterable elements and how to effectively use iteration patterns in real-world C++ applications.