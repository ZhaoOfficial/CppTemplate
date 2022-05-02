#include <iostream>

#include "book/chapter1.hpp"
#include "spdlog/spdlog.h"

int main() {

    spdlog::info("Introduction to function template.");
    {
        int i1 { 100 };
        int i2 { 0 };
        std::cout << "Coding::max(i1, i2) = " << Coding::max(i1, i2) << std::endl;

        double d1 { 3.4 };
        double d2 { -5.6 };
        std::cout << "Coding::max(d1, d2) = " << Coding::max(d1, d2) << std::endl;

        std::string s1 { "Math" };
        std::string s2 { "Mathematics" };
        std::cout << "Coding::max(s1, s2) = " << Coding::max(s1, s2) << std::endl;
    }
    spdlog::info("Introduction to function template overloading.");
    {
        int i1 = 7;
        int i2 = 42;
        std::cout << "Coding::max(i1, i2) = " << Coding::max(i1, i2) << std::endl;

        std::string s1 { "hey" };
        std::string s2 { "you" };
        std::cout << "Coding::max(s1, s2) = " << Coding::max(s1, s2) << std::endl;

        int *p1 = &i1;
        int *p2 = &i2;
        std::cout << "Coding::max(p1, p2) = " << Coding::max(p1, p2) << std::endl;

        char const* c1 = "hello";
        char const* c2 = "world";
        std::cout << "Coding::max(c1, c2) = " << Coding::max(c1, c2) << std::endl;

    }

    return 0;
}

