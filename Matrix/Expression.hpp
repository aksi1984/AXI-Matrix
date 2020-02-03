#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <regex>
#include <numeric>
#include <iostream>

#include "Conversions.hpp"
#include "Exception.hpp"
#include "Type_aliases.h"

namespace linarg
{

    template<std::size_t N, typename... Ts>
    struct Select;

    template<std::size_t N, typename T, typename... Ts>
    struct Select<N, T, Ts...> : Select<N - 1, Ts...> { };

    template<typename T, typename... Ts>
    struct Select<0, T, Ts...> { using type = T; };

    ///////////////////////////////////////////////////////////

    template<typename T>
    class Expression
    {
    public:

        using value_type    = T;

        Expression(const std::string& expr);

        void start();
        vector_of_vectors<T> get() const noexcept;

    private:

        vector_of_strings split(const std::string& expr, char denom, bool denom_preserve = false);

        void erase_parenth(vector_of_strings& str_vec);

        vector_of_vectors<std::string> get_only_numbers(const vector_of_strings& str_vec);

        void convert(const vector_of_vectors<std::string> &str_map);

        void expr_check(const vector_of_strings& expr_vec);

        std::regex pattern_;
        std::string expr_;

        vector_of_vectors<T> expr_map_;
    };

} // namespace linarg

#endif // EXPRESSION_HPP
