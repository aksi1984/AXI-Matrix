#ifndef CUBE_SUBVIEW_TCC
#define CUBE_SUBVIEW_TCC

#include "Cube_subview.hpp"

namespace linalg
{

    template<typename CubeType, typename L>
    Cube_subview<CubeType, L>::Cube_subview() :
        base(allocator_type{}) { }

    template<typename CubeType, typename L>
    Cube_subview<CubeType, L>::Cube_subview(CubeType* cube_ptr, size_type elem) :
        base(cube_ptr->slices(), Matrix<value_type>{}, allocator_type{}),
        elems_{elem},
        cube_ptr_{cube_ptr}
    {
        set_slices(*cube_ptr, elem, elem + 1);
    }

    template<typename CubeType, typename L>
    Cube_subview<CubeType, L>::Cube_subview(CubeType* cube_ptr, size_type elem_first, size_type elem_last) :
        base(cube_ptr->slices(), allocator_type{}),
        elems_{std::pair{elem_first, elem_last}},
        cube_ptr_{cube_ptr}
    {
        set_slices(*cube_ptr_, elem_first, elem_last);
    }

    template<typename CubeType, typename L>
    void
    Cube_subview<CubeType, L>::fill(value_type value)
    {
        auto ranges = std::visit(visitor::Cube_subview_elements_visitor{}, elems_);

        for(size_type i = 0; i < base::slices(); ++i)
        {
            layout_type::fill(cube_ptr_->operator[](i), ranges.first, ranges.second, value);
            layout_type::fill(base::operator[](i), ranges.first, ranges.second, value);
        }
    }

    //

    template<typename CubeType, typename L>
    void
    Cube_subview<CubeType, L>::set_slices(CubeType cube, size_type elem_first, size_type elem_last)
    {
        for(size_type i = 0; i < base::slices(); ++i)
        {
            auto matrix = layout_type::get(cube[i], elem_first, elem_last);
            base::operator[](i) = matrix;
        }
    }


    template<typename CubeType, typename L>
    void
    Cube_subview<CubeType, L>::set_slices(CubeType cube, std::initializer_list<size_type> elems)
    {
        for(size_type i = 0; i < base::slices(); ++i)
        {
            auto matrix = layout_type::get(cube[i], elems);
            base::operator[](i) = matrix;
        }
    }


} // namespace linalg

#endif // CUBE_SUBVIEW_TCC
