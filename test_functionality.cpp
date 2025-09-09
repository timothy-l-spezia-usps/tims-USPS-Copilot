#include "set_iterables.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

using namespace set_iterables;

/**
 * @brief Simple test suite to verify key functionality
 */
class FunctionalityTester {
public:
    void run_all_tests() {
        std::cout << "Running Set Iterables Functionality Tests..." << std::endl;
        
        test_basic_operations();
        test_iteration_patterns();
        test_filtering();
        test_range_queries();
        test_container_conversion();
        test_set_operations();
        test_utilities();
        
        std::cout << "All tests passed! ✓" << std::endl;
    }

private:
    void test_basic_operations() {
        std::cout << "Testing basic operations... ";
        
        SetIterator<int> set{3, 1, 4, 1, 5, 9};
        
        // Test size and uniqueness
        assert(set.size() == 5); // duplicates removed
        assert(!set.empty());
        
        // Test insertion
        set.insert(7);
        assert(set.size() == 6);
        
        std::cout << "✓" << std::endl;
    }

    void test_iteration_patterns() {
        std::cout << "Testing iteration patterns... ";
        
        SetIterator<int> set{1, 2, 3, 4, 5};
        
        // Test that we can call all iteration methods without errors
        std::ostringstream oss;
        std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
        
        set.iterate_forward();
        set.iterate_reverse();
        set.iterate_with_iterators();
        
        std::cout.rdbuf(old_cout);
        
        // Should have some output
        assert(!oss.str().empty());
        
        std::cout << "✓" << std::endl;
    }

    void test_filtering() {
        std::cout << "Testing filtering functionality... ";
        
        SetIterator<int> set{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // Test filtering to vector
        auto evens = set.filter_to_vector([](int x) { return x % 2 == 0; });
        assert(evens.size() == 5);
        assert(evens[0] == 2);
        assert(evens[4] == 10);
        
        std::cout << "✓" << std::endl;
    }

    void test_range_queries() {
        std::cout << "Testing range queries... ";
        
        SetIterator<int> set{10, 20, 30, 40, 50, 60, 70};
        
        // Test that range iteration works (just check it doesn't crash)
        std::ostringstream oss;
        std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
        
        set.iterate_range(20, 60);
        
        std::cout.rdbuf(old_cout);
        
        // Should have some output for the range
        assert(!oss.str().empty());
        
        std::cout << "✓" << std::endl;
    }

    void test_container_conversion() {
        std::cout << "Testing container conversion... ";
        
        // Test vector to set
        std::vector<int> vec{3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        SetIterator<int> from_vec(vec);
        assert(from_vec.size() == 7); // unique elements
        
        // Test set to vector
        auto back_to_vec = from_vec.copy_to_container<std::vector<int>>();
        assert(back_to_vec.size() == 7);
        assert(std::is_sorted(back_to_vec.begin(), back_to_vec.end()));
        
        std::cout << "✓" << std::endl;
    }

    void test_set_operations() {
        std::cout << "Testing set operations... ";
        
        SetIterator<int> set1{1, 2, 3, 4};
        SetIterator<int> set2{3, 4, 5, 6};
        
        // Test that set operations don't crash
        std::ostringstream oss;
        std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
        
        set1.demonstrate_set_operations(set2);
        
        std::cout.rdbuf(old_cout);
        
        // Should have output for union, intersection, difference
        std::string output = oss.str();
        assert(output.find("Union") != std::string::npos);
        assert(output.find("Intersection") != std::string::npos);
        assert(output.find("Difference") != std::string::npos);
        
        std::cout << "✓" << std::endl;
    }

    void test_utilities() {
        std::cout << "Testing utility functions... ";
        
        // Test iterable_to_set
        std::vector<int> vec{3, 1, 4, 1, 5};
        auto set_from_vec = utils::iterable_to_set<int>(vec);
        assert(set_from_vec.size() == 4); // unique elements
        
        // Test merge_iterables
        std::vector<int> vec1{1, 2, 3};
        std::vector<int> vec2{3, 4, 5};
        auto merged = utils::merge_iterables<int>(vec1, vec2);
        assert(merged.size() == 5); // {1, 2, 3, 4, 5}
        
        std::cout << "✓" << std::endl;
    }
};

int main() {
    FunctionalityTester tester;
    tester.run_all_tests();
    return 0;
}