#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <type_traits>
//#include <vector>
//#include <initializer_list>

#include "Container.hpp"
#include "Type_aliases.h"

namespace linarg
{
    namespace traits
    {
        template<typename T, typename C>
        struct is_list : std::false_type
        {
            using type = std::vector<T>;
        };

        template<typename T>
        struct is_list<T, List<T>>
        {
            using type = List<T>;
        };

        template<typename T, typename = void>
        struct is_linarg_vector : std::false_type { };

        template<typename T>
        struct is_linarg_vector<T, std::conditional_t<false, std::void_t< typename T::struct_tag >, void>> : public std::true_type { };

        template<typename T, typename = void>
        struct is_matrix : std::false_type { };


        template<typename T>
        struct is_matrix<T, std::conditional_t<false, std::void_t< typename T::base,
                                                                   //decltype(std::declval<T>().is_square()),
                                                                   decltype(std::declval<T>().rows()),
                                                                   decltype(std::declval<T>().cols())//,
                                                                   //decltype(std::declval<T>().transpose())
                                                                 >, void >> : public std::true_type { };


        template<typename T, typename = void>
        struct is_complex : std::false_type { };

        template<typename T>
        struct is_complex<T, std::conditional_t<false, std::void_t < typename T::value_type,
                                                                     decltype(std::declval<T>().real()),
                                                                     decltype(std::declval<T>().imag())
                                                                   >, void
                                                                   > > : public std::true_type { };       


        template<bool Cond, typename T>
        struct Get_type
        {
            using type = typename T::value_type;
        };

        template<typename T>
        struct Get_type<false, T>
        {
            using type = T;
        };

    }
}

#endif // TRAITS_HPP
