#ifndef _CHAPTER5_HPP_
#define _CHAPTER5_HPP_

#include <array>
#include <bitset>
#include <cassert>
#include <deque>
#include <iostream>

#include "common.hpp"

namespace Coding {

    template <typename Container>
    void printContainer(Container const& container) {
        typename Container::const_iterator cit;
        for (cit = container.begin(); cit != container.end(); ++cit) {
            std::cout << *cit << ' ';
        }
        std::cout << '\n';
    }

    template <typename T>
    void undefinedValue() {
        // T x;
        // T* ptr;
        print<'\n', '\0'>(
            "If T is a built-in type, then x has a undefined value, but GCC will give a warning.",
            "If T is a built-in type, then ptr has a zero value, but GCC will give a warning."
        );
    }

    template <typename T>
    void zeroInitializedValue() {
        T x{};
        T* ptr{};
        print(
            "If T is a built-in type, then it has a zero value: x =", x,
            "If T is a built-in type, then it has a zero value: ptr =", ptr
        );
    }

    //! using `this->`
    template <typename T>
    class Base {
    public:
        void base() {}
    };

    template <typename T>
    class Derived : Base<T> {
    public:
        void derived() {
            //! `base()` deined in `Base` is never considered, use `this->`
            // base();
            this->base();
        }
    };
    //! using `this->`

    template <typename T, int M, int N>
    bool less(T(&a)[M], T(&b)[N]) {
        int minimum = std::min<int>(M, N);
        for (int i = 0; i < minimum; ++i) {
            if (a[i] < b[i]) return true;
            if (b[i] < a[i]) return false;
        }
        return M < N;
    }

    //! MyClass
    template <typename T>
    struct MyClass;

    //* partial specialization for arrays of known bounds
    template <typename T, std::size_t Size>
    struct MyClass<T[Size]> {
        static void print() {
            std::cout << "1 print() for T [" << Size << "]\n";
        }
    };

    //* partial specialization for reference to arrays of known bounds
    template <typename T, std::size_t Size>
    struct MyClass<T(&)[Size]> {
        static void print() {
            std::cout << "2 print() for T(&)[" << Size << "]\n";
        }
    };

    //* partial specialization for arrays of unknown bounds
    template <typename T>
    struct MyClass<T[]> {
        static void print() {
            std::cout << "3 print() for T []\n";
        }
    };

    //* partial specialization for reference to arrays of unknown bounds
    template <typename T>
    struct MyClass<T(&)[]> {
        static void print() {
            std::cout << "4 print() for T(&)[]\n";
        }
    };

    //* partial specialization for pointer
    template <typename T>
    struct MyClass<T*> {
        static void print() {
            std::cout << "5 print() for T*\n";
        }
    };

    template <typename T, typename U, typename V>
    void testMyClass(int a[7], int b[], int (&c)[14], int (&d)[], T e, U& f, V&& g) {
        MyClass<decltype(a)>::print();
        MyClass<decltype(b)>::print();
        MyClass<decltype(c)>::print();
        MyClass<decltype(d)>::print();
        MyClass<decltype(e)>::print();
        MyClass<decltype(f)>::print();
        MyClass<decltype(g)>::print();
    }
    //! MyClass

    //! Stack
    template <typename T, typename Container = std::deque<T>>
    class Stack {
    private:
        Container elems;
    public:
        Stack() = default;
        Stack(T const& elem) : elems({elem}) {}
        template <typename U, typename C>
        Stack& operator=(Stack<U, C> const& other);

        void push(T const& elem);
        void pop();
        T const& top() const;
        bool empty() const;

        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, Stack<U> const& s);
        //* to get access to private members of `Stack<T>` for any type `T`
        template <typename, typename> friend class Stack;
    };

    template <typename T, typename Container>
    template <typename U, typename C>
    Stack<T, Container>& Stack<T, Container>::operator=(Stack<U, C> const& other) {
        this->elems.clear();
        this->elems.insert(this->elems.begin(), other.elems.begin(), other.elems.end());
        return *this;
    }

    template <typename T, typename Container>
    void Stack<T, Container>::push(T const& elem) {
        this->elems.push_back(elem);
    }

    template <typename T, typename Container>
    void Stack<T, Container>::pop() {
        assert(!this->elems.empty());
        this->elems.pop_back();
    }

    template <typename T, typename Container>
    T const& Stack<T, Container>::top() const {
        assert(!this->elems.empty());
        return this->elems.back();
    }

    template <typename T, typename Container>
    bool Stack<T, Container>::empty() const {
        return this->elems.empty();
    }

    template <typename U>
    std::ostream& operator<<(std::ostream& out, Stack<U> const& s) {
        for (const auto&& e : s.elems) {
            out << e;
        }
        return out;
    }
    //! Stack

    //! BoolString
    class BoolString {
    private:
        std::string value;
    public:
        BoolString(std::string const& s) : value{s} {}
        template <typename T = std::string>
        T get() const {
            return this->value;
        }
    };

    //* full specialization for `BoolString::get<>()` for `bool`
    template <>
    inline bool BoolString::get<bool>() const {
        return value == "true" || value == "1" || value == "ok";
    }
    //! BoolString

    //! `.template` construct
    //* This is a problem only if the construct before the period depends on a template parameter.
    template <uint32_t N>
    void printBitset(std::bitset<N> const& bs) {
        std::cout << bs.template to_string<char, std::char_traits<char>, std::allocator<char>>();
    }
    //! `.template` construct

    //! variable template
    template <typename T = long double>
    constexpr T pi{3.1415926535897932385L};

    //* zero initialization
    template <std::size_t N>
    std::array<int, N> int_arr{};

    //* type deduction
    template <auto N>
    constexpr decltype(N) val = N;
    //! variable template

    //! alias of template parameter
    template <typename T>
    struct Origin {
        static constexpr int value = 100;
    };

    template <typename T>
    int Alias = Origin<T>::value;
    //! alias of template parameter

    //! template template parameter
    template <
        typename T,
        template <
            typename Elem, typename Alloc = std::allocator<Elem>
        > class Container = std::deque
    >
    class TemplateStack {
    private:
        Container<T> elems;
    public:
        void push(T const& elem);
        void pop();
        T const& top() const;
        bool empty() const;

        template <
            typename U,
            template <
                typename Elem2, typename Alloc2 = std::allocator<Elem2>
            > class Container2
        >
        TemplateStack<T, Container>& operator=(TemplateStack<U, Container2> const& other);
        template <typename, template <typename, typename> class>
        friend class TemplateStack;
    };

    template <typename T, template <typename, typename> class Container>
    void TemplateStack<T, Container>::push(T const& elem) {
        this->elems.push_back(elem);
    }

    template <typename T, template <typename, typename> class Container>
    void TemplateStack<T, Container>::pop() {
        assert(!this->elems.empty());
        this->elems.pop_back();
    }

    template <typename T, template <typename, typename> class Container>
    T const& TemplateStack<T, Container>::top() const {
        assert(!this->elems.empty());
        return this->elems.back();
    }

    template <typename T, template <typename, typename> class Container>
    bool TemplateStack<T, Container>::empty() const {
        return this->elems.empty();
    }

    template <typename T, template <typename, typename> class Container>
    template <typename U, template <typename, typename> class Container2>
    TemplateStack<T, Container>& TemplateStack<T, Container>::operator=(TemplateStack<U, Container2> const& other) {
        this->elems.clear();
        this->elems.insert(this->elems.begin(), other.elems.begin(), other.elems.end());
        return *this;
    }


    //! template template parameter

} // !namespace Coding

#endif // !_CHAPTER5_HPP_
