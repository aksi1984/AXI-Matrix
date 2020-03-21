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
        triangular_type::fill(base::rows(), base::cols(), base::data_, random);
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(size_type size, std::function<T> func, const allocator_type& alloc) :
        base(size, size, alloc)
    {
        triangular_type::fill(base::rows(), base::cols(), base::data_, func);
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const Triangular_matrix<T, Tr>& copy) :
        base(copy) { }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(Triangular_matrix<T, Tr>&& move) :
        base(std::move(move)) { }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>&
    Triangular_matrix<T, Tr>::operator=(const Triangular_matrix<T, Tr>& rhs)
    {
        base::operator=(rhs);

        return *this;
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>&
    Triangular_matrix<T, Tr>::operator=(Triangular_matrix<T, Tr>&& rhs)
    {
        base::operator=(std::move(rhs));

        return *this;
    }

    template<typename T, typename Tr>
    typename Triangular_matrix<T, Tr>::reference
    Triangular_matrix<T, Tr>::operator()(size_type i, size_type j)
    {
        LINARG_CHECK(base::operator()(i, j) != 0, Bad_index(i, j,
                     "in triangular matrix this index cannot be changed"))

        return  base::operator()(i, j);
    }

    template<typename T, typename Tr>
    typename Triangular_matrix<T, Tr>::const_reference
    Triangular_matrix<T, Tr>::operator()(size_type i, size_type j) const
    {
        return  base::operator()(i, j);
    }

    template<typename T, typename Tr>
    typename Triangular_matrix<T, Tr>::reference
    Triangular_matrix<T, Tr>::at(size_type i, size_type j)
    {
        LINARG_CHECK(base::operator()(i, j) != 0, Bad_index(i, j,
                     "in triangular matrix this index cannot be changed"))

        return  base::operator()(i, j);
    }

} // namespace linarg

#endif // SQUARE_MATRIX_TCC
