#ifndef SUBCUBE_ELEMS_FILL_HPP
#define SUBCUBE_ELEMS_FILL_HPP

#include "include/Storage/Arrays.hpp"
#include "include/Matrix/Matrix.hpp"

namespace axi
{
    struct Row
    {

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
        static void fill(MatType& mat, std::size_t first_row, std::size_t last_row, typename MatType::value_type value)
        {
            for(std::size_t i = first_row; i < last_row; ++i)
            {
                for(auto row_iter = mat.begin_row(i); row_iter != mat.end_row(i); ++row_iter)
                {
                    *row_iter = value;
                }
            }
        }
    };

    struct Col
    {
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
        static void fill(MatType& mat, std::size_t first_col, std::size_t last_col, typename MatType::value_type value)
        {
            for(std::size_t i = first_col; i < last_col; ++i)
            {
                for(auto row_iter = mat.begin_col(i); row_iter != mat.end_col(i); ++row_iter)
                {
                    *row_iter = value;
                }
            }
        }

    };

} // namespace linalg

#endif // SUBCUBE_ELEMS_FILL_HPP
