/**
 * Advanced Iteration Patterns with std::set
 * 
 * This file demonstrates advanced iteration techniques, algorithm usage,
 * and complex iteration scenarios with std::set.
 */

#include <iostream>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>

void demonstrateSTLAlgorithms() {
    std::cout << "=== STL Algorithms with std::set ===" << std::endl;
    
    std::set<int> numbers = {1, 3, 5, 7, 9, 11, 13, 15};
    
    // std::for_each
    std::cout << "Using std::for_each: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n * 2 << " ";
    });
    std::cout << std::endl;
    
    // std::count_if
    int evenCount = std::count_if(numbers.begin(), numbers.end(), 
                                  [](int n) { return n % 2 == 0; });
    std::cout << "Even numbers count: " << evenCount << std::endl;
    
    // std::find_if
    auto found = std::find_if(numbers.begin(), numbers.end(), 
                              [](int n) { return n > 10; });
    if (found != numbers.end()) {
        std::cout << "First number > 10: " << *found << std::endl;
    }
    
    // std::accumulate
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Sum of all numbers: " << sum << std::endl;
}

void demonstrateConditionalIteration() {
    std::cout << "\n=== Conditional Iteration ===" << std::endl;
    
    std::set<std::string> words = {"apple", "application", "apply", "banana", 
                                   "band", "bandana", "cherry", "chair"};
    
    // Find and iterate through words starting with 'a'
    std::cout << "Words starting with 'a': ";
    auto lower = words.lower_bound("a");
    auto upper = words.lower_bound("b"); // First element >= "b"
    
    for (auto it = lower; it != upper; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Custom predicate iteration
    std::cout << "Words with length > 5: ";
    for (const auto& word : words) {
        if (word.length() > 5) {
            std::cout << word << " ";
        }
    }
    std::cout << std::endl;
}

void demonstrateSafeEraseDuringIteration() {
    std::cout << "\n=== Safe Erase During Iteration ===" << std::endl;
    
    std::set<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Original set: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // Safe way to erase elements during iteration
    std::cout << "Removing even numbers..." << std::endl;
    for (auto it = numbers.begin(); it != numbers.end();) {
        if (*it % 2 == 0) {
            it = numbers.erase(it); // erase returns iterator to next element
        } else {
            ++it;
        }
    }
    
    std::cout << "After removing evens: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

void demonstrateIteratorArithmetic() {
    std::cout << "\n=== Iterator Properties and Limitations ===" << std::endl;
    
    std::set<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    
    auto it = letters.begin();
    
    // Bidirectional iterator - can go forward and backward
    std::cout << "Starting at: " << *it << std::endl;
    
    ++it; // Move forward
    ++it;
    std::cout << "After moving forward twice: " << *it << std::endl;
    
    --it; // Move backward
    std::cout << "After moving backward once: " << *it << std::endl;
    
    // Note: std::set iterators are NOT random access
    // This would NOT work: it += 3; // Compilation error
    
    // To advance by multiple positions, use std::advance
    std::advance(it, 3);
    std::cout << "After advancing by 3: " << *it << std::endl;
    
    // To get distance between iterators
    auto distance = std::distance(letters.begin(), it);
    std::cout << "Distance from begin: " << distance << std::endl;
}

void demonstrateIteratorInvalidation() {
    std::cout << "\n=== Iterator Invalidation Rules ===" << std::endl;
    
    std::set<int> numbers = {10, 20, 30, 40, 50};
    
    auto it1 = numbers.find(30);
    auto it2 = numbers.find(40);
    
    std::cout << "Before erase - it1 points to: " << *it1 << std::endl;
    std::cout << "Before erase - it2 points to: " << *it2 << std::endl;
    
    // Erase element that it1 points to
    numbers.erase(it1);
    // it1 is now invalidated and should not be used
    
    // it2 is still valid (only erased element's iterator is invalidated)
    std::cout << "After erase - it2 still points to: " << *it2 << std::endl;
    
    // Insert operation doesn't invalidate existing iterators
    numbers.insert(35);
    std::cout << "After insert - it2 still points to: " << *it2 << std::endl;
    
    std::cout << "Final set: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

void demonstrateBidirectionalIteratorFeatures() {
    std::cout << "\n=== Bidirectional Iterator Features ===" << std::endl;
    
    std::set<double> values = {1.1, 2.2, 3.3, 4.4, 5.5};
    
    // Forward iteration
    std::cout << "Forward: ";
    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Backward iteration using rbegin/rend
    std::cout << "Backward (using reverse iterators): ";
    for (auto it = values.rbegin(); it != values.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Backward iteration using regular iterators
    std::cout << "Backward (using regular iterators): ";
    if (!values.empty()) {
        auto it = values.end();
        --it; // Move to last element
        while (true) {
            std::cout << *it << " ";
            if (it == values.begin()) break;
            --it;
        }
    }
    std::cout << std::endl;
}

int main() {
    demonstrateSTLAlgorithms();
    demonstrateConditionalIteration();
    demonstrateSafeEraseDuringIteration();
    demonstrateIteratorArithmetic();
    demonstrateIteratorInvalidation();
    demonstrateBidirectionalIteratorFeatures();
    
    return 0;
}