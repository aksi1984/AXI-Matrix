#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include "Unbounded_matrix.hpp"
#include "Random.hpp"

namespace linarg
{
    template<typename T>
    class Sparse_matrix : public Unbounded_matrix<Sparse_tag, T>
    {
        static_assert (std::is_arithmetic<T>::value, "Uncorrect type");

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

        explicit Sparse_matrix(rd::Rd_ptr<T> random, double dens, const allocator_type& alloc = allocator_type());

    private:

        virtual void fill_random(rd::Rd_ptr<T> random, std::false_type) override;

        double density_;
        size_type zeros_;
        size_type non_zeros_;
    };

} // namespace linarg

#endif // SPARSE_MATRIX_HPP
