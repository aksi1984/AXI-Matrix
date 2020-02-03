#ifndef MINOR_INITIALIZER_TCC
#define MINOR_INITIALIZER_TCC

#include "Minor_initializer.hpp"

namespace linarg
{
    Minor_initializer::Minor_initializer(Matrix_size size, Dimension dim) :
        dim_(dim)
    {
        std::size_t rows = ( dim == Dimension::Row ? size[0] - 1 : size[1] - 1 ) ;
        std::size_t cols = ( dim == Dimension::Row ? size[1] : size[0] );

        LINARG_CHECK( (rows == cols), Not_square() )

        size_ = Matrix_size(rows, cols);
    }

    Minor_initializer::Minor_initializer(Matrix_size size, List<std::size_t> rows, const List<std::size_t> cols)
    {
        std::size_t new_rows = size[0] - rows.size();
        std::size_t new_cols = size[1] - cols.size();

        LINARG_CHECK( (new_rows == new_cols), Not_square() )

        size_ = Matrix_size(new_rows, new_cols);

        cols_.resize(cols.size());
        rows_.resize(rows.size());

        std::copy(cols.begin(), cols.end(), cols_.begin());
        std::copy(rows.begin(), rows.end(), rows_.begin());
    }

    Dimension
    Minor_initializer::dim() const noexcept
    {
        return dim_;
    }

    Container<std::size_t>
    Minor_initializer::n_cols() const noexcept
    {
        return cols_;
    }

    Container<std::size_t>
    Minor_initializer::n_rows() const noexcept
    {
        return rows_;
    }

    Matrix_size
    Minor_initializer::size() const noexcept
    {
        return size_;
    }

} // namespace linarg

#endif // MINOR_INITIALIZER_TCC
