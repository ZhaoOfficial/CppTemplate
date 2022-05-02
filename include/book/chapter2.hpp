#ifndef _CHAPTER2_HPP_
#define _CHAPTER2_HPP_

#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

namespace Coding {

    //! Stack
    template <typename T>
    class Stack {
    private:
        std::vector<T> elems;
    public:
        Stack() = default;
        Stack(T const& elem) : elems({elem}) {}

        void push(T const& elem);
        void pop();
        T const& top() const;
        bool empty() const;

        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, Stack<U> const& s);
    };

    template <typename T>
    void Stack<T>::push(T const& elem) {
        elems.push_back(elem);
    }

    template <typename T>
    void Stack<T>::pop() {
        assert(!elems.empty());
        elems.pop_back();
    }

    template <typename T>
    T const& Stack<T>::top() const {
        assert(!elems.empty());
        return elems.back();
    }

    template <typename T>
    bool Stack<T>::empty() const {
        return elems.empty();
    }

    template <typename U>
    std::ostream& operator<<(std::ostream& out, Stack<U> const& s) {
        for (const auto&& e : s.elems) {
            out << e;
        }
        return out;
    }
    //* Deduction Guide
    Stack(char const*) -> Stack<std::string>;
    //! Stack

    //! Stack, full specialized version
    template <>
    class Stack<std::string> {
    private:
        std::vector<std::string> elems;
    public:
        Stack() = default;
        Stack(std::string const& elem) : elems({elem}) {}
        Stack(char const* elem) : elems({elem}) {}

        void push(std::string const& elem);
        void pop();
        std::string const& top() const;
        bool empty() const;
    };

    void Stack<std::string>::push(std::string const& elem) {
        std::cout << "Push " << elem << "\n";
        elems.push_back(elem);
    }

    void Stack<std::string>::pop() {
        assert(!elems.empty());
        std::cout << "Pop " << elems.back() << "\n";
        elems.pop_back();
    }

    std::string const& Stack<std::string>::top() const {
        assert(!elems.empty());
        return elems.back();
    }

    bool Stack<std::string>::empty() const {
        return elems.empty();
    }
    //! Stack

    //! Stack, partial specialized version
    template <typename T>
    class Stack<T*> {
    private:
        std::vector<T*> elems;
    public:
        void push(T* elem);
        void pop();
        T* top() const;
        bool empty() const;
    };

    template <typename T>
    void Stack<T*>::push(T* elem) {
        elems.push_back(elem);
    }

    template <typename T>
    void Stack<T*>::pop() {
        assert(!elems.empty());
        elems.pop_back();
    }

    template <typename T>
    T* Stack<T*>::top() const {
        assert(!elems.empty());
        return elems.back();
    }

    template <typename T>
    bool Stack<T*>::empty() const {
        return elems.empty();
    }
    //! Stack

    //! Partial specialization with multiple parameters
    template <typename T1, typename T2>
    class MyClass {
    public:
        MyClass() {
            std::cout << "Using template <typename T1, typename T2> class MyClass {};" << std::endl;
        }
    };

    template <typename T>
    class MyClass<T, T> {
    public:
        MyClass() {
            std::cout << "Using template <typename T> class MyClass<T, T> {};" << std::endl;
        }
    };

    template <typename T>
    class MyClass<T, int> {
    public:
        MyClass() {
            std::cout << "Using template <typename T> class MyClass<T, int> {};" << std::endl;
        }
    };

    template <typename T1, typename T2>
    class MyClass<T1*, T2*> {
    public:
        MyClass() {
            std::cout << "Using template <typename T1, typename T2> class MyClass<T1*, T2*> {};" << std::endl;
        }
    };
    //! Partial specialization with multiple parameters

    //! Default class template arguments
    template <typename T, typename Container = std::deque<T>>
    class Queue {
    private:
        Container elems;
    public:
        void push(T const& elem);
        void pop();
        T const& front() const;
        bool empty() const;
    };

    template <typename T, typename Container>
    void Queue<T, Container>::push(T const& elem) {
        elems.push_back(elem);
    }

    template <typename T, typename Container>
    void Queue<T, Container>::pop() {
        assert(!elems.empty());
        elems.pop_front();
    }

    template <typename T, typename Container>
    T const& Queue<T, Container>::front() const {
        assert(!elems.empty());
        return elems.front();
    }

    template <typename T, typename Container>
    bool Queue<T, Container>::empty() const {
        return elems.empty();
    }
    //! Default class template arguments

} //! namespace Coding

#endif // !_CHAPTER2_HPP_
