#ifndef SUBCUBE_ELEMS_FILL_HPP
#define SUBCUBE_ELEMS_FILL_HPP

#include "include/Storage/Arrays.hpp"
#include "include/Matrix/Matrix.hpp"

namespace linalg
{

    struct Row
    {
        template<typename MatType>
        static Matrix<typename MatType::value_type> get(MatType src, std::size_t row)
        {
            using value_type = typename MatType::value_type;

            std::size_t rows = 1;
            std::size_t cols = src.cols();

            Matrix<value_type> dest(rows, cols);

            for(auto src_iter = src.begin_row(row), dest_iter = dest.begin_row(0); src_iter != src.end_row(row); ++src_iter, ++ dest_iter)
            {
                *dest_iter = *src_iter;
            }

            return dest;
        }

        template<typename MatType>
        static Matrix<typename MatType::value_type> get(MatType src, std::size_t first_row, std::size_t last_row)
        {
            using value_type = typename MatType::value_type;

            std::size_t rows = last_row - first_row;
            std::size_t cols = src.cols();

            Matrix<value_type> dest(rows, cols);

            for(std::size_t i = first_row, dest_row_count = 0; i < last_row; ++i, ++dest_row_count)
            {
                for(auto src_iter = src.begin_row(i), dest_iter = dest.begin_row(dest_row_count); src_iter != src.end_row(i); ++src_iter, ++ dest_iter)
                {
                    *dest_iter = *src_iter;
                }
            }

            return dest;
        }

        template<typename MatType>
        static Matrix<typename MatType::value_type> get(MatType src, std::initializer_list<std::size_t> indices)
        {
            using value_type = typename MatType::value_type;

            std::size_t rows = indices.size();
            std::size_t cols = src.cols();

            Matrix<value_type> dest(rows, cols);
            std::size_t dest_row_count = 0;

            for(auto list_iter = indices.begin(); list_iter != indices.end(); ++list_iter, ++dest_row_count)
            {
                for(auto src_iter = src.begin_row(*list_iter), dest_iter = dest.begin_row(dest_row_count); src_iter != src.end_row(*list_iter); ++src_iter, ++ dest_iter)
                {
                    *dest_iter = *src_iter;
                }
            }

            return dest;
        }

        template<typename MatType>
        static void set(MatType src, MatType dest, std::size_t row)
        {
            for(auto src_iter = src.begin_row(row), dest_iter = dest.begin_row(row); src_iter != src.end_row(row); ++src_iter, ++ dest_iter)
            {
                *dest_iter = *src_iter;
            }
        }

        template<typename MatType>
        static void set(MatType src, MatType& dest, std::initializer_list<std::size_t> indices)
        {
            for(auto list_iter = indices.begin(); list_iter != indices.end(); ++list_iter)
            {
                for(auto src_iter = src.begin_row(*list_iter), dest_iter = dest.begin_row(*list_iter); src_iter != src.end_row(*list_iter); ++src_iter, ++ dest_iter)
                {
                    *dest_iter = *src_iter;
                }
            }
        }

        template<typename MatType>
        static void fill(MatType& dest, std::size_t n, typename MatType::value_type value)
        {
            for(auto dest_iter = dest.begin_row(n); dest_iter != dest.end_row(n); ++dest_iter)
            {
                *dest_iter = value;
            }
        }
    };

    struct Col
    {
        template<typename MatType>
        static Matrix<typename MatType::value_type> get(MatType src, std::size_t nth_col)
        {
            using value_type = typename MatType::value_type;

            std::size_t rows = src.rows();
            std::size_t cols = 1;

            Matrix<value_type> dest(rows, cols);

            for(auto src_iter = src.begin_col(nth_col), dest_iter = dest.begin_col(0); src_iter != src.end_col(nth_col); ++src_iter, ++ dest_iter)
            {
                *dest_iter = *src_iter;
            }

            return dest;
        }

        template<typename MatType>
        static Matrix<typename MatType::value_type> get(MatType src, std::size_t first_col, std::size_t last_col)
        {
            using value_type = typename MatType::value_type;

            std::size_t rows = src.rows();
            std::size_t cols = last_col - first_col;

            Matrix<value_type> dest(rows, cols);

            for(std::size_t i = first_col, dest_col_count = 0; i < last_col; ++i, ++dest_col_count)
            {
                for(auto src_iter = src.begin_col(i), dest_iter = dest.begin_col(dest_col_count); src_iter != src.end_col(i); ++src_iter, ++ dest_iter)
                {
                    *dest_iter = *src_iter;
                }
            }

            return dest;
        }

        template<typename MatType>
        static Matrix<typename MatType::value_type> get(MatType src, std::initializer_list<std::size_t> indices)
        {
            using value_type = typename MatType::value_type;

            std::size_t rows = src.rows();
            std::size_t cols = indices.size();

            Matrix<value_type> dest(rows, cols);
            std::size_t dest_col_count = 0;

            for(auto list_iter = indices.begin(); list_iter != indices.end(); ++list_iter, ++dest_col_count)
            {
                for(auto src_iter = src.begin_col(*list_iter), dest_iter = dest.begin_col(dest_col_count); src_iter != src.end_col(*list_iter); ++src_iter, ++ dest_iter)
                {
                    *dest_iter = *src_iter;
                }
            }

            return dest;
        }
    };

} // namespace linalg

#endif // SUBCUBE_ELEMS_FILL_HPP
