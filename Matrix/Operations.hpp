#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "Matrix_size.hpp"
#include "Traits.hpp"
#include "Exception.hpp"

#include <iostream>
#include <functional>

namespace linalg
{
    namespace op
    {
        struct Op_vector { };
        struct Op_matrix { };

        template<typename L, typename R>
        struct Binary_function
        {
            using lhs_type      = L;
            using rhs_type      = R;
            using result_type   = L;
        };

        template<typename L, typename R, typename OpType = Op_matrix>
        struct Plus : public Binary_function<L, R>
        {
            using base          = Binary_function<L, R>;
            using lhs_type      = typename base::lhs_type;
            using rhs_type      = typename base::rhs_type;
            using result_type   = typename base::result_type;

            result_type operator()(lhs_type lhs, rhs_type rhs)
            {
                LINARG_CHECK(lhs.size() == rhs.size(), Incompatible_size("Plus", lhs.rows(), lhs.cols(),
                                                                         rhs.rows(), rhs.cols()))

                result_type result(lhs.rows(), lhs.cols());

                auto result_iter = result.begin();
                auto lhs_iter = lhs.begin();
                auto rhs_iter = rhs.begin();

                while(lhs_iter < lhs.end())
                {
                    *result_iter = *lhs_iter + *rhs_iter;

                    lhs_iter++;
                    rhs_iter++;
                    result_iter++;
                }

                return result;
            }
        };

        template<typename L, typename R>
        struct Plus<L, R, Op_vector> : public Binary_function<L, R>
        {
            using base          = Binary_function<L, R>;
            using lhs_type      = typename base::lhs_type;
            using rhs_type      = typename base::rhs_type;
            using result_type   = typename base::result_type;

            result_type operator()(lhs_type lhs, rhs_type rhs)
            {
                LINARG_CHECK(lhs.size() == rhs.size(), Incompatible_size("Plus", lhs.size(), rhs.size()))

                result_type result(lhs.size());

                for(std::size_t i = 0; i < lhs.size(); ++i)
                {
                    result[i] = lhs[i] + rhs[i];
                }

                return result;
            }
        };

        template<typename L, typename R, typename OpType = Op_matrix>
        struct Minus : public Binary_function<L, R>
        {
            using base          = Binary_function<L, R>;
            using lhs_type      = typename base::lhs_type;
            using rhs_type      = typename base::rhs_type;
            using result_type   = typename base::result_type;

            result_type operator()(lhs_type lhs, rhs_type rhs)
            {
                LINARG_CHECK(lhs.size() == rhs.size(), Incompatible_size("Plus", lhs.rows(), lhs.cols(),
                                                                         rhs.rows(), rhs.cols()))

                result_type result(lhs.rows(), lhs.cols());

                auto result_iter = result.begin();
                auto lhs_iter = lhs.begin();
                auto rhs_iter = rhs.begin();

                while(lhs_iter < lhs.end())
                {
                    *result_iter = *lhs_iter - *rhs_iter;

                    lhs_iter++;
                    rhs_iter++;
                    result_iter++;
                }

                return result;
            }
        };

        template<typename L, typename R>
        struct Minus<L, R, Op_vector> : public Binary_function<L, R>
        {
            using base          = Binary_function<L, R>;
            using lhs_type      = typename base::lhs_type;
            using rhs_type      = typename base::rhs_type;
            using result_type   = typename base::result_type;

            result_type operator()(lhs_type lhs, rhs_type rhs)
            {
                LINARG_CHECK(lhs.size() == rhs.size(), Incompatible_size("Plus", lhs.size(), rhs.size()))

                result_type result(lhs.size());

                for(std::size_t i = 0; i < lhs.size(); ++i)
                {
                    result[i] = lhs[i] - rhs[i];
                }

                return result;
            }
        };

        template<typename L, typename R, typename OpType = Op_matrix>
        struct Multiplies : public Binary_function<L, R>
        {
            using base          = Binary_function<L, R>;
            using lhs_type      = typename base::lhs_type;
            using rhs_type      = typename base::rhs_type;
            using result_type   = typename base::result_type;

            result_type operator()(lhs_type lhs, rhs_type rhs)
            {
                LINARG_CHECK( (lhs.rows() == rhs.cols()) && (lhs.cols() == rhs.rows()), Incompatible_size() )

                result_type result(lhs.rows(), rhs.cols());

                for(std::size_t i = 0; i < lhs.rows(); ++i)
                {
                    for(std::size_t j = 0; j < lhs.cols(); ++j)
                    {
                        using value_type = typename result_type::value_type;
                        value_type subtotal = 0;

                        for(std::size_t k = 0; k < lhs.cols(); ++k)
                        {
                            subtotal += lhs(i, k) * rhs(k, j);
                        }

                        result(i, j) = subtotal;
                    }
                }

                return result;
            }
        };

        template<typename L, typename R>
        struct Multiplies<L, R, Op_vector> : public Binary_function<L, R>
        {
            using base          = Binary_function<L, R>;
            using lhs_type      = typename base::lhs_type;
            using rhs_type      = typename base::rhs_type;
            using result_type   = typename base::result_type;
            using value_type    = typename result_type::value_type;

