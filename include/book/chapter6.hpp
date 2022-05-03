#ifndef _CHAPTER6_HPP_
#define _CHAPTER6_HPP_

#include <iostream>
#include <utility>
#include <vector>

namespace Coding {

    //! perfect forwarding
    class X {};
    void f(X&) {
        std::cout << "f() for reference.\n";
    }
    void f(X const&) {
        std::cout << "f() for const reference.\n";
    }
    void f(X&&) {
        std::cout << "f() for movable object.\n";
    }

    //* imperfect forwarding
    void g(X& x) {
        f(x);
    }
    void g(X const& x) {
        f(x);
    }
    void g(X&& x) {
        f(x);
        f(std::move(x));
    }

    template <typename T>
    void h(T&& t) {
        f(std::forward<T>(t));
    }
    //! perfect forwarding

    //! special member function template
    class PersonA {
    private:
        std::string name;
    public:
        explicit PersonA(std::string const& n) : name(n) {
            std::cout << "Copy string const& for '" << name << "'.\n";
        }
        explicit PersonA(std::string&& n) : name(std::move(n)) {
            std::cout << "Move string&& for '" << name << "'.\n";
        }
        PersonA(PersonA const& p) : name(p.name) {
            std::cout << "Copy const& '" << name << "'.\n";
        }
        PersonA(PersonA&& p) : name(std::move(p.name)) {
            std::cout << "Move const&& '" << name << "'.\n";
        }
    };

    class PersonB {
    private:
        std::string name;
    public:
        template <typename Str>
        explicit PersonB(Str&& n) : name(std::forward<Str>(n)) {
            std::cout << "Move string&& for '" << name << "'.\n";
        }
        PersonB(PersonB const& p) : name(p.name) {
            std::cout << "Copy const& '" << name << "'.\n";
        }
        PersonB(PersonB&& p) : name(std::move(p.name)) {
            std::cout << "Move const&& '" << name << "'.\n";
        }
    };
    //! special member function template

    //! disable template with `enable_if<>`
    //* A kind of type trait.
    template <typename T>
    typename std::enable_if<(sizeof(T) > 4), void>::type foo() {}

    // type suffix `_t`
    template <typename T>
    std::enable_if_t<(sizeof(T) > 4), T> bar() { return T{}; }
    //! disable template with `enable_if<>`

}

#endif //! _CHAPTER6_HPP_
