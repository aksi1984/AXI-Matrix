#ifndef COND_HPP
#define COND_HPP

#include <type_traits>
#include <vector>

#include "Aliases.h"

namespace linalg
{
    template<typename T, typename C>
    struct is_initializer_list : std::false_type
    {
        using type = std::vector<T>;
    };

    template<typename T>
    struct is_initializer_list<T, List<T>>
    {
        using type = List<T>;
    };

    ////////////////////////////////////////////////////////

    template<typename T, typename = void>
    struct is_linarg_vector : std::false_type { };

    template<typename T>
    struct is_linarg_vector<T, std::conditional_t<false, std::void_t< typename T::storage_type >, void>> : public std::true_type { };


    ////////////////////////////////////////////////////////

    template<typename T, typename = void>
    struct is_complex : std::false_type { };

    template<typename T>
    struct is_complex<T, std::conditional_t<false, std::void_t < typename T::value_type,
                                                                 decltype(std::declval<T>().real()),
                                                                 decltype(std::declval<T>().imag())
                                                               >, void
                                                               > > : public std::true_type { };

    /////////////////////////////////////////////////////////


    template<typename T, typename = void>
    struct is_matrix : std::false_type { };


    template<typename T>
    struct is_matrix<T, std::conditional_t<false, std::void_t< typename T::base,
                                                               decltype(std::declval<T>().rows()),
                                                               decltype(std::declval<T>().cols())
                                                             >, void >> : public std::true_type { };

    ////////////////////////////////////////////////////////

    template<typename T>
    struct is_functor
    {
        typedef char true_t[1];
        typedef char false_t[2];

        template<typename U> static true_t& check(decltype(&U::operator()));
        template<typename U> static false_t& check(...);

        static constexpr bool value = ( sizeof(check<T>(0)) == sizeof(true_t) );
    };

} // namespace linarg

#endif // COND_HPP
