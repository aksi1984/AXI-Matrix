#ifndef TRIANGULAR_PARAM_HPP
#define TRIANGULAR_PARAM_HPP

#include <complex>
#include "Traits.hpp"

namespace linarg
{

    template<std::size_t N, typename... Ts>
    using selected_type = typename std::tuple_element<N, std::tuple<Ts...>>::type;

    template<std::size_t N, typename T>
    struct Predicate
    {
        using type = selected_type<N, std::less<T>, std::greater<T>, std::not_equal_to<T>>;
    };

    template<std::size_t N>
    std::size_t calc_non_zero(std::size_t size)
    {
        return ( N != 2 ? ((1 + size) * size) / 2 : size );
    }

    template<typename T>
    Array<std::complex<T>> fill_with_cplx(std::size_t size, Random<T> random)
    {
        Array<std::complex<T>> cplx_array(size);

        for(std::size_t i = 0; i < cplx_array.size(); ++i)
        {
            std::complex<T> cplx;
            cplx.real(random.get());
            cplx.imag(random.get());
        }

        return cplx_array;
    }

    template<std::size_t N>
    struct Triangular_data
    {
        template<typename MS, typename T>
        static void fill(std::size_t rows, std::size_t cols, MS& matrix_storage, T data, std::false_type)
        {
            using matrix_value_type = typename MS::value_type;
            typename Predicate<N, matrix_value_type>::type pred;
            using data_type = typename std::conditional<std::is_arithmetic<T>::value, traits::Arithmetic_value<T>, traits::Non_arithmetic_value<T>>::type;
            using size_type = typename MS::size_type;
            std::size_t non_zeros_size = calc_non_zero<N>(rows);
            data.apply_size(non_zeros_size);

            Array<matrix_value_type> rd_array = data.get();

            for(size_type i = 0, k = 0; i < rows; ++i)
            {
                for(size_type j = 0; j < cols; ++j)
                {
                    matrix_value_type value = pred(i, j) ? static_cast<matrix_value_type>(0) : rd_array[k++];
                    matrix_storage[rows * j + i] = value;
                }
            }
        }

        template<typename MS, typename T>
        static void fill(std::size_t rows, std::size_t cols, MS& matrix_storage, T data, std::true_type)
        {
            using matrix_value_type = typename MS::value_type;
            using size_type = typename MS::size_type;

            typename Predicate<2, matrix_value_type>::type pred;

            for(size_type i = 0; i < rows; ++i)
            {
                for(size_type j = 0; j < cols; ++j)
                {
                    matrix_value_type value = pred(i, j) ? static_cast<matrix_value_type>(0) : data[i];
                    matrix_storage[rows * j + i] = value;
                }
            }
        }
    };

    //

    using Lower    = Triangular_data<0>;
    using Upper    = Triangular_data<1>;
    using Diagonal = Triangular_data<2>;

}

#endif // TRIANGULAR_PARAM_HPP
