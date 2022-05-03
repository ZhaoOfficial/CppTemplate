#include <iostream>

#include "book/chapter6.hpp"
#include "common.hpp"
#include "spdlog/spdlog.h"

int main() {

    spdlog::info("Test perfect forwarding.");
    {
        Coding::X x;
        Coding::X const cx;

        std::cout << "Imperfect forwarding.\n";
        g(x);
        g(cx);
        g(Coding::X{});
        g(std::move(x));

        std::cout << "Perfect forwarding.\n";
        h(x);
        h(cx);
        h(std::move(x));
        h(Coding::X{});
    }
    spdlog::info("Test special member function templates.");
    {
        std::string s("sname");
        std::cout << "Normal class.\n";
        Coding::PersonA p1(s);
        Coding::PersonA p2("temp");
        Coding::PersonA p3(p1);
        Coding::PersonA p4(std::move(p1));

        std::cout << "Template class.\n";
        Coding::PersonB p5(s);
        //* char const[5]
        Coding::PersonB p6("temp");
        //! compile error
        //* The reason is, non-const lvalue constructor is prior to the copy constructor.
        // Coding::PersonB p7(p5);
        Coding::PersonB p8(std::move(p5));
        Coding::PersonB const p9("ctemp");
        Coding::PersonB p10(p9);
    }
    spdlog::info("Test disable templates with `enable_if<>`.");
    {
        //! compile error
        //* sizeof(int) == 4, then there are no false type of enable_if<>, then compile error.
        // Coding::foo<int>();
        Coding::foo<double>();
        Coding::bar<double>();
    }

    return 0;
}
