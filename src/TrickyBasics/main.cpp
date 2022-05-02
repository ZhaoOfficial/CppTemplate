#include <bitset>
#include <iostream>
#include <iomanip>
#include <type_traits>
#include <vector>

#include "book/chapter5.hpp"
#include "common.hpp"
#include "spdlog/spdlog.h"

int main() {

    spdlog::info("Test keyword `typename`.");
    {
        std::vector vi { 1, 2, 3, 4, 5 };
        Coding::printContainer(vi);
    }
    spdlog::info("Test zero initialization.");
    {
        Coding::undefinedValue<int>();
        Coding::zeroInitializedValue<int>();
        Coding::undefinedValue<double>();
        Coding::zeroInitializedValue<double>();
    }
    spdlog::info("Test using `this->`.");
    {
        Coding::Derived<int> foo{};
    }
    spdlog::info("Test templates for raw arrays and string literals.");
    {
        int x[] = {1, 2, 3, 4, 5};
        int y[] = {1, 2, 3, 4, 5, 6, 7};
        std::cout << Coding::less(x, y) << '\n';
        std::cout << Coding::less("123", "abc") << '\n';
        
        int a[14];
        extern int b[];
        Coding::MyClass<decltype(a)>::print();
        Coding::MyClass<decltype(b)>::print();
        Coding::testMyClass(a, a, a, b, b, b, b);
        Coding::print<'\n', '\0'>(
            "The reason is:",
            "1. Call by value, the array decays to pointer.",
            "2. For a known bounded array, remove the length makes decay.",
            "3. Normal behavior.",
            "4. Normal behavior.",
            "5. Same as 1.",
            "6. Normal behavior.",
            "7. Normal behavior."
        );
    }
    spdlog::info("Test member templates.");
    {
        Coding::Stack<int> intStack;
        for (int i = 0; i < 10; i++) {
            intStack.push(i);
        }
        Coding::Stack<float> floatStack;
        for (int i = 10; i < 20; ++i) {
            floatStack.push(static_cast<float>(i) + 0.5f);
        }
        Coding::print("Before assignment, the top is:", floatStack.top());
        floatStack = intStack;
        Coding::print("After assignment, the top is:", floatStack.top());

        std::cout << std::boolalpha;
        Coding::BoolString s1("hello");
        std::cout << s1.get() << '\n';
        std::cout << s1.get<bool>() << '\n';
        Coding::BoolString s2("ok");
        std::cout << s2.get<bool>() << '\n';

        Coding::printBitset<32>(std::bitset<32>{0xDEAD});
        std::cout << '\n';

        std::cout << "lambda function is a shortcut for overloading of member function `opertor()`\n";
    }
    spdlog::info("Test variable templates.");
    {
        std::cout << std::setprecision(8) << Coding::pi<float> << '\n';
        std::cout << std::setprecision(16) << Coding::pi<double> << '\n';
        // default long double
        std::cout << std::setprecision(24) << Coding::pi<> << '\n';
        //! compile error, one should specify the bracket
        // Coding::pi;

        //* note that even when the initialization of and iteration over `int_arr`
        //* happens in different translation units, the same variable `int_arr` is still used.
        std::cout << Coding::val<'x'> << '\n';
        Coding::int_arr<10>[0] = 42;
        for (auto&& i: Coding::int_arr<10>) {
            std::cout << i << ' ';
        }
        std::cout << '\n';

        auto v = Coding::Alias<std::string>;
        std::cout << v << '\n';

        //* Type traits suffix _v
        std::cout << std::boolalpha << std::is_const_v<const char> << '\n';
        std::cout << std::boolalpha << std::is_const<const char>::value << '\n';
    }
    spdlog::info("Test template template parameters.");
    {
        std::cout << std::setprecision(6);
        Coding::TemplateStack<int> int_stack;
        Coding::TemplateStack<float> float_stack;

        int_stack.push(1);
        int_stack.push(2);
        std::cout << "int_stack.top(): " << int_stack.top() << '\n';

        float_stack.push(3.3f);
        std::cout << "float_stack.top(): " << float_stack.top() << '\n';

        float_stack = int_stack;
        std::cout << "float_stack.top(): " << float_stack.top() << '\n';
        float_stack.push(4.4f);
        std::cout << "float_stack.top(): " << float_stack.top() << '\n';

        Coding::TemplateStack<double, std::vector> double_stack;
        double_stack.push(5.5);
        double_stack.push(6.6);
        std::cout << "double_stack.top(): " << double_stack.top() << '\n';

        double_stack = float_stack;
        std::cout << "double_stack: ";
        while (not double_stack.empty()) {
            std::cout << double_stack.top() << ' ';
            double_stack.pop();
        }
        std::cout << '\n';
    }

    return 0;
}

int b[] = {1, 2, 3, 4, 5};
