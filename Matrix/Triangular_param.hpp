#ifndef TRIANGULAR_PARAM_HPP
#define TRIANGULAR_PARAM_HPP

#include "Traits.hpp"

namespace linarg
{
struct Triangular_describer
{
    template<typename M, typename T, typename Predicate>
    static void fill(std::size_t rows, std::size_t cols, M& storage, T data, Predicate pred)
    {
        using value_type = typename M::value_type;
        using data_type = typename std::conditional<std::is_arithmetic<T>::value, traits::Arithmetic_value<T>, traits::Non_arithmetic_value<T>>::type;

        using size_type = typename M::size_type;

        for(size_type i = 0; i < rows; ++i)
        {
            for(size_type j = 0; j < cols; ++j)
            {
                value_type value = pred(i, j) ? static_cast<value_type>(0) : data_type::get(data);
                storage[rows * j + i] = value;
            }
        }
    }
};

struct Lower
{
    template<typename M, typename T>
    static void fill(std::size_t rows, std::size_t cols, M& matrix, T data)
    {
        using value_type = typename M::value_type;

        Triangular_describer::fill(rows, cols, matrix, data, std::less<value_type>());
    }
};

struct Upper
{
    template<typename M, typename T>
    static void fill(std::size_t rows, std::size_t cols, M& matrix, T data)
    {
        using value_type = typename M::value_type;

        Triangular_describer::fill(rows, cols, matrix, data, std::greater<value_type>());
    }
};

}

#endif // TRIANGULAR_PARAM_HPP
