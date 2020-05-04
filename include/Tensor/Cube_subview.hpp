#ifndef CUBE_SUBVIEW_HPP
#define CUBE_SUBVIEW_HPP

#include "Cube.hpp"
#include "Cube_subview_elems_fill.hpp"

namespace linalg
{
    template<typename M>
    struct Matrix_value_type
    {
        using type = typename M::value_type;
    };

    ////////////////////////////////////////

    template<typename CubeType, typename L>
    class Cube_subview : public Tensor<Matrix<typename Matrix_value_type<typename CubeType::value_type>::type>>
    {
    private:

        using base              = Tensor<Matrix<typename Matrix_value_type<typename CubeType::value_type>::type>>;

    public:

        using matrix_type       = typename CubeType::value_type;
        using value_type        = typename matrix_type::value_type;
        using layout_type       = L;
        using size_type         = std::size_t;
        using allocator_type    = typename base::allocator_type;

        Cube_subview();

        Cube_subview(const CubeType& cube, size_type n);

        Cube_subview(const CubeType& cube, size_type first, size_type last);

        Cube_subview(const CubeType& cube, std::initializer_list<size_type> indices);

        void fill(value_type value);

        void update(CubeType& cube);

    private:

        size_type slices_;

        std::variant<size_type, std::pair<size_type, size_type>, std::initializer_list<size_type>> elems_;

    };

} // namespace linalg

#endif // CUBE_SUBVIEW_HPP
