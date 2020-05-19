#ifndef MAT_SIZE_HPP
#define MAT_SIZE_HPP

#include <iostream>

namespace axi
{

    struct Matrix_size
    {
        using size_type = std::size_t;

        Matrix_size();

        Matrix_size(size_type rows, size_type cols);

        std::size_t total() const noexcept;

        size_type operator[](size_type n);

        bool operator>(const Matrix_size& rhs) const noexcept;

        bool operator<(const Matrix_size& rhs) const noexcept;

        bool operator==(const Matrix_size& rhs) const noexcept;

        bool operator!=(const Matrix_size& rhs) const noexcept;

        Matrix_size operator+(const Matrix_size& rhs);

        Matrix_size operator-(const Matrix_size& rhs);

        Matrix_size& operator+=(const Matrix_size& rhs);

        Matrix_size& operator-=(const Matrix_size& rhs);

        Matrix_size& operator+=(const size_type& rhs);

        Matrix_size& operator-=(const size_type& rhs);

        Matrix_size& operator*=(const size_type& rhs);

        Matrix_size& operator/=(const size_type& rhs);

        size_type rows_;
        size_type cols_;
    };

    //////////////////////////////////////////////////////////////////////

    struct Square_matrix_size : public Matrix_size
    {
        Square_matrix_size();

        Square_matrix_size(std::size_t size);
    };

} // namespace Axi

#endif // MAT_SIZE_HPP
