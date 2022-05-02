#include <algorithm>
#include <iostream>
#include <random>

#include "book/chapter3.hpp"
#include "spdlog/spdlog.h"

// test restriction for nontype template parameters
extern char const s03[] = "Since C++03";
char const s11[] = "Since C++11";

int main() {

    spdlog::info("Test nontype class template parameters.");
    {
        Coding::Stack<int, 20> int20stack;
        Coding::Stack<int, 40> int40stack;
        Coding::Stack<std::string, 40> string40stack;

        int20stack.push(20);
        std::cout << int20stack.top() << std::endl;
        int20stack.pop();

        string40stack.push("string40stack");
        std::cout << string40stack.top() << std::endl;
        string40stack.pop();
    }
    spdlog::info("Test nontype function template parameters.");
    {
        std::random_device rd;
        std::mt19937_64 rng{rd()};
        std::uniform_int_distribution<int> unif{1, 6};
        std::array<int, 10> arr;
        auto dice = [&unif, &rng](){ return unif(rng); };

        std::generate(arr.begin(), arr.end(), dice);
        for (std::cout << "Original array: "; auto&& i : arr) {
            std::cout << i << ' ';
        }
        std::cout << '\n';

        std::transform(arr.begin(), arr.end(), arr.begin(), Coding::addValue<3, int>);
        for (std::cout << "Modified array: "; auto&& i : arr) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
    spdlog::info("Test restriction for nontype template parameters.");
    {
        static char const s17[] = "Since C++17";
        Coding::Message<s03> m03;
        Coding::Message<s11> m11;
        Coding::Message<s17> m17;
    }
    spdlog::info("Test template parameters type `auto`.");
    {
        Coding::Stack<int, 20> int20stack;
        Coding::Stack<int, 40u> int40stack;
        Coding::Stack<std::string, 40lu> string40stack;

        int20stack.push(20);
        std::cout << int20stack.top() << std::endl;
        int20stack.pop();

        string40stack.push("string40stack");
        std::cout << string40stack.top() << std::endl;
        string40stack.pop();

        if (!std::is_same_v<decltype(int20stack.size()), decltype(int40stack.size())>) {
            std::cout << "Size type differ.\n";
        }
        if (!std::is_same_v<decltype(int40stack.size()), decltype(string40stack.size())>) {
            std::cout << "Size type differ.\n";
        }
    }

    return 0;
}
