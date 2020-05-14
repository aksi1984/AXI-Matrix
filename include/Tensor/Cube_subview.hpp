#ifndef CUBE_SUBVIEW_HPP
#define CUBE_SUBVIEW_HPP

#include "Cube.hpp"
#include "Cube_subview_elems_fill.hpp"
#include "include/Common/Visitor.hpp"

namespace linalg
{
    template<typename M>
    struct Matrix_value_type
    {
        using type = typename M::value_type;
    };

    ////////////////////////////////////////

    template<typename CubeType, typename FT>
    class Cube_subview : public Tensor<Matrix<typename Matrix_value_type<typename CubeType::value_type>::type>>
    {
    private:

        using base              = Tensor<Matrix<typename Matrix_value_type<typename CubeType::value_type>::type>>;

    public:

        using object_type       = typename CubeType::object_type;
        using value_type        = typename object_type::value_type;
        using fill_type         = FT;
        using size_type         = std::size_t;
        using allocator_type    = typename base::allocator_type;

        Cube_subview();

        Cube_subview(CubeType* cube_ptr, size_type elem);

        Cube_subview(CubeType* cube_ptr, size_type elem_first, size_type elem_last);

        void fill(value_type value);


    private:

        void set_slices(CubeType cube, size_type elem_first, size_type elem_last);

        void set_slices(CubeType cube, std::initializer_list<size_type> elems);

        size_type slices_;

        std::variant<size_type, std::pair<size_type, size_type>> elems_;

        CubeType* cube_ptr_;

    };

} // namespace linalg

#endif // CUBE_SUBVIEW_HPP
