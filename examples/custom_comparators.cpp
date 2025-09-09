/**
 * Custom Comparators and Iterable Elements in std::set
 * 
 * This file demonstrates how custom comparators affect iteration order
 * and how different comparison strategies work with iterable elements.
 */

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

// Custom struct for demonstration
struct Person {
    std::string name;
    int age;
    
    Person(const std::string& n, int a) : name(n), age(a) {}
};

// Comparator for Person objects - sort by age, then by name
struct PersonComparator {
    bool operator()(const Person& a, const Person& b) const {
        if (a.age != b.age) {
            return a.age < b.age;
        }
        return a.name < b.name;
    }
};

// Function object for case-insensitive string comparison
struct CaseInsensitiveCompare {
    bool operator()(const std::string& a, const std::string& b) const {
        return std::lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end(),
            [](char c1, char c2) {
                return std::tolower(c1) < std::tolower(c2);
            }
        );
    }
};

void demonstrateDefaultComparator() {
    std::cout << "=== Default Comparator (std::less) ===" << std::endl;
    
    std::set<int> numbers = {50, 20, 80, 10, 60, 30};
    
    std::cout << "Default ordering (ascending): ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

void demonstrateCustomComparator() {
    std::cout << "\n=== Custom Comparator (std::greater) ===" << std::endl;
    
    // Using std::greater for descending order
    std::set<int, std::greater<int>> descendingNumbers = {50, 20, 80, 10, 60, 30};
    
    std::cout << "Descending order: ";
    for (int n : descendingNumbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // Iteration is still the same - just the order changes
    std::cout << "Reverse iteration (ascending again): ";
    for (auto it = descendingNumbers.rbegin(); it != descendingNumbers.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void demonstrateCaseInsensitiveStrings() {
    std::cout << "\n=== Case-Insensitive String Comparison ===" << std::endl;
    
    // Regular set (case-sensitive)
    std::set<std::string> caseSensitive = {"Apple", "banana", "Cherry", "apple"};
    
    std::cout << "Case-sensitive set: ";
    for (const auto& item : caseSensitive) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // Case-insensitive set
    std::set<std::string, CaseInsensitiveCompare> caseInsensitive;
    caseInsensitive.insert("Apple");
    caseInsensitive.insert("banana");
    caseInsensitive.insert("Cherry");
    caseInsensitive.insert("apple");  // Will be treated as duplicate
    
    std::cout << "Case-insensitive set: ";
    for (const auto& item : caseInsensitive) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void demonstrateCustomObjectComparator() {
    std::cout << "\n=== Custom Objects with Comparator ===" << std::endl;
    
    std::set<Person, PersonComparator> people;
    
    people.insert(Person("Alice", 30));
    people.insert(Person("Bob", 25));
    people.insert(Person("Charlie", 30));
    people.insert(Person("David", 20));
    people.insert(Person("Eve", 25));
    
    std::cout << "People sorted by age, then name:" << std::endl;
    for (const auto& person : people) {
        std::cout << "  " << person.name << " (age " << person.age << ")" << std::endl;
    }
    
    // Finding a specific person
    Person searchPerson("Charlie", 30);
    auto found = people.find(searchPerson);
    if (found != people.end()) {
        std::cout << "Found: " << found->name << " (age " << found->age << ")" << std::endl;
    }
}

void demonstrateLambdaComparator() {
    std::cout << "\n=== Lambda Comparator ===" << std::endl;
    
    // Using lambda for comparison (C++11)
    auto lengthComparator = [](const std::string& a, const std::string& b) {
        if (a.length() != b.length()) {
            return a.length() < b.length();
        }
        return a < b; // If same length, use lexicographic order
    };
    
    std::set<std::string, decltype(lengthComparator)> lengthSortedWords(lengthComparator);
    
    lengthSortedWords.insert("cat");
    lengthSortedWords.insert("elephant");
    lengthSortedWords.insert("dog");
    lengthSortedWords.insert("butterfly");
    lengthSortedWords.insert("ant");
    lengthSortedWords.insert("horse");
    
    std::cout << "Words sorted by length, then alphabetically:" << std::endl;
    for (const auto& word : lengthSortedWords) {
        std::cout << "  " << word << " (length: " << word.length() << ")" << std::endl;
    }
}

void demonstrateIterationWithCustomComparator() {
    std::cout << "\n=== Iteration Patterns with Custom Comparators ===" << std::endl;
    
    // Create a set that sorts strings by their last character
    auto lastCharComparator = [](const std::string& a, const std::string& b) {
        if (a.back() != b.back()) {
            return a.back() < b.back();
        }
        return a < b; // Same last char, use normal comparison
    };
    
    std::set<std::string, decltype(lastCharComparator)> lastCharSet(lastCharComparator);
    
    lastCharSet.insert("hello");
    lastCharSet.insert("world");
    lastCharSet.insert("test");
    lastCharSet.insert("code");
    lastCharSet.insert("example");
    
    std::cout << "Words sorted by last character:" << std::endl;
    for (const auto& word : lastCharSet) {
        std::cout << "  " << word << " (ends with '" << word.back() << "')" << std::endl;
    }
    
    // All iteration methods still work the same way
    std::cout << "\nReverse iteration:" << std::endl;
    for (auto it = lastCharSet.rbegin(); it != lastCharSet.rend(); ++it) {
        std::cout << "  " << *it << std::endl;
    }
}

void demonstrateIteratorConsistency() {
    std::cout << "\n=== Iterator Consistency Across Different Comparators ===" << std::endl;
    
    // Same data, different comparators
    std::vector<int> data = {5, 2, 8, 1, 9, 3};
    
    std::set<int> ascendingSet(data.begin(), data.end());
    std::set<int, std::greater<int>> descendingSet(data.begin(), data.end());
    
    std::cout << "Ascending set iteration: ";
    for (auto it = ascendingSet.begin(); it != ascendingSet.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Descending set iteration: ";
    for (auto it = descendingSet.begin(); it != descendingSet.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Both sets have the same iterator interface and behavior
    // Only the ordering is different
    std::cout << "Both sets support the same iteration operations!" << std::endl;
}

int main() {
    demonstrateDefaultComparator();
    demonstrateCustomComparator();
    demonstrateCaseInsensitiveStrings();
    demonstrateCustomObjectComparator();
    demonstrateLambdaComparator();
    demonstrateIterationWithCustomComparator();
    demonstrateIteratorConsistency();
    
    return 0;
}