#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include "Unbounded_matrix.hpp"
#include "Random.hpp"

namespace linalg
{
    template<typename T>
    class Sparse_matrix : public Unbounded_matrix<Sparse_tag, T>
    {
        static_assert (std::is_arithmetic<T>::value || is_complex<T>::value, "Uncorrect type");

    public:

        using base              = Unbounded_matrix<Sparse_tag, T>;
        using matrix_type       =  typename base::matrix_type;

        using value_type        = typename base::value_type;
        using reference         = typename base::reference;
        using const_reference   = typename base::const_reference;
        using pointer           = typename base::pointer;
        using const_pointer     = typename base::const_pointer;
        using size_type         = typename base::size_type;
        using allocator_type    = typename base::allocator_type;

        explicit Sparse_matrix(const allocator_type& alloc = allocator_type());

        explicit Sparse_matrix(size_type cols, size_type rows, const allocator_type& alloc = allocator_type());

        explicit Sparse_matrix(const Matrix_size& size, const allocator_type& alloc = allocator_type());

        template<typename U, typename = std::enable_if_t<std::is_same_v<U, typename traits::Get_type<is_complex<T>::value, T>::type>>>
        explicit Sparse_matrix(size_type req_rows, size_type req_cols, double density, Random<U> random, const allocator_type& alloc = allocator_type());

        template<typename U, typename = std::enable_if_t<std::is_same_v<U, typename traits::Get_type<is_complex<T>::value, T>::type>>>
        explicit Sparse_matrix(const Matrix_size& req_size, double density, Random<U> random, const allocator_type& alloc = allocator_type());

        Sparse_matrix(const Sparse_matrix& copy);

        Sparse_matrix(Sparse_matrix&& move);

        Sparse_matrix& operator=(const Sparse_matrix& rhs);

        Sparse_matrix& operator=(Sparse_matrix&& rhs);

        template<typename U, typename = std::enable_if_t<std::is_same_v<U, typename traits::Get_type<is_complex<T>::value, T>::type>>>
        Sparse_matrix& operator=(Random<U> rhs);

    private:

        size_type zeros_;
        size_type non_zeros_;
    };

} // namespace linarg

#endif // SPARSE_MATRIX_HPP
