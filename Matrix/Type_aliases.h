#ifndef TYPE_ALIASES_H
#define TYPE_ALIASES_H

#include <vector>
#include <initializer_list>

//#include "Vector.hpp"
#include "Random.hpp"

namespace linarg
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

    /*template<typename C>
    using randui_mt19937        = rd::Random<C, uniform_int<int>, mersenne19937>;

    template<typename C>
    using randull_mt19937       = rd::Random<C, uniform_int<long long>, mersenne19937>;

    template<typename C>
    using randrf_mt19937        = rd::Random<C, uniform_real<float>, mersenne19937>;

    template<typename C>
    using randrd_mt19937        = rd::Random<C, uniform_real<double>, mersenne19937>;

    template<typename C>
    using randrld_mt19937       = rd::Random<C, uniform_real<long double>, mersenne19937>;*/


} // namespace linarg

#endif // TYPE_ALIASES_H
