#include "set_iterables.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <chrono>

using namespace set_iterables;

// Book struct for custom type demonstration
struct Book {
    std::string title;
    int year;
    
    Book(const std::string& t, int y) : title(t), year(y) {}
    
    bool operator<(const Book& other) const {
        if (year != other.year) return year < other.year;
        return title < other.title;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Book& b) {
        return os << b.title << "(" << b.year << ")";
    }
};

/**
 * @brief Interactive demonstration of set iterables functionality
 */
class SetIterablesDemo {
public:
    void run() {
        std::cout << "======================================" << std::endl;
        std::cout << "    C++ Set Iterables Demonstration   " << std::endl;
        std::cout << "======================================" << std::endl << std::endl;
        
        show_menu();
        
        char choice;
        do {
            std::cout << "\nEnter your choice (1-9, q to quit): ";
            std::cin >> choice;
            
            switch (choice) {
                case '1': demo_basic_operations(); break;
                case '2': demo_iteration_patterns(); break;
                case '3': demo_filtering_transformation(); break;
                case '4': demo_set_operations(); break;
                case '5': demo_range_queries(); break;
                case '6': demo_custom_types(); break;
                case '7': demo_container_conversion(); break;
                case '8': demo_performance(); break;
                case '9': run_all_demos(); break;
                case 'q':
                case 'Q': 
                    std::cout << "Goodbye!" << std::endl; 
                    return;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
            
            std::cout << "\n" << std::string(50, '-') << std::endl;
            
        } while (true);
    }

private:
    void show_menu() {
        std::cout << "Choose a demonstration:" << std::endl;
        std::cout << "1. Basic Set Operations" << std::endl;
        std::cout << "2. Iteration Patterns" << std::endl;
        std::cout << "3. Filtering and Transformation" << std::endl;
        std::cout << "4. Set Operations (Union, Intersection, etc.)" << std::endl;
        std::cout << "5. Range Queries" << std::endl;
        std::cout << "6. Custom Data Types" << std::endl;
        std::cout << "7. Container Conversion" << std::endl;
        std::cout << "8. Performance Examples" << std::endl;
        std::cout << "9. Run All Demonstrations" << std::endl;
        std::cout << "q. Quit" << std::endl;
    }

    void demo_basic_operations() {
        std::cout << "\n=== Basic Set Operations ===" << std::endl;
        
        SetIterator<int> numbers;
        
        // Insert some numbers
        std::vector<int> data{5, 2, 8, 1, 9, 3, 7, 2, 5}; // duplicates will be removed
        numbers.insert_from_iterable(data);
        
        std::cout << "Inserted numbers: ";
        for (int n : data) std::cout << n << " ";
        std::cout << std::endl;
        
        std::cout << "Set contents (sorted, unique): ";
        numbers.iterate_forward();
        
        numbers.print_info();
    }

    void demo_iteration_patterns() {
        std::cout << "\n=== Iteration Patterns ===" << std::endl;
        
        SetIterator<std::string> fruits{"apple", "banana", "cherry", "date", "elderberry", "fig"};
        
        std::cout << "Different ways to iterate:" << std::endl;
        fruits.iterate_forward();
        fruits.iterate_reverse();
        fruits.iterate_with_iterators();
    }

    void demo_filtering_transformation() {
        std::cout << "\n=== Filtering and Transformation ===" << std::endl;
        
        SetIterator<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        
        // Various filtering examples
        numbers.iterate_conditional([](int x) { return x % 2 == 0; }, "Even numbers");
        numbers.iterate_conditional([](int x) { return x > 10; }, "Numbers > 10");
        numbers.iterate_conditional([](int x) { return x % 3 == 0; }, "Divisible by 3");
        
        // Transformation examples
        numbers.iterate_and_apply([](int x) { return x * x; }, "Squared");
        numbers.iterate_and_apply([](int x) { return x * 10; }, "Multiplied by 10");
    }

    void demo_set_operations() {
        std::cout << "\n=== Set Operations ===" << std::endl;
        
        SetIterator<int> evens{2, 4, 6, 8, 10, 12};
        SetIterator<int> primes{2, 3, 5, 7, 11, 13};
        
        std::cout << "Set A (evens): ";
        evens.iterate_forward();
        
        std::cout << "Set B (primes): ";
        primes.iterate_forward();
        
        evens.demonstrate_set_operations(primes);
    }

    void demo_range_queries() {
        std::cout << "\n=== Range Queries ===" << std::endl;
        
        SetIterator<int> numbers{10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70};
        
        std::cout << "Full set: ";
        numbers.iterate_forward();
        
        numbers.iterate_range(20, 50);
        numbers.iterate_range(35, 65);
        numbers.iterate_range(0, 30);
    }

    void demo_custom_types() {
        std::cout << "\n=== Custom Data Types ===" << std::endl;
        
        SetIterator<Book> library{
            Book("The Hobbit", 1937),
            Book("1984", 1949),
            Book("Dune", 1965),
            Book("Neuromancer", 1984),
            Book("Foundation", 1951)
        };
        
        std::cout << "Library (sorted by year, then title): ";
        library.iterate_forward();
        
        library.iterate_conditional([](const Book& b) { return b.year >= 1950; }, 
                                   "Books from 1950 onwards");
    }

    void demo_container_conversion() {
        std::cout << "\n=== Container Conversion ===" << std::endl;
        
        // Start with a vector containing duplicates
        std::vector<int> input{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
        std::cout << "Original vector: ";
        utils::print_iterable(input, "Vector");
        
        // Convert to set (removes duplicates, sorts)
        SetIterator<int> unique_sorted(input);
        std::cout << "As set: ";
        unique_sorted.iterate_forward();
        
        // Convert back to vector
        auto back_to_vector = unique_sorted.copy_to_container<std::vector<int>>();
        utils::print_iterable(back_to_vector, "Back to vector");
        
        // Merge multiple containers
        std::vector<int> more_numbers{7, 8, 9};
        std::list<int> even_more{10, 11, 12};
        
        auto merged = utils::merge_iterables<int>(input, more_numbers, even_more);
        utils::print_iterable(merged, "Merged from multiple containers");
    }

    void demo_performance() {
        std::cout << "\n=== Performance Examples ===" << std::endl;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Create a large set
        SetIterator<int> large_set;
        for (int i = 1; i <= 10000; ++i) {
            if (i % 7 == 0 || i % 11 == 0) {
                large_set.insert(i);
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Created large set with " << large_set.size() << " elements in " 
                  << duration.count() << " microseconds" << std::endl;
        
        // Efficient range queries
        std::cout << "Elements in range [1000, 2000): ";
        large_set.iterate_range(1000, 2000);
        
        // Efficient filtering
        start = std::chrono::high_resolution_clock::now();
        auto filtered = large_set.filter_to_vector([](int x) { return x % 77 == 0; });
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        utils::print_iterable(filtered, "Multiples of 77");
        std::cout << "Filtering completed in " << duration.count() << " microseconds" << std::endl;
    }

    void run_all_demos() {
        std::cout << "\n=== Running All Demonstrations ===" << std::endl;
        demo_basic_operations();
        demo_iteration_patterns();
        demo_filtering_transformation();
        demo_set_operations();
        demo_range_queries();
        demo_custom_types();
        demo_container_conversion();
        demo_performance();
        std::cout << "\n=== All Demonstrations Complete ===" << std::endl;
    }
};

int main() {
    SetIterablesDemo demo;
    demo.run();
    return 0;
}