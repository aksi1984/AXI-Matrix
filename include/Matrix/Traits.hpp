#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <type_traits>
//#include <vector>
//#include <initializer_list>

//#include "Container.hpp"
#include "include/Matrix/Aliases.h"

namespace linalg
{
    namespace traits
    {

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

        /////////////////////////////////////////////

        template<bool Cond, typename T>
        struct Type_of_random
        {
            using type = T;
        };

        template<typename T>
        struct Type_of_random<false, T>
        {
            using element_type = typename T::element_type;
            using type = typename element_type::result_type;
        };

        /////////////////////////////////////////////

        template<typename T>
        struct Arithmetic_value
        {
            static T get(T value)
            {
                return value;
            }
        };

        template<typename T>
        struct Non_arithmetic_value
        {
            using element_type = typename T::element_type;
            using type = typename element_type::result_type;

            static type get(T struct_type)
            {
                return  struct_type->get();
            }
        };

        //////////////////////////////////////////////

        template<typename T, typename... Ts>
        constexpr bool is_one_of()
        {
            return (std::is_same_v<T, Ts> || ...);
        }
    }
}

#endif // TRAITS_HPP
