#ifndef _CHAPTER4_HPP_
#define _CHAPTER4_HPP_

#include <iostream>
#include <cstring>

#include "common.hpp"

namespace Coding {

    //! print
    void print1() {}

    template <typename T, typename... Types>
    void print1(T arg, Types... args) {
        std::cout << arg << std::endl;
        print1(args...);
    }

    void print2() {
        std::cout << '\n';
    }

    template <typename T>
    void print2(T arg) {
        // if there is only one element
        std::cout << arg << '\n';
    }

    template <typename T, typename... Types>
    void print2(T arg, Types... args) {
        // if there are two elements,
        // it will call `print(T arg)` twice
        print2(arg);
        print2(args...);
    }
    //! print

    //! count
    template <typename... Types>
    void count(Types... args) {
        std::cout << "Number of elements: sizeof...(Types) = " << sizeof...(Types) << '\n';
        std::cout << "Number of elements: sizeof...(args) = " << sizeof...(args) << '\n';
    }
    //! count

    //! foldSum
    template <typename... Types>
    auto foldSum(Types... args) {
        return (... + args);
    }
    //! foldSum

    //! binary tree
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    template <typename T, typename... Types>
    Node* traverse(T root, Types... paths) {
        // root -> *path1 -> *path2 ...
        return (root ->* ... ->* paths);
    }
    //! binary tree

    //! some print
    template <typename T, typename... Types>
    constexpr bool is_homogeneous(T const& first, Types const&... args) {
        return (std::is_same<T, Types>::value && ...);
    }

    template <typename... Types>
    void printDouble(Types const&... args) {
        print(args + args...);
    }

    template <typename... Types>
    void addOne(Types const&... args) {
        print((args + 1)...);
    }

    template <typename Container, typename... Index>
    void printElems(Container const& container, Index const&... index) {
        print(container[index]...);
    }

    template <std::size_t... index, typename Container>
    void printIndex(Container const& container) {
        print(container[index]...);
    }
    //! some print

    //! Customer
    class Customer {
    private:
        std::string name;
    public:
        Customer(std::string const& n) : name(n) {}
        std::string getName() const { return this->name; }
    };

    struct CustomerEq {
        bool operator()(Customer const& c1, Customer const& c2) const {
            std::cout << "CustomerEq::operator() called.\n";
            return c1.getName() == c2.getName();
        }
    };

    struct CustomerHash {
        std::size_t operator()(Customer const& c) const {
            std::cout << "CustomerHash::operator() called.\n";
            return std::hash<std::string>{}(c.getName());
        }
    };

    template <typename... Bases>
    struct Overloader : public Bases... {
        using Bases::operator()...;
    };
    //! Customer
}

#endif // !_CHAPTER4_HPP_
