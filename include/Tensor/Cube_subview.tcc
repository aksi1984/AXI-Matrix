#ifndef CUBE_SUBVIEW_TCC
#define CUBE_SUBVIEW_TCC

#include "Cube_subview.hpp"

namespace linalg
{

    template<typename CubeType, typename L>
    Cube_subview<CubeType, L>::Cube_subview() :
        base(allocator_type{}) { }

    template<typename CubeType, typename L>
    Cube_subview<CubeType, L>::Cube_subview(const CubeType& cube, size_type n) :
        base(cube.slices(), Matrix<value_type>{}, allocator_type{}),
        elems_{n}
    {
        for(size_type i = 0; i < base::slices(); ++i)
        {
            auto matrix = layout_type::get(cube[i], n, n + 1);
            base::operator[](i) = matrix;
        }
    }

    template<typename CubeType, typename L>
    Cube_subview<CubeType, L>::Cube_subview(const CubeType& cube, size_type first, size_type last) :
        base(cube.slices(), allocator_type{}),
        elems_{std::pair{first, last}}
    {
        for(size_type i = 0; i < base::slices(); ++i)
        {
            auto matrix = layout_type::get(cube[i], first, last);
            base::operator[](i) = matrix;
        }
    }

    template<typename CubeType, typename L>
    Cube_subview<CubeType, L>::Cube_subview(const CubeType& cube, std::initializer_list<size_type> indices) :
        base(cube.slices(), allocator_type{}),
        elems_{indices}
    {
        for(size_type i = 0; i < base::slices(); ++i)
        {
            auto matrix = layout_type::get(cube[i], indices);
            base::operator[](i) = matrix;
        }
    }

    template<typename CubeType, typename L>
    void
    Cube_subview<CubeType, L>::fill(value_type value)
    {
        auto elems = elems_
        layout_type
    }

    template<typename CubeType, typename L>
    void
    Cube_subview<CubeType, L>::update(CubeType& cube)
    {

    }

} // namespace linalg

#endif // CUBE_SUBVIEW_TCC
