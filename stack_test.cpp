#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "stack.h"

void require(bool condition, const char* message)
{
    if (!condition) {
        std::cerr << "FAIL: " << message << std::endl;
        std::exit(1);
    }
}

int main()
{
    Stack<int> values;
    require(values.empty(), "new stack should be empty");
    require(values.size() == 0, "new stack should have size zero");

    values.push(3);
    values.push(7);
    require(!values.empty(), "stack should not be empty after push");
    require(values.size() == 2, "size should reflect pushed values");
    require(values.top() == 7, "top should be the most recently pushed value");

    values.pop();
    require(values.top() == 3, "pop should reveal the previous top");
    values.pop();
    require(values.empty(), "stack should be empty after removing all values");

    bool threw = false;
    try {
        values.pop();
    }
    catch (const std::underflow_error&) {
        threw = true;
    }
    require(threw, "pop on an empty stack should throw underflow_error");

    threw = false;
    try {
        values.top();
    }
    catch (const std::underflow_error&) {
        threw = true;
    }
    require(threw, "top on an empty stack should throw underflow_error");

    std::cout << "All stack tests passed." << std::endl;
    return 0;
}