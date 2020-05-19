#ifndef SQUARE_MATRIX_TCC
#define SQUARE_MATRIX_TCC

#include "Triangular_matrix.hpp"

namespace axi
{
    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const allocator_type& alloc) :
        base(alloc),
        initialized_{false} { }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const Square_matrix_size& req_size, value_type value, const allocator_type& alloc) :
        base(req_size.rows_, req_size.cols_, alloc)
    {
        triangular_fill_type::fill(base::rows(), base::cols(), base::data_, value, std::integral_constant<bool, true>{});
        initialized_ = true;
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(size_type size, value_type value, const allocator_type& alloc) :
        self_type(Square_matrix_size{size}, value, alloc) { }

    template<typename T, typename Tr>
        template<typename U, typename>
        Triangular_matrix<T, Tr>::Triangular_matrix(const Square_matrix_size& req_size, Random<U> random, const allocator_type& alloc) :
            base(req_size.rows_, req_size.cols_, alloc)
        {
            triangular_fill_type::fill(base::rows(), base::cols(), base::data_, random);
            initialized_ = true;
        }

    template<typename T, typename Tr>
        template<typename U, typename>
        Triangular_matrix<T, Tr>::Triangular_matrix(size_type req_size, Random<U> random, const allocator_type& alloc) :
            self_type(Square_matrix_size{req_size}, random, alloc) { }

    template<typename T, typename Tr>
        template<typename Function, typename>
        Triangular_matrix<T, Tr>::Triangular_matrix(size_type size, Function function, const allocator_type& alloc) :
            base(size, size, alloc)
        {
            triangular_fill_type::fill(base::rows(), base::cols(), base::data_, function, std::integral_constant<bool, false>{});
            initialized_ = true;
        }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const std::vector<value_type>& vector, const allocator_type& alloc) :
        base(vector.size(), vector.size(), alloc)
    {
        detail::fill(*this, vector);
        initialized_ = true;
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const Vector<value_type>& vector, const allocator_type& alloc) :
        base(vector.size(), vector.size(), alloc)
    {
        detail::fill(*this, vector);
        initialized_ = true;
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(const Triangular_matrix<T, Tr>& copy) :
        base(copy),
        initialized_{true} { }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>::Triangular_matrix(Triangular_matrix<T, Tr>&& move) :
        base(std::move(move)),
        initialized_{true} { }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>&
    Triangular_matrix<T, Tr>::operator=(const Triangular_matrix<T, Tr>& rhs)
    {
        base::operator=(rhs);
        initialized_ = true;

        return *this;
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>&
    Triangular_matrix<T, Tr>::operator=(Triangular_matrix<T, Tr>&& rhs)
    {
        base::operator=(std::move(rhs));
        initialized_ = true;

        return *this;
    }

    template<typename T, typename Tr>
        template<typename U, typename>
        Triangular_matrix<T, Tr>&
        Triangular_matrix<T, Tr>::operator=(Random<U> random)
        {
            LINALG_CHECK(std::holds_alternative<Square_matrix_size>(random.size()), Bad_constructor{})

            if(Square_matrix_size new_size = std::get<1>(random.size()); new_size.total() != base::size().total())
            {
                Triangular_matrix<T, Tr> temp{new_size, 0};
                *this = temp;
            }

            triangular_fill_type::fill(base::rows(), base::cols(), base::data_, random);
            initialized_ = true;

            return *this;
        }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>&
    Triangular_matrix<T, Tr>::operator=(const std::vector<value_type>& rhs)
    {
        resize(rhs);
        detail::fill(*this, rhs);
        initialized_ = true;

        return *this;
    }

    template<typename T, typename Tr>
    Triangular_matrix<T, Tr>&
    Triangular_matrix<T, Tr>::operator=(const Vector<value_type>& rhs)
    {
        resize(rhs);
        detail::fill(*this, rhs);
        initialized_ = true;

        return *this;
    }

    template<typename T, typename Tr>
    typename Triangular_matrix<T, Tr>::reference
    Triangular_matrix<T, Tr>::operator()(size_type i, size_type j)
    {
        using compare = typename detail::Compare<triangular_fill_type::compare_number, value_type>::type;
        compare comp;

        LINALG_CHECK(!comp(i, j) && initialized_ == true, Bad_index(i, j, "Attempt to change zero index in triangular matrix."))

        return  base::operator()(i, j);
    }

    template<typename T, typename Tr>
    typename Triangular_matrix<T, Tr>::const_reference
    Triangular_matrix<T, Tr>::operator()(size_type i, size_type j) const
    {
        return base::operator()(i, j);
    }

    template<typename T, typename Tr>
    typename Triangular_matrix<T, Tr>::reference
    Triangular_matrix<T, Tr>::at(size_type i, size_type j)
    {
        using compare = typename detail::Compare<triangular_fill_type::compare_number, value_type>::type;
        compare comp;

        LINALG_CHECK(!comp(i, j) && initialized_ == true, Bad_index(i, j, "Attempt to change zero index in triangular matrix."))

        return  base::operator()(i, j);
    }

    template<typename T, typename Tr>
        template<typename VectorType>
        VectorType Triangular_matrix<T, Tr>::non_zeros()
        {
            VectorType vector;
            triangular_fill_type::non_zeros(base::data_, base::rows(), base::cols(), vector);

            return vector;
        }

    template<typename T, typename Tr>
    template<typename Container>
    void
    Triangular_matrix<T, Tr>::resize(Container container)
    {
        if(size_type new_size = container.size(); (new_size * new_size) != base::size().total())
        {
            Triangular_matrix temp{new_size, 0};
            *this = temp;
        }
    }

} // namespace linarg

#endif // SQUARE_MATRIX_TCC
