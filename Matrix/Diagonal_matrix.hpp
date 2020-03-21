#ifndef DIAGONAL_MATRIX_HPP
#define DIAGONAL_MATRIX_HPP

#include "Base.hpp"
#include "Triangular_param.hpp"

namespace linarg
{
    template<typename T>
    class Diagonal_matrix : Base<Diagonal_tag, T, Array<T>>
    {
        using base            = Base<Diagonal_tag, T, Array<T>>;
        using self_type       = Diagonal_matrix<T>;
        using matrix_type     = typename base::matrix_type;
        using value_type      = typename base::value_type;
        using reference       = typename base::reference;
        using const_reference = typename base::const_reference;
        using pointer         = typename base::pointer;
        using const_pointer   = typename base::const_pointer;
        using size_type       = typename base::size_type;
        using allocator_type  = typename base::allocator_type;

        Diagonal_matrix(const allocator_type& alloc = allocator_type());
    };

}

#endif // DIAGONAL_MATRIX_HPP
