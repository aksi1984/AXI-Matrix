#ifndef TYPE_ALIASES_H
#define TYPE_ALIASES_H

#include <vector>
#include <initializer_list>

//#include "Vector.hpp"
#include "Random.hpp"

namespace linalg
{
    template<typename T>
    using List              = std::initializer_list<T>;

    template<typename T>
    using List_of_lists     = std::initializer_list<std::initializer_list<T>>;

    using vector_of_strings = std::vector<std::string>;

    template<typename T>
    using vector_of_vectors = std::vector<std::vector<T>>;

    //Random
    template<typename T>
    using uniform_int               = std::uniform_int_distribution<>;

    template<typename T>
    using uniform_real              = std::uniform_real_distribution<T>;

    using mersenne19937             = std::mt19937;
    using mersenne19937_64          = std::mt19937_64;

} // namespace linarg

#endif // TYPE_ALIASES_H
