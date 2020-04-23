#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <type_traits>

#include "Traits.hpp"
#include "Enums.hpp"
#include "Cond.hpp"

namespace linarg
{
    namespace algo
    {
        template<typename Iterator, typename T>
        void copy(Iterator first, Iterator last, T val)
        {
            for(auto iter = first; iter != last; ++iter)
            {
                *iter = val;
            }
        }

        template<typename Iterator>
        void copy(Iterator first, Iterator last, Iterator result)
        {
            for(auto iter = first; iter != last; ++iter, ++result)
            {
                *result = *iter;
            }
        }

        template<typename O, typename Pred>
        bool any_of(O obj, Pred pred)
        {
            std::size_t count = 0;

            for(auto iter = obj.begin(); iter != obj.end(); ++iter)
            {
                if(pred(*iter))
                {
                    count++;
                }
            }

            if constexpr(is_matrix<O>{})
            {
                return count == obj.rows() * obj.cols();
            }
            else
            {
                return count == obj.size();
            }
        }

        template<typename O>
        bool any_of(O obj)
        {
            using value_type = typename O::value_type;
            return any(obj, [](value_type val){ return compare(val); });
        }

        namespace priv
        {
            template<typename M, typename Pred>
            std::size_t any_of_in_row(M mat, std::size_t n, Pred pred)
            {
                std::size_t count = 0;

                for(auto iter = mat.begin_row(n); iter != mat.end_row(n); ++iter)
                {
                    if(pred(*iter))
                    {
                      count++;
                    }
                    else
                    {
                        break;
                    }
                }

                return count;
            }

            template<typename M, typename Pred>
            std::size_t any_of_in_col(M mat, std::size_t n, Pred pred)
            {
                std::size_t count = 0;

                for(auto iter = mat.begin_col(n); iter != mat.end_col(n); ++iter)
                {
                    if(pred(*iter))
                    {
                        count++;
                    }
                    else
                    {
                        break;
                    }
                }

                return count;
            }
        }

        template<typename M, typename Pred>
        bool any_of(M mat, std::size_t n, Dimension dim, Pred pred)
        {
            std::size_t count;

            if(dim == Dimension::Row)
            {
                count = priv::any_of_in_row(mat, n, pred);
                return count == mat.rows();
            }
            else
            {
                count = priv::any_of_in_col(mat, n, pred);
                return count == mat.cols();
            }
        }

        template<typename M>
        bool any_of(M mat, std::size_t n, Dimension dim)
        {
            using value_type = typename M::value_type;

            return any(mat, n, dim, [](value_type val){ return compare(val); });
        }

        enum Sort_dir
        {
            Ascend,
            Descend
        };

        template<typename Iterator>
        bool is_sorted(Iterator first, Iterator last, Sort_dir dir)
        {
            Iterator next = first;

            while(++next != last)
            {
                if(bool cond = ( dir == Sort_dir::Ascend ? *next < *first : *next > *first);
                        cond)
                {
                    return false;
                }

                first++;
            }

            return true;
        }

        namespace priv
        {
            enum Diag_check_type
            {
                All,
                Outside
            };

            template<typename M, typename Pred>
            bool is_diagonal_priv(M mat, Pred pred, Diag_check_type type)
            {
                std::size_t zeros = 0;

                for(std::size_t i = 0; i < mat.rows(); ++i)
                {
                    for(std::size_t j = 0; j < mat.cols(); ++j)
                    {
                        if(pred(i, j))
                        {
                            if(mat(i, j) == 0)
                            {
                                zeros++;
                            }
                        }
                    }
                }

                std::size_t total_entries = ((( mat.rows() * mat.cols() )) - mat.rows());
                std::size_t entries = ( type == Diag_check_type::All ? total_entries : total_entries / 2 );

                return zeros == entries;
            }
        }

        template<typename M>
        typename std::enable_if<is_complex<typename M::value_type>::value, bool>::type
        is_diagonal(M mat)
        {
            bool diag_check = priv::is_diagonal_priv(mat, [](std::size_t i, std::size_t j){ return i != j; }, priv::Diag_check_type::All);

            return diag_check;
        }

        template<typename M>
        typename std::enable_if<!is_complex<typename M::value_type>::value, bool>::type
        is_unit(M mat)
        {
            if(!mat.is_square())
            {
                return false;
            }

            bool diagonal = priv::is_diagonal_priv(mat, [](std::size_t i, std::size_t j){ return i != j; }, priv::Diag_check_type::All);
            bool has_ones = true;

            for(auto iter = mat.begin_diag(); iter != mat.end_diag(); ++iter)
            {
                if(*iter != 1)
                {
                    has_ones = false;
                    break;
                }
            }

            return diagonal && has_ones;
        }

        template<typename M>
        void
        transpose(M& m)
        {
            M mat(m.cols(), m.rows());

            for(std::size_t i = 0; i < m.cols(); ++i)
            {
                for(std::size_t j = 0; j < m.rows(); ++j)
                    mat(i, j) = m(j, i);
            }

            m = std::move(mat);
        }

        template<typename M>
        std::size_t zeros(M mat)
        {
            using value_type = typename M::value_type;
            std::size_t count = 0;

            for(auto x : mat)
            {
                if(x == value_type{})
                {
                    count++;
                }
            }

            return count;
        }

    } // namespace algo

} // namespace axi

#endif // ALGORITHMS_HPP
