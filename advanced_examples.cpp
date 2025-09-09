#include "set_iterables.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <random>

using namespace set_iterables;

/**
 * @brief Demonstrates set operations between different sets
 */
void demonstrate_set_operations() {
    std::cout << "=== Set Operations ===" << std::endl;
    
    SetIterator<int> set1{1, 2, 3, 4, 5, 6};
    SetIterator<int> set2{4, 5, 6, 7, 8, 9};
    
    std::cout << "Set 1: ";
    set1.iterate_forward();
    std::cout << "Set 2: ";
    set2.iterate_forward();
    
    std::cout << std::endl;
    set1.demonstrate_set_operations(set2);
    std::cout << std::endl;
}

/**
 * @brief Demonstrates merging multiple iterables into a set
 */
void demonstrate_merging_iterables() {
    std::cout << "=== Merging Multiple Iterables ===" << std::endl;
    
    std::vector<int> vec{1, 2, 3, 4};
    std::list<int> lst{3, 4, 5, 6};
    std::set<int> original_set{5, 6, 7, 8};
    
    utils::print_iterable(vec, "Vector");
    utils::print_iterable(lst, "List");
    utils::print_iterable(original_set, "Original Set");
    
    // Merge all iterables into one set
    auto merged = utils::merge_iterables<int>(vec, lst, original_set);
    utils::print_iterable(merged, "Merged Set");
    std::cout << std::endl;
}

/**
 * @brief Demonstrates complex filtering and transformation
 */
void demonstrate_complex_operations() {
    std::cout << "=== Complex Operations ===" << std::endl;
    
    // Generate a set of random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    SetIterator<int> random_numbers;
    for (int i = 0; i < 20; ++i) {
        random_numbers.insert(dis(gen));
    }
    
    std::cout << "Random numbers: ";
    random_numbers.iterate_forward();
    
    // Multiple filtering operations
    auto primes_check = [](int n) -> bool {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    };
    
    random_numbers.iterate_conditional(primes_check, "Prime numbers");
    random_numbers.iterate_conditional([](int x) { return x >= 50; }, "Numbers >= 50");
    
    // Transform and display
    random_numbers.iterate_and_apply([](int x) { return x * 2; }, "Doubled values");
    
    // Complex range operations
    random_numbers.iterate_range(10, 50);
    random_numbers.iterate_range(25, 75);
    
    std::cout << std::endl;
}

/**
 * @brief Demonstrates working with custom objects
 */
struct Person {
    std::string name;
    int age;
    
    Person(const std::string& n, int a) : name(n), age(a) {}
    
    // Required for std::set
    bool operator<(const Person& other) const {
        if (name != other.name) return name < other.name;
        return age < other.age;
    }
    
    // For printing
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << p.name << "(" << p.age << ")";
    }
};

void demonstrate_custom_objects() {
    std::cout << "=== Custom Objects ===" << std::endl;
    
    SetIterator<Person> people{
        Person("Alice", 25),
        Person("Bob", 30),
        Person("Charlie", 22),
        Person("David", 35),
        Person("Eve", 28)
    };
    
    std::cout << "All people: ";
    people.iterate_forward();
    
    // Filter by age
    people.iterate_conditional([](const Person& p) { return p.age >= 25; }, 
                              "People 25 or older");
    
    // Transform names to uppercase
    people.iterate_and_apply([](const Person& p) { 
        std::string upper_name = p.name;
        std::transform(upper_name.begin(), upper_name.end(), upper_name.begin(), ::toupper);
        return upper_name + "(" + std::to_string(p.age) + ")";
    }, "Uppercase names");
    
    std::cout << std::endl;
}

/**
 * @brief Demonstrates performance-oriented iteration patterns
 */
void demonstrate_performance_patterns() {
    std::cout << "=== Performance Patterns ===" << std::endl;
    
    // Large set for performance demonstration
    SetIterator<int> large_set;
    for (int i = 1; i <= 1000; ++i) {
        if (i % 3 == 0 || i % 7 == 0) {  // Numbers divisible by 3 or 7
            large_set.insert(i);
        }
    }
    
    std::cout << "Large set size: " << large_set.size() << std::endl;
    
    // Efficient range queries
    std::cout << "Numbers in range [100, 200): ";
    large_set.iterate_range(100, 200);
    
    // Efficient filtering
    auto multiples_of_21 = large_set.filter_to_vector([](int x) { return x % 21 == 0; });
    utils::print_iterable(multiples_of_21, "Multiples of 21");
    
    // Show first and last few elements efficiently
    const auto& set_ref = large_set.get_set();
    std::cout << "First 5 elements: ";
    auto it = set_ref.begin();
    for (int i = 0; i < 5 && it != set_ref.end(); ++i, ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Last 5 elements: ";
    auto rit = set_ref.rbegin();
    for (int i = 0; i < 5 && rit != set_ref.rend(); ++i, ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;
    
    std::cout << std::endl;
}

int main() {
    std::cout << "C++ Set Iterables - Advanced Examples" << std::endl;
    std::cout << "======================================" << std::endl << std::endl;
    
    demonstrate_set_operations();
    demonstrate_merging_iterables();
    demonstrate_complex_operations();
    demonstrate_custom_objects();
    demonstrate_performance_patterns();
    
    return 0;
}