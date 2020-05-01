#ifndef CUBE_HPP
#define CUBE_HPP

#include "Tensor_base.tcc"
#include "Matrix/Matrix_size.hpp"
#include "Matrix/Cond.hpp"

namespace linalg
{
template<typename Mat>
class Cube : public Tensor_base<Mat>
{
private:

    using base          = Tensor_base<Mat>;
    using self_type     = Cube<Mat>;

public:

    using value_type        = typename base::object_type;
    using mat_value_type    = typename value_type::value_type;
    using size_type         = typename base::size_type;
    using allocator_type    = typename base::allocator_type;

    explicit Cube(const allocator_type& alloc = allocator_type{});

    explicit Cube(const Matrix_size& req_size, size_type slices, const allocator_type& alloc = allocator_type{});

    explicit Cube(size_type rows, size_type cols, size_type slices, const allocator_type& alloc = allocator_type{});

    template<typename U>
    explicit Cube(const Matrix_size& req_size, size_type slices, Random<U> random, const allocator_type& alloc = allocator_type{});

    template<typename U>
    explicit Cube(const Matrix_size& req_size, double density, size_type slices, Random<U> random, const allocator_type& alloc = allocator_type{});

    template<typename U>
    explicit Cube(const Square_matrix_size& req_size, size_type slices, Random<U> random, const allocator_type& alloc = allocator_type{});

    std::vector<mat_value_type> row(size_type row, size_type slice);

};

} // namespace linalg

#endif // CUBE_HPP
