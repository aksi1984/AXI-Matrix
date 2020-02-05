#ifndef TRIANGULAR_PARAM_HPP
#define TRIANGULAR_PARAM_HPP

#include "Traits.hpp"

namespace linarg
{
struct Triangular_describer
{
    template<typename M, typename T, typename Predicate>
    static void fill(M& matrix, T data, Predicate pred)
    {
        using value_type = typename M::value_type;
        using data_type = typename std::conditional<std::is_arithmetic<T>::value, traits::Arithmetic_value<T>, traits::Non_arithmetic_value<T>>::type;

        using size_type = typename M::size_type;

        for(size_type i = 0; i < matrix.rows(); ++i)
        {
            for(size_type j = 0; j < matrix.rows(); ++j)
            {
                value_type value = pred(i, j) ? static_cast<value_type>(0) : data_type::get(data);
                matrix(i, j) = value;
            }
        }
    }
};

struct Lower
{
    template<typename M, typename T>
    static void fill(M& matrix, T data)
    {
        using value_type = typename M::value_type;

        Triangular_describer::fill(matrix, data, std::less<value_type>());
    }
};

struct Upper
{
    template<typename M, typename T>
    static void fill(M& matrix, T data)
    {
        using value_type = typename M::value_type;

        Triangular_describer::fill(matrix, data, std::greater<value_type>());
    }
};

}

#endif // TRIANGULAR_PARAM_HPP
