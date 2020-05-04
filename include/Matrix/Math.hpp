#ifndef MATH_HPP
#define MATH_HPP

#include "Vector.hpp"
#include "Enums.hpp"


namespace linalg
{
    namespace math
    {
        template<typename M>
        void lu(const M& mat, M& L, M& U)
        {
            std::size_t n = mat.rows();

            if(!mat.is_square())
            {
                throw std::logic_error("Matrix is not square");
            }

            using value_type = typename M::value_type;

            for(std::size_t i = 0; i < n; ++i)
            {
                for(std::size_t k = i; k < n; ++k)
                {
                    value_type sum = 0;

                     for(std::size_t j = 0; j < i; ++j)
                     {
                         sum += L(i, j) * U(j, k);
                     }

                     U(i, k) = mat(i, k) - sum;
                 }

                 for(std::size_t k = i; k < n; ++k)
                 {
                     if(i == k)
                     {
                         L(i, i) = 1;
                     }
                     else
                     {
                        value_type sum = 0;

                        for(std::size_t j = 0; j < n; ++j)
                        {
                            sum += L(k, j) * U(j, i);
                        }

                        L(k, i) = (mat(k, i) - sum) / U(i, i);
                     }
                 }
            }
        }

        //////////////////////////////////////////////////////////////////

        template<typename T>
        bool compare(T value)
        {
            T eps = 1e-12;
            return std::fabs(value) > eps;
        }

        template<typename M, typename T = typename M::value_type>
        bool gauss_compute(M mat, Vector<T>& vec)
        {
            std::size_t n = mat.rows();

            for(std::size_t i = 0; i < n; ++i)
            {
                T multiplier;

                for(std::size_t j = i + 1; j < n; ++j)
                {
                    if(!compare(mat(i, i)))
                    {
                        return false;
                    }

                    multiplier = -(mat(j, i) / mat(i, i));

                    for(std::size_t k = i + 1; k <= n; ++k)
                    {
                        mat(j, k) += multiplier * mat(i, k);
                    }
                }
            }

            for(int i = static_cast<int>(n - 1); i >= 0; --i)
            {
                T sum = mat(i, n);

                for(int j = static_cast<int>(n - 1); j >= i + 1; --j)
                {
                    sum = sum - mat(i, j) * vec[j];
                }

                vec[i] = sum / mat(i, i);
            }

            return true;
        }

        template<typename M, typename T = typename M::value_type>
        Vector<T> gauss(M mat)
        {
            Vector<T> vec(mat.rows());

            if(!gauss_compute(mat, vec))
            {
                throw std::logic_error("Divisor zero");
            }

            return vec;
        }

        template<typename M>
        M cholesky(M mat)
        {
            if(!mat.is_square())
            {
                throw std::logic_error("No square matrix (" + std::to_string(mat.rows()) + "x" +
                                       std::to_string(mat.cols()) + ")");
            }

            using value_type = typename M::value_type;

            M lower(mat.size());

            std::size_t n = mat.rows();

            for(std::size_t j = 0; j < n; ++j)
            {
                for(std::size_t k = j; k < n; ++k)
                {
                    value_type sum = 0;

                    for(std::size_t i = 0; i < j; ++i)
                    {
                        sum += (lower(k, i) * lower(j, i));
                    }

                    lower(k, j) = mat(k, j) - sum;

                    if(j == k)
                    {
                        lower(k, j) = std::sqrt(lower(k, j));
                    }
                    else
                    {
                        lower(k, j) = lower(k, j) / lower(j ,j);
                    }
                }
            }

            return lower;
        }

        template<typename M>
        typename M::value_type det(M mat)
        {
            if(!mat.is_square())
            {
                throw std::logic_error("No square matrix (" + std::to_string(mat.rows()) + "x" +
                                       std::to_string(mat.cols()) + ")");
            }

            using value_type = typename M::value_type;

            value_type n_1;
            value_type n_2;
            value_type total = 1;
            value_type determinant = 1;

            std::size_t index;
            std::size_t n = mat.rows();

            Vector<value_type> temp(n + 1);

            for(std::size_t i = 0; i < n; i++)
            {
                index = i;

                while(mat(index, i) == 0 && index < n)
                {
                     index++;
                }

                if(index == n)
                {
                    continue;
                }

                if(index != i)
                {
                    for(std::size_t j = 0; j < n; j++)
                    {
                       std::swap(mat(index, j),mat(i, j));
                    }

                    determinant = determinant * std::pow(-1,index-i);
                }

                for(std::size_t j = 0; j < n; j++)
                {
                    temp[j] = mat(i, j);
                }

                for(std::size_t j = i+1; j < n; j++)
                {
                    n_1 = temp[i];
                    n_2 = mat(j, i);


                    for(std::size_t k = 0; k < n; k++)
                    {
                         mat(j, k) = (n_1 * mat(j, k)) - (n_2 * temp[k]);
                    }

                    total = total * n_1;
                }
            }

            for(std::size_t i = 0; i < n; i++)
            {
                determinant = determinant * mat(i, i);
            }

            return (determinant/total);
        }

        template<typename M>
        typename M::value_type accumulate(const M& mat)
        {
            return std::accumulate(mat.cbegin(), mat.cend(), 0);
        }

        template<typename M>
        typename M::value_type diagsum(M mat)
        {
            using value_type = typename M::value_type;
            value_type sum = 0;

            for(auto iter = mat.begin_diag(); iter != mat.end_diag(); ++iter)
            {
                sum += *iter;
            }

            return sum;
        }

   } // namespace math

} // namespace axi

#endif // MATH_HPP
