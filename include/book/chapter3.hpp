#ifndef _CHAPTER3_HPP_
#define _CHAPTER3_HPP_

#include <array>
#include <cassert>

namespace Coding {

    //! addValue
    template <int Value, typename T>
    T addValue(T x) {
        return x + Value;
    }
    //! addValue

    //! Restriction
    template <char const Str[]>
    class Message {
    public:
        Message() {
            std::cout << "Construct: " << Str << std::endl;
        }
    };
    //! Restriction

    //! Stack auto
    template <typename T, auto Capacity>
    class Stack {
    public:
        using size_type = decltype(Capacity);
    private:
        std::array<T, Capacity> elems;
        size_type num_elems;

    public:
        Stack();
        void push(T const& elem);
        void pop();
        T const& top() const;
        bool empty() const;
        auto size() const;
    };

    template <typename T, auto Capacity>
    Stack<T, Capacity>::Stack() : num_elems{0} {}

    template <typename T, auto Capacity>
    void Stack<T, Capacity>::push(T const& elem) {
        assert(this->num_elems < Capacity);
        this->elems[this->num_elems] = elem;
        ++this->num_elems;
    }

    template <typename T, auto Capacity>
    void Stack<T, Capacity>::pop() {
        assert(!this->elems.empty());
        --this->num_elems;
    }

    template<typename T, auto Capacity>
    T const& Stack<T, Capacity>::top() const {
        assert(!this->elems.empty());
        return this->elems[this->num_elems - 1];
    }

    template <typename T, auto Capacity>
    bool Stack<T, Capacity>::empty() const {
        return this->num_elems == 0;
    }

    template <typename T, auto Capacity>
    auto Stack<T, Capacity>::size() const {
        return this->num_elems;
    }
    //! Stack
}

#endif // !_CHAPTER3_HPP_
