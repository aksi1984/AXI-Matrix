#ifndef MINOR_INITIALIZER_HPP
#define MINOR_INITIALIZER_HPP

#include "Math.hpp"

namespace linalg
{
    class Minor_initializer
    {
    public:

        Minor_initializer(Matrix_size size, Dimension dim);

        Minor_initializer(Matrix_size size, List<std::size_t> rows, const List<std::size_t> cols);

        Dimension dim() const noexcept;

        Container<std::size_t> n_cols() const noexcept;

        Container<std::size_t> n_rows() const noexcept;

        Matrix_size size() const noexcept;

    private:

        Dimension dim_;
        Matrix_size size_;

        Container<std::size_t> cols_;
        Container<std::size_t> rows_;
    };

} // namespace linarg

#endif // MINOR_INITIALIZER_HPP
