#pragma once

#include <set>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>

namespace set_iterables {

/**
 * @brief Utility class for demonstrating various std::set iteration patterns
 * and operations with different types of iterables.
 */
template<typename T>
class SetIterator {
private:
    std::set<T> data_;

public:
    // Constructor with initializer list
    SetIterator(std::initializer_list<T> init) : data_(init) {}
    
    // Constructor from container
    template<typename Container>
    SetIterator(const Container& container) 
        : data_(container.begin(), container.end()) {}
    
    // Default constructor
    SetIterator() = default;

    /**
     * @brief Insert an element into the set
     */
    void insert(const T& value) {
        data_.insert(value);
    }

    /**
     * @brief Insert multiple elements from an iterable container
     */
    template<typename Iterable>
    void insert_from_iterable(const Iterable& iterable) {
        for (const auto& item : iterable) {
            data_.insert(item);
        }
    }

    /**
     * @brief Basic forward iteration using range-based for loop
     */
    void iterate_forward() const {
        std::cout << "Forward iteration: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Reverse iteration using reverse iterators
     */
    void iterate_reverse() const {
        std::cout << "Reverse iteration: ";
        for (auto it = data_.rbegin(); it != data_.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Iterator-based iteration with explicit iterators
     */
    void iterate_with_iterators() const {
        std::cout << "Iterator-based: ";
        for (auto it = data_.begin(); it != data_.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Conditional iteration - process elements that match a predicate
     */
    template<typename Predicate>
    void iterate_conditional(Predicate pred, const std::string& description = "") const {
        if (!description.empty()) {
            std::cout << description << ": ";
        }
        for (const auto& item : data_) {
            if (pred(item)) {
                std::cout << item << " ";
            }
        }
        std::cout << std::endl;
    }

    /**
     * @brief Apply a function to each element during iteration
     */
    template<typename Function>
    void iterate_and_apply(Function func, const std::string& description = "") const {
        if (!description.empty()) {
            std::cout << description << ": ";
        }
        for (const auto& item : data_) {
            std::cout << func(item) << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Find and iterate over a range of elements
     */
    void iterate_range(const T& start, const T& end) const {
        std::cout << "Range [" << start << ", " << end << "): ";
        auto lower = data_.lower_bound(start);
        auto upper = data_.lower_bound(end);
        
        for (auto it = lower; it != upper; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Copy set elements to another container using iterators
     */
    template<typename OutputContainer>
    OutputContainer copy_to_container() const {
        OutputContainer result;
        std::copy(data_.begin(), data_.end(), 
                 std::inserter(result, result.end()));
        return result;
    }

    /**
     * @brief Get elements that satisfy a condition as a vector
     */
    template<typename Predicate>
    std::vector<T> filter_to_vector(Predicate pred) const {
        std::vector<T> result;
        std::copy_if(data_.begin(), data_.end(), 
                    std::back_inserter(result), pred);
        return result;
    }

    /**
     * @brief Demonstrate set operations with another set
     */
    void demonstrate_set_operations(const SetIterator<T>& other) const {
        std::set<T> union_result;
        std::set<T> intersection_result;
        std::set<T> difference_result;

        // Union
        std::set_union(data_.begin(), data_.end(),
                      other.data_.begin(), other.data_.end(),
                      std::inserter(union_result, union_result.begin()));

        // Intersection
        std::set_intersection(data_.begin(), data_.end(),
                             other.data_.begin(), other.data_.end(),
                             std::inserter(intersection_result, intersection_result.begin()));

        // Difference
        std::set_difference(data_.begin(), data_.end(),
                           other.data_.begin(), other.data_.end(),
                           std::inserter(difference_result, difference_result.begin()));

        std::cout << "Set operations results:" << std::endl;
        std::cout << "Union: ";
        for (const auto& item : union_result) std::cout << item << " ";
        std::cout << std::endl;

        std::cout << "Intersection: ";
        for (const auto& item : intersection_result) std::cout << item << " ";
        std::cout << std::endl;

        std::cout << "Difference: ";
        for (const auto& item : difference_result) std::cout << item << " ";
        std::cout << std::endl;
    }

    /**
     * @brief Print set information
     */
    void print_info() const {
        std::cout << "Set size: " << data_.size() << std::endl;
        std::cout << "Empty: " << (data_.empty() ? "Yes" : "No") << std::endl;
        if (!data_.empty()) {
            std::cout << "First element: " << *data_.begin() << std::endl;
            std::cout << "Last element: " << *data_.rbegin() << std::endl;
        }
    }

    // Accessor for the underlying set
    const std::set<T>& get_set() const { return data_; }
    
    // Size accessor
    size_t size() const { return data_.size(); }
    
    // Empty check
    bool empty() const { return data_.empty(); }
};

/**
 * @brief Utility functions for working with various iterable containers and sets
 */
namespace utils {

    /**
     * @brief Convert any iterable container to a set
     */
    template<typename T, typename Iterable>
    std::set<T> iterable_to_set(const Iterable& iterable) {
        return std::set<T>(iterable.begin(), iterable.end());
    }

    /**
     * @brief Print any iterable container
     */
    template<typename Iterable>
    void print_iterable(const Iterable& iterable, const std::string& name = "Iterable") {
        std::cout << name << ": ";
        for (const auto& item : iterable) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Create a set from multiple iterables
     */
    template<typename T, typename... Iterables>
    std::set<T> merge_iterables(const Iterables&... iterables) {
        std::set<T> result;
        auto insert_from = [&result](const auto& iterable) {
            for (const auto& item : iterable) {
                result.insert(item);
            }
        };
        
        (insert_from(iterables), ...); // C++17 fold expression
        return result;
    }

} // namespace utils

} // namespace set_iterables