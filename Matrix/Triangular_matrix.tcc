#ifndef SQUARE_MATRIX_TCC
#define SQUARE_MATRIX_TCC

#include "Triangular_matrix.hpp"

namespace linarg
{
    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const allocator_type& alloc) :
        base(alloc) { }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(size_type size, value_type value, const allocator_type& alloc) :
        base(size, size, alloc)
    {

        triangular_fill_type::fill(base::rows(), base::cols(), base::data_, value, std::integral_constant<bool, true>{});
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const Square_size& size, value_type value, const allocator_type& alloc) :
        self_type(size.rows_, value, alloc) { }

    template<typename T, typename Tr>
        template<typename U, typename>
        Triangular_matrix<T, Tr>::Triangular_matrix(size_type req_size, Random<U> random, const allocator_type& alloc) :
            base(req_size, req_size, alloc)
        {
            triangular_fill_type::fill(base::rows(), base::cols(), base::data_, random);
        }

    template<typename T, typename Tr>
        template<typename Function>
        Triangular_matrix<T, Tr>::Triangular_matrix(size_type size, Function function, const allocator_type& alloc) :
            base(size, size, alloc)
        {
            triangular_fill_type::fill(base::rows(), base::cols(), base::data_, function, std::integral_constant<bool, false>{});
        }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const std::vector<T>& vector, const allocator_type& alloc) :
        base(vector.size(), vector.size(), alloc)
    {
        detail::fill(*this, vector);
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const Vector<T>& vector, const allocator_type& alloc) :
        base(vector.size(), vector.size(), alloc)
    {
        detail::fill(*this, vector);
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
        template<typename U>
        Triangular_matrix<T, Tr>&
        Triangular_matrix<T, Tr>::operator=(Random<U> random)
        {
            LINARG_CHECK(std::holds_alternative<size_type>(random.size()), Bad_constructor{})

            if(size_type new_size = std::get<1>(random.size()); (new_size * new_size) != base::size().total())
            {
                Triangular_matrix<T, Tr> temp{new_size, 0};
                *this = temp;
            }

            triangular_fill_type::fill(base::rows(), base::cols(), base::data_, random);

            return *this;
        }

    template<typename T, typename Tr>
    typename Triangular_matrix<T, Tr>::reference
    Triangular_matrix<T, Tr>::operator()(size_type i, size_type j)
    {
        LINARG_CHECK(base::operator()(i, j) != value_type{}, Bad_index(i, j,
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
        LINARG_CHECK(base::operator()(i, j) != value_type{}, Bad_index(i, j,
                     "in triangular matrix this index cannot be changed"))

        return  base::operator()(i, j);
    }

} // namespace linarg

#endif // SQUARE_MATRIX_TCC
