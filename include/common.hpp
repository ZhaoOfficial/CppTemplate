#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <iostream>

namespace Coding {
    //* A Python-like print
    template <typename T>
    class AddSep {
    private:
        T const& ref;
        char sep;
    public:
        AddSep(T const& ref, char sep) : ref(ref), sep(sep) {}
        friend std::ostream& operator<<(std::ostream& os, const AddSep<T>& s) {
            return os << s.ref << s.sep;
        }
    };

    template <char Sep = ' ', char End = '\n', typename... Types>
    void print(Types... args) {
        (std::cout << ... << AddSep(args, Sep)) << End;
    }
    //* A Python-like print
}

#endif // !_COMMON_HPP_
