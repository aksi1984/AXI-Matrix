#ifndef EXPRESSION_TCC
#define EXPRESSION_TCC

#include "Expression.hpp"

namespace linalg
{
    template<typename T>
    Expression<T>::Expression(const std::string& expr) :
        pattern_{R"(\{(\d+\,{1})*(\d+){1}\})"},
        expr_{expr} { }

    template<typename T>
    void
    Expression<T>::start()
    {
        vector_of_strings expr_vec = split(expr_, '}', true);
        expr_check(expr_vec);
        erase_parenth(expr_vec);
        auto expr_map = get_only_numbers(expr_vec);
        convert(expr_map);
    }

    template<typename T>
    vector_of_vectors<T>
    Expression<T>::get() const noexcept
    {
        return expr_map_;
    }

    template<typename T>
    vector_of_strings
    Expression<T>::split(const std::string& expr, char denom, bool denom_preserve)
    {
        std::size_t previous = 0;
        std::size_t current = expr.find(denom);
        std::size_t n = denom_preserve ? 1 : 0;

        std::vector<std::string> str_vec;

        while(current != std::string::npos)
        {
            str_vec.push_back(expr.substr(previous, current - previous + n));
            previous = current + 1;
            current = expr.find(denom, previous);
        }

        if(!denom_preserve)
        {
            str_vec.push_back(expr.substr(previous, current - previous + n));
        }

        return str_vec;
    }

    template<typename T>
    void
    Expression<T>::erase_parenth(vector_of_strings& str_vec)
    {
        for(std::size_t i = 0; i < str_vec.size(); ++i)
        {
            str_vec[i].erase( std::remove_if(str_vec[i].begin(), str_vec[i].end(), [](char ch){return ch == '}';}), str_vec[i].end() );
            str_vec[i].erase( std::remove_if(str_vec[i].begin(), str_vec[i].end(), [](char ch){return ch == '{';}), str_vec[i].end() );
        }
    }

    template<typename T>
    vector_of_vectors<std::string>
    Expression<T>::get_only_numbers(const vector_of_strings& str_vec)
    {
        vector_of_vectors<std::string> only_num_map;

        for(std::size_t i = 0; i < str_vec.size(); ++i)
        {
            only_num_map.push_back(split(str_vec[i], ','));
        }

        return only_num_map;
    }

    template<typename T>
    void
    Expression<T>::convert(const vector_of_vectors<std::string>& str_map)
    {
        using type = typename Select<conv::Conversion_type<T>::value, conv::Int, conv::Float, conv::Double, conv::Long_double>::type;

        for(std::size_t i = 0, key = 0; i < str_map.size(); ++i, ++key)
        {
            std::vector<T> temp;

            for(std::size_t j = 0; j < str_map[i].size(); ++j)
            {
                temp.push_back(type::convert(str_map[i].at(j)));
            }

            expr_map_.push_back(temp);
        }
    }

    template<typename T>
    void
    Expression<T>::expr_check(const vector_of_strings& expr_vec)
    {
        std::smatch match;

        for(auto x : expr_vec) LINALG_CHECK(std::regex_search(x, match, pattern_), Invalid_expression())
    }

} // namespace linarg

#endif // EXPRESSION_TCC
