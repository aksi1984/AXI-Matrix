#ifndef MATRIX_SIZE_TCC
#define MATRIX_SIZE_TCC

#include "Matrix_size.hpp"

namespace axi
{
    Matrix_size::Matrix_size() :
        rows_{},
        cols_{} { }

    Matrix_size::Matrix_size(size_type rows, size_type cols) :
        rows_{rows},
        cols_{cols} { }

    std::size_t
    Matrix_size::total() const noexcept
    {
        return (rows_ * cols_);
    }

    typename Matrix_size::size_type
    Matrix_size::operator[](size_type n)
    {
        return (n == 0 ? rows_ : cols_);
    }

    bool
    Matrix_size::operator>(const Matrix_size& rhs) const noexcept
    {
        return (rows_ > rhs.rows_) || (cols_ > rhs.cols_);
    }

    bool
    Matrix_size::operator<(const Matrix_size& rhs) const noexcept
    {
        return (rows_ < rhs.rows_) || (cols_ < rhs.cols_);
    }

    bool
    Matrix_size::operator==(const Matrix_size& rhs) const noexcept
    {
        return (rows_ == rhs.rows_) && (cols_ == rhs.cols_);
    }

    bool
    Matrix_size::operator!=(const Matrix_size& rhs) const noexcept
    {
        return !(this->operator==(rhs));
    }

    Matrix_size&
    Matrix_size::operator+=(const Matrix_size& rhs)
    {
        cols_ += rhs.cols_;
        rows_ += rhs.rows_;

        return *this;
    }

    Matrix_size&
    Matrix_size::operator-=(const Matrix_size& rhs)
    {
        cols_ -= rhs.cols_;
        rows_ -= rhs.rows_;

        return *this;
    }

    Matrix_size&
    Matrix_size::operator+=(const size_type& rhs)
    {
        cols_ += rhs;
        rows_ += rhs;

        return *this;
    }

    Matrix_size&
    Matrix_size::operator-=(const size_type& rhs)
    {
        cols_ -= rhs;
        rows_ -= rhs;

        return *this;
    }

    Matrix_size&
    Matrix_size::operator*=(const size_type& rhs)
    {
        cols_ *= rhs;
        rows_ *= rhs;

        return *this;
    }

    Matrix_size&
    Matrix_size::operator/=(const size_type& rhs)
    {
        cols_ /= rhs;
        rows_ /= rhs;

        return *this;
    }

    ////////////////////////////////////////////////////////

    Square_matrix_size::Square_matrix_size() { }

    Square_matrix_size::Square_matrix_size(std::size_t size) :
        Matrix_size(size, size) { }

} // namespace linarg

#endif // MATRIX_SIZE_TCC
