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

        triangular_fill_type::fill(base::rows(), base::cols(), base::data_, 1, std::integral_constant<bool, false>{});
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const Square_size& size, const allocator_type& alloc) :
        self_type(size.rows_, alloc) { }

    template<typename T, typename Tr>
        template<typename U>
        Triangular_matrix<T, Tr>::Triangular_matrix(size_type req_size, Random<U> random, const allocator_type& alloc) :
            base(req_size, req_size, alloc)
        {
            triangular_fill_type::fill(base::rows(), base::cols(), base::data_, random, std::integral_constant<bool, false>{});
        }

    /*template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(Random_ptr<typename traits::Get_type<is_complex<T>::value, T>::type> random, const allocator_type& alloc) :
        base(random->mat_size(), alloc)
    {
        //triangular_fill_type::fill(base::rows(), base::cols(), base::data_, random, std::integral_constant<bool, false>{});
    }*/

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(size_type size, std::function<T> func, const allocator_type& alloc) :
        base(size, size, alloc)
    {
        triangular_fill_type::fill(base::rows(), base::cols(), base::data_, func, std::integral_constant<bool, false>{});
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const Vector<T>& vector, const allocator_type& alloc) :
        base(vector.size(), vector.size(), alloc)
    {
        static_assert (std::is_same_v<Tr, Diagonal>, "For this contructor the matrix must be diagonal.");

        triangular_fill_type::fill(base::rows(), base::cols(), base::data_, vector, std::integral_constant<bool, true>{});
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
