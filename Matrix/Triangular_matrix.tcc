#ifndef SQUARE_MATRIX_TCC
#define SQUARE_MATRIX_TCC

#include "Triangular_matrix.hpp"

namespace linarg
{
    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const allocator_type& alloc) :
        base(alloc) { }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(size_type size, const allocator_type& alloc) :
        base(size, size, alloc)
    {
        triangular_type::fill(base::rows(), base::cols(), *this, 1);
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const Square_size& size, const allocator_type& alloc) :
        self_type(size.rows_, alloc) { }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, const allocator_type& alloc) :
        base(random->mat_size(), alloc)
    {
        triangular_type::fill(*this, random);
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(size_type size, std::function<T> func, const allocator_type& alloc) :
        base(size, size, alloc)
    {

    }

} // namespace linarg

#endif // SQUARE_MATRIX_TCC
