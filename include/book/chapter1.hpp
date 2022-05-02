#ifndef _CHAPTER1_HPP_
#define _CHAPTER1_HPP_

#include <cstring>

namespace Coding {

    template <typename T>
    concept Comparable = requires(T a, T b) { a < b; };

    template <Comparable T>
    T max(const T& a, const T& b) {
        // To ensure the function behaves correctly
        // when `a` and `b` are equivalent but not the same variable.
        return b < a ? a : b;
    }

    template <Comparable T>
    T* max(const T* a, const T* b) {
        return *b < *a ? a : b;
    }

    char const* max(char const* a, char const* b) {
        return std::strcmp(b, a) < 0 ? a : b;
    }

} //! namespace Coding

#endif // !_CHAPTER1_HPP_
