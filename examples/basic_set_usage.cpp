/**
 * Basic std::set Usage and Iteration Examples
 * 
 * This file demonstrates fundamental std::set operations and various
 * iteration patterns to showcase how elements are iterable.
 */

#include <iostream>
#include <set>
#include <string>
#include <vector>

void demonstrateBasicOperations() {
    std::cout << "=== Basic std::set Operations ===" << std::endl;
    
    // Creating and initializing a set
    std::set<int> numbers;
    
    // Inserting elements (duplicates will be ignored)
    numbers.insert(5);
    numbers.insert(2);
    numbers.insert(8);
    numbers.insert(1);
    numbers.insert(5); // Duplicate - will be ignored
    numbers.insert(3);
    
    std::cout << "Set size: " << numbers.size() << std::endl;
    std::cout << "Elements are automatically sorted!" << std::endl;
}

void demonstrateIterationMethods() {
    std::cout << "\n=== Different Iteration Methods ===" << std::endl;
    
    std::set<std::string> fruits = {"apple", "banana", "cherry", "date"};
    
    // Method 1: Range-based for loop (C++11+)
    std::cout << "Range-based for loop: ";
    for (const auto& fruit : fruits) {
        std::cout << fruit << " ";
    }
    std::cout << std::endl;
    
    // Method 2: Traditional iterator
    std::cout << "Traditional iterator: ";
    for (auto it = fruits.begin(); it != fruits.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Method 3: Const iterator (explicit)
    std::cout << "Const iterator: ";
    for (std::set<std::string>::const_iterator it = fruits.cbegin(); 
         it != fruits.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Method 4: Reverse iteration
    std::cout << "Reverse iteration: ";
    for (auto it = fruits.rbegin(); it != fruits.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void demonstrateSearchAndRanges() {
    std::cout << "\n=== Search and Range Operations ===" << std::endl;
    
    std::set<int> numbers = {10, 20, 30, 40, 50, 60, 70};
    
    // Finding a specific element
    auto it = numbers.find(30);
    if (it != numbers.end()) {
        std::cout << "Found element: " << *it << std::endl;
        
        // Iterate from found element to end
        std::cout << "Elements from 30 onwards: ";
        for (; it != numbers.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    // Using lower_bound and upper_bound
    auto lower = numbers.lower_bound(25); // First element >= 25
    auto upper = numbers.upper_bound(55); // First element > 55
    
    std::cout << "Elements in range [25, 55]: ";
    for (auto iter = lower; iter != upper; ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

void demonstrateSetWithCustomObjects() {
    std::cout << "\n=== Set with Custom Objects ===" << std::endl;
    
    // Using set with strings (naturally comparable)
    std::set<std::string> cities = {"New York", "London", "Tokyo", "Paris"};
    
    std::cout << "Cities in alphabetical order: ";
    for (const auto& city : cities) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    
    // Checking membership
    std::string searchCity = "Paris";
    if (cities.find(searchCity) != cities.end()) {
        std::cout << searchCity << " is in the set!" << std::endl;
    }
}

int main() {
    demonstrateBasicOperations();
    demonstrateIterationMethods();
    demonstrateSearchAndRanges();
    demonstrateSetWithCustomObjects();
    
    return 0;
}