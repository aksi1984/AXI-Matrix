#ifndef DIAGONAL_MATRIX_HPP
#define DIAGONAL_MATRIX_HPP

#include "Base.hpp"
#include "Triangular_param.hpp"

namespace linarg
{
    template<typename T, typename Tr>
    class Triangular_matrix : public Base<Triangular_tag, T, Array<T>>
    {
    private:

        using self_type         = Triangular_matrix<T, Tr>;
        using triangular_type   = Tr;

    public:

        using base            = Base<Triangular_tag, T, Array<T>>;
        using matrix_type     = typename base::matrix_type;
        using value_type      = typename base::value_type;
        using reference       = typename base::reference;
        using const_reference = typename base::const_reference;
        using pointer         = typename base::pointer;
        using const_pointer   = typename base::const_pointer;
        using size_type       = typename base::size_type;
        using allocator_type  = typename base::allocator_type;

        explicit Triangular_matrix(const allocator_type& alloc = allocator_type());

        explicit Triangular_matrix(size_type size, const allocator_type& alloc = allocator_type());

        explicit Triangular_matrix(const Square_size& size, const allocator_type& alloc = allocator_type());

        explicit Triangular_matrix(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, const allocator_type& alloc = allocator_type());

        explicit Triangular_matrix(size_type size, std::function<T> func, const allocator_type& alloc = allocator_type());

        Triangular_matrix& operator=(const Triangular_matrix& rhs);

        Triangular_matrix& operator=(Triangular_matrix&& rhs);

        Triangular_matrix& operator=(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random);

        Triangular_matrix& operator=(const std::vector<T>& rhs);

        Triangular_matrix& operator=(const Vector<T>& rhs);
    };

} // namespace linarg

#endif // DIAGONAL_MATRIX_HPP
