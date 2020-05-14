#ifndef TRIANGULAR_FILL_HPP
#define TRIANGULAR_FILL_HPP

#include <complex>
#include "include/Matrix/Traits.hpp"

namespace linalg
{
    namespace detail
    {
        template<std::size_t N, typename... Ts>
        using selected_type = typename std::tuple_element<N, std::tuple<Ts...>>::type;

        template<std::size_t N, typename T>
        struct Compare
        {
            using type = selected_type<N, std::less<std::size_t>, std::greater<std::size_t>, std::not_equal_to<std::size_t>>;
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

        template<typename M, typename Container>
        void fill(M& matrix, Container container)
        {
            auto container_iterator = container.begin();

            for(auto diag_iter = matrix.begin_diag(); diag_iter != matrix.end_diag(); ++diag_iter, ++container_iterator)
            {
                *diag_iter = *container_iterator;
            }
        }


    } // namespace detail


    template<std::size_t N>
    struct Triangular_fill
    {
        static constexpr std::size_t compare_number = N;

        template<typename MS, typename T>
        static void fill(std::size_t rows, std::size_t cols, MS& matrix_storage, Random<T> random)
        {
            using value_type = typename MS::value_type;
            typename detail::Compare<N, value_type>::type pred;
            using size_type = typename MS::size_type;
            std::size_t non_zeros_size = detail::calc_non_zero<N>(rows);
            random.set_size(non_zeros_size);

            Array<value_type> values = random.get(std::is_arithmetic<value_type>{});

            for(size_type i = 0, k = 0; i < rows; ++i)
            {
                for(size_type j = 0; j < cols; ++j)
                {
                    value_type value = pred(i, j) ? value_type{} : values[k++];
                    matrix_storage[rows * j + i] = value;
                }
            }
        }

        template<typename MS>
        static void fill(std::size_t rows, std::size_t cols, MS& matrix_storage, typename MS::value_type data, std::true_type)
        {
            using matrix_value_type = typename MS::value_type;
            using size_type = typename MS::size_type;

            typename detail::Compare<N, matrix_value_type>::type pred;

            for(size_type i = 0; i < rows; ++i)
            {
                for(size_type j = 0; j < cols; ++j)
                {
                    matrix_value_type value = pred(i, j) ? matrix_value_type{} : matrix_value_type{data};
                    matrix_storage[rows * j + i] = value;
                }
            }
        }

        template<typename MS, typename Function>
        static void fill(std::size_t rows, std::size_t cols, MS& matrix_storage, Function function, std::false_type)
        {
            using value_type = typename MS::value_type;
            using size_type = typename MS::size_type;

            typename detail::Compare<N, value_type>::type pred;

            for(size_type i = 0; i < rows; ++i)
            {
                for(size_type j = 0; j < cols; ++j)
                {
                    value_type value = pred(i, j) ? value_type{} : function();
                    matrix_storage[rows * j + i] = value;
                }
            }
        }

        template<typename MS, typename VectorType>
        static void non_zeros(const MS& matrix_storage, std::size_t rows, std::size_t cols, VectorType& vector)
        {
            using value_type = typename MS::value_type;
            using size_type = typename MS::size_type;

            typename detail::Compare<N, value_type>::type pred;

            size_type size = detail::calc_non_zero<N>(rows);

            vector.resize(size);
            size_type count = 0;

            for(size_type i = 0; i < rows; ++i)
            {
                for(size_type j = 0; j < cols; ++j)
                {
                    if(!pred(i, j))
                    {
                        vector[count] = matrix_storage[rows * j + i];
                        count++;
                    }
                }
            }
        }
    };

    //

    using Lower    = Triangular_fill<0>;
    using Upper    = Triangular_fill<1>;
    using Diagonal = Triangular_fill<2>;

}

#endif // TRIANGULAR_FILL_HPP
