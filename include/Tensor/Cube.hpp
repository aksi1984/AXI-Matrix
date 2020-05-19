#ifndef CUBE_HPP
#define CUBE_HPP

#include "include/Tensor/Tensor.tcc"
#include "include/Matrix/Matrix_size.hpp"
#include "include/Matrix/Cond.hpp"
#include "Cube_subview.hpp"

namespace axi
{
    template<typename Mat>
    class Cube : public Tensor<Mat>
    {
    private:

        using base          = Tensor<Mat>;
        using self_type     = Cube<Mat>;

    public:

        using value_type        = typename base::object_type;
        using mat_value_type    = typename value_type::value_type;
        using size_type         = typename base::size_type;
        using allocator_type    = typename base::allocator_type;

        Cube();

        Cube(const Matrix_size& req_size, size_type slices);

        Cube(size_type rows, size_type cols, size_type slices);

        template<typename U>
        Cube(const Matrix_size& req_size, size_type slices, Random<U> random);

        template<typename U>
        Cube(const Matrix_size& req_size, double density, size_type slices, Random<U> random);

        template<typename U>
        Cube(const Square_matrix_size& req_size, size_type slices, Random<U> random);

        Cube(const Cube& copy);

        template<typename OtherMat>
        Cube(const Cube<OtherMat>& copy) = delete;

        Cube(Cube&& move);

        template<typename OtherMat>
        Cube(Cube<OtherMat>&& move) = delete;

        Cube& operator=(const Cube& rhs);

        template<typename OtherMat>
        Cube& operator=(const Cube<OtherMat>& rhs) = delete;

        Cube& operator=(Cube&& rhs);

        template<typename OtherMat>
        Cube& operator=(Cube<OtherMat>&& rhs) = delete;

        std::vector<mat_value_type> row(size_type row, size_type slice);

    };

} // namespace linalg

#endif // CUBE_HPP