            result_type operator()(lhs_type lhs, rhs_type rhs)
            {
                LINARG_CHECK( lhs.size() == rhs.size(), Incompatible_size(lhs.size(), rhs.size()) )

                result_type result(lhs.size());

                auto lhs_iter = lhs.begin();
                auto rhs_iter = rhs.begin();
                auto result_iter = result.begin();

                while(lhs_iter < lhs.end())
                {
                    *result_iter = *lhs_iter * *rhs_iter;

                    lhs_iter++;
                    rhs_iter++;
                    result_iter++;
                }

                return result;
            }
        };


        template<typename L, typename R, typename OpType = Op_matrix>
        struct Scalar_multiplies : public Binary_function<L, R>
        {
            using base          = Binary_function<L, R>;
            using lhs_type      = typename base::lhs_type;
            using rhs_type      = typename base::rhs_type;
            using result_type   = typename base::result_type;

            result_type operator()(lhs_type lhs, rhs_type scalar)
            {
                result_type result(lhs.rows(), lhs.cols());

                auto result_iter = result.begin();
                auto lhs_iter = lhs.begin();

                while(lhs_iter < lhs.end())
                {
                    *result_iter = *lhs_iter * scalar;

                    lhs_iter++;
                    result_iter++;
                }

                return result;
            }
        };

        template<typename L, typename R>
        struct Scalar_multiplies<L, R, Op_vector> : public Binary_function<L, R>
        {
            using base          = Binary_function<L, R>;
            using lhs_type      = typename base::lhs_type;
            using rhs_type      = typename base::rhs_type;
            using result_type   = typename base::result_type;

            result_type operator()(lhs_type lhs, rhs_type scalar)
            {
                result_type result(lhs.size());

                auto result_iter = result.begin();
                auto lhs_iter = lhs.begin();

                while(lhs_iter < lhs.end())
                {
                    *result_iter = *lhs_iter * scalar;

                    lhs_iter++;
                    result_iter++;
                }

                return result;
            }
        };

        template<typename L, typename R, typename OpType = Op_matrix>
        struct Scalar_divide : public Binary_function<L, R>
        {
            using base          = Binary_function<L, R>;
            using lhs_type      = typename base::lhs_type;
            using rhs_type      = typename base::rhs_type;
            using result_type   = typename base::result_type;

            result_type operator()(lhs_type lhs, rhs_type scalar)
            {
                //LINARG_CHECK( scalar != 0, Divide_by_zero("Scalar divide") )

                result_type result(lhs.rows(), lhs.cols());

                auto result_iter = result.begin();
                auto lhs_iter = lhs.begin();

                while(lhs_iter < lhs.end())
                {
                    *result_iter = *lhs_iter / scalar;

                    lhs_iter++;
                    result_iter++;
                }

                return result;
            }
        };


        template<typename L, typename R>
        struct Scalar_divide<L, R, Op_vector> : public Binary_function<L, R>
        {
            using base          = Binary_function<L, R>;
            using lhs_type      = typename base::lhs_type;
            using rhs_type      = typename base::rhs_type;
            using result_type   = typename base::result_type;

            result_type operator()(lhs_type lhs, rhs_type scalar)
            {
                LINARG_CHECK( scalar != 0, Divide_by_zero("Scalar divide") )

                result_type result(lhs.size());

                auto result_iter = result.begin();
                auto lhs_iter = lhs.begin();

                while(lhs_iter < lhs.end())
                {
                    *result_iter = *lhs_iter / scalar;

                    lhs_iter++;
                    result_iter++;
                }

                return result;
            }
        };

        template<typename L, typename R, typename OpType = Op_matrix>
        struct Equal
        {
            using value_type    = typename L::value_type;
            using lhs_type      = L;
            using rhs_type      = R;

            bool operator()(lhs_type lhs, rhs_type rhs)
            {
                if(lhs.size() != rhs.size())
                {
                    return false;
                }

                auto lhs_iter = lhs.begin();
                auto rhs_iter = rhs.begin();

                while(lhs_iter < lhs.end())
                {
                    if( !std::equal_to<value_type>()(*lhs_iter, *rhs_iter) )
                    {
                        return false;
                    }

                    lhs_iter++;
                    rhs_iter++;
                }

                return true;
            }
        };

        template<typename L, typename R>
        struct Equal<L, R, Op_vector>
        {
            using value_type    = typename L::value_type;
            using lhs_type      = L;
            using rhs_type      = R;

            bool operator()(lhs_type lhs, rhs_type rhs)
            {
                LINARG_CHECK( lhs.size() == rhs.size(), Incompatible_size(lhs.size(), rhs.size()) )

                auto lhs_iter = lhs.begin();
                auto rhs_iter = rhs.begin();

                while(lhs_iter < lhs.end())
                {
                    if( !std::equal_to<value_type>()(*lhs_iter, *rhs_iter) )
                    {
                        return false;
                    }

                    lhs_iter++;
                    rhs_iter++;
                }

                return true;
            }
        };

    } // namespace op

} // namespace axi

#endif // OPERATIONS_HPP
