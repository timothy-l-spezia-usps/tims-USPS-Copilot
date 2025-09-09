#include "set_iterables.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace set_iterables;

/**
 * @brief Demonstrates basic set iteration patterns
 */
void demonstrate_basic_iteration() {
    std::cout << "=== Basic Iteration Patterns ===" << std::endl;
    
    // Create a set with some numbers
    SetIterator<int> numbers{5, 2, 8, 1, 9, 3, 7};
    
    std::cout << "Original set: ";
    numbers.iterate_forward();
    
    // Different iteration methods
    numbers.iterate_reverse();
    numbers.iterate_with_iterators();
    
    // Print set information
    numbers.print_info();
    std::cout << std::endl;
}

/**
 * @brief Demonstrates conditional iteration and filtering
 */
void demonstrate_conditional_iteration() {
    std::cout << "=== Conditional Iteration ===" << std::endl;
    
    SetIterator<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Iterate over even numbers only
    numbers.iterate_conditional([](int x) { return x % 2 == 0; }, "Even numbers");
    
    // Iterate over numbers greater than 5
    numbers.iterate_conditional([](int x) { return x > 5; }, "Numbers > 5");
    
    // Apply a function during iteration (square each number)
    numbers.iterate_and_apply([](int x) { return x * x; }, "Squared values");
    
    // Filter to vector
    auto evens = numbers.filter_to_vector([](int x) { return x % 2 == 0; });
    utils::print_iterable(evens, "Even numbers (vector)");
    std::cout << std::endl;
}

/**
 * @brief Demonstrates range-based iteration
 */
void demonstrate_range_iteration() {
    std::cout << "=== Range-based Iteration ===" << std::endl;
    
    SetIterator<int> numbers{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    std::cout << "Full set: ";
    numbers.iterate_forward();
    
    // Iterate over ranges
    numbers.iterate_range(30, 70);  // [30, 70)
    numbers.iterate_range(50, 90);  // [50, 90)
    numbers.iterate_range(15, 45);  // [15, 45) - includes elements >= 15 and < 45
    std::cout << std::endl;
}

/**
 * @brief Demonstrates working with different data types
 */
void demonstrate_string_sets() {
    std::cout << "=== String Set Iteration ===" << std::endl;
    
    SetIterator<std::string> words{"apple", "banana", "cherry", "date", "elderberry"};
    
    std::cout << "All words: ";
    words.iterate_forward();
    
    // Words starting with specific letters
    words.iterate_conditional([](const std::string& s) { 
        return s[0] >= 'a' && s[0] <= 'c'; 
    }, "Words starting with a-c");
    
    // Transform during iteration (convert to uppercase first letter)
    words.iterate_and_apply([](const std::string& s) {
        std::string result = s;
        if (!result.empty()) result[0] = std::toupper(result[0]);
        return result;
    }, "Capitalized");
    
    std::cout << std::endl;
}

/**
 * @brief Demonstrates building sets from various iterables
 */
void demonstrate_iterable_conversion() {
    std::cout << "=== Iterable Conversion ===" << std::endl;
    
    // Create set from vector
    std::vector<int> vec{3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    SetIterator<int> from_vector(vec);
    
    std::cout << "Original vector: ";
    utils::print_iterable(vec, "Vector");
    std::cout << "Set from vector: ";
    from_vector.iterate_forward();
    
    // Add elements from another container
    std::vector<int> more_numbers{7, 8, 9, 10};
    from_vector.insert_from_iterable(more_numbers);
    
    std::cout << "After adding more numbers: ";
    from_vector.iterate_forward();
    
    // Convert back to vector (sorted and unique)
    auto sorted_unique = from_vector.copy_to_container<std::vector<int>>();
    utils::print_iterable(sorted_unique, "Back to vector (sorted, unique)");
    
    std::cout << std::endl;
}

int main() {
    std::cout << "C++ Set Iterables - Basic Examples" << std::endl;
    std::cout << "===================================" << std::endl << std::endl;
    
    demonstrate_basic_iteration();
    demonstrate_conditional_iteration();
    demonstrate_range_iteration();
    demonstrate_string_sets();
    demonstrate_iterable_conversion();
    
    return 0;
}