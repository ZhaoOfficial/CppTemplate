#include <iostream>
#include <list>

#include "book/chapter2.hpp"
#include "spdlog/spdlog.h"

int main() {

    spdlog::info("Test class template.");
    {
        Coding::Stack<std::pair<uint64_t, double>> pair_stack;
        pair_stack.push({1ul, 1.5});
        pair_stack.push({2ul, 2.5});
        std::cout << pair_stack.top().first << std::endl;
        std::cout << pair_stack.top().second << std::endl;
        // std::cout << pair_stack.top() << std::endl; //! compile error
        pair_stack.pop();
        pair_stack.pop();
        std::cout << pair_stack.empty() << std::endl;
    }
    spdlog::info("Test full specialization.");
    {
        Coding::Stack<std::string> string_stack;
        string_stack.push("Hello");
        string_stack.push("World");
        std::cout << string_stack.top() << std::endl;
        string_stack.pop();
        string_stack.pop();
        std::cout << string_stack.empty() << std::endl;
    }
    spdlog::info("Test partial specialization.");
    {
        Coding::MyClass<int, float> mif;
        Coding::MyClass<float, float> mff;
        Coding::MyClass<float, int> mfi;
        Coding::MyClass<int*, float*> mpp;
        // Coding::MyClass<int, int> mii; //! compile error
        // Coding::MyClass<int*, int*> mpi; //! compile error
    }
    spdlog::info("Test default class template argument.");
    {
        Coding::Queue<int> int_queue;
        int_queue.push(1);
        std::cout << int_queue.front() << std::endl;
        int_queue.pop();

        Coding::Queue<double, std::list<double>> double_queue;
        double_queue.push(1.1);
        std::cout << double_queue.front() << std::endl;
        double_queue.pop();
    }
    spdlog::info("Test deduction guide.");
    {
        Coding::Stack string_stack {(const char*)"Deduction Guide."};
        std::cout << string_stack.top() << std::endl;
        string_stack.push("Hello");
        string_stack.push("World");
        std::cout << string_stack.top() << std::endl;
        string_stack.pop();
        string_stack.pop();
        string_stack.pop();
        std::cout << string_stack.empty() << std::endl;
    }

    return 0;
}
