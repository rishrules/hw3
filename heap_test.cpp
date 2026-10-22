#include <cstdlib>
#include <cstddef>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "heap.h"

void require(bool condition, const char* message)
{
    if (!condition) {
        std::cerr << "FAIL: " << message << std::endl;
        std::exit(1);
    }
}

template <typename T, typename Comparator>
void checkOrder(Heap<T, Comparator>& heap,
                const std::vector<T>& expected,
                const char* message)
{
    require(heap.size() == expected.size(), "heap size after insertion");
    for (std::size_t i = 0; i < expected.size(); ++i) {
        require(!heap.empty(), "heap unexpectedly became empty");
        require(heap.top() == expected[i], message);
        heap.pop();
    }
    require(heap.empty(), "heap should be empty after removing all items");
}

int main()
{
    const std::vector<int> values = {8, 3, 10, 1, 6, 2, 9, 4, 7, 5};

    Heap<int> min_heap;
    for (int value : values) {
        min_heap.push(value);
    }
    checkOrder(min_heap, std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
               "binary min-heap should pop in ascending order");

    Heap<int, std::greater<int> > max_heap(3, std::greater<int>());
    for (int value : values) {
        max_heap.push(value);
    }
    checkOrder(max_heap, std::vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
               "ternary max-heap should pop in descending order");

    Heap<std::string> string_heap;
    string_heap.push("pear");
    string_heap.push("apple");
    string_heap.push("orange");
    checkOrder(string_heap,
               std::vector<std::string>{"apple", "orange", "pear"},
               "string min-heap should pop in lexicographic order");

    Heap<int> empty_heap;
    bool top_threw = false;
    try {
        empty_heap.top();
    }
    catch (const std::underflow_error&) {
        top_threw = true;
    }
    require(top_threw, "top on an empty heap should throw");

    bool pop_threw = false;
    try {
        empty_heap.pop();
    }
    catch (const std::underflow_error&) {
        pop_threw = true;
    }
    require(pop_threw, "pop on an empty heap should throw");

    bool invalid_arity_threw = false;
    try {
        Heap<int> invalid_heap(1);
    }
    catch (const std::invalid_argument&) {
        invalid_arity_threw = true;
    }
    require(invalid_arity_threw, "arity less than two should throw");

    std::cout << "All heap tests passed." << std::endl;
    return 0;
}