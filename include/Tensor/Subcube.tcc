#ifndef CUBE_SUBVIEW_TCC
#define CUBE_SUBVIEW_TCC

#include "Subcube.hpp"

namespace axi
{

    template<typename CubeType, typename FT>
    Subcube<CubeType, FT>::Subcube() :
        base(allocator_type{}) { }

    template<typename CubeType, typename FT>
    Subcube<CubeType, FT>::Subcube(CubeType& cube_, size_type elem) :
        base(cube_.slices(), Matrix<value_type>{}, allocator_type{}),
        elems_{elem},
        cube_{cube_}
    {
        set_slices(cube_, elem, elem + 1);
    }

    template<typename CubeType, typename FT>
    Subcube<CubeType, FT>::Subcube(CubeType& cube_, size_type elem_first, size_type elem_last) :
        base(cube_.slices(), allocator_type{}),
        elems_{std::pair{elem_first, elem_last}},
        cube_{cube_}
    {
        set_slices(cube_, elem_first, elem_last);
    }

    template<typename CubeType, typename FT>
    void
    Subcube<CubeType, FT>::fill(value_type value)
    {
        auto ranges = std::visit(visitor::Cube_subview_elements_visitor{}, elems_);

        size_type last = (std::is_same_v<fill_type, Row> ? base::operator[](0).rows() : base::operator[](0).cols());

        for(size_type i = 0; i < base::slices(); ++i)
        {
            fill_type::fill(cube_[i], ranges.first, ranges.second, value);
            fill_type::fill(base::operator[](i), 0, last, value);
        }
    }

    //

    template<typename CubeType, typename FT>
    void
    Subcube<CubeType, FT>::set_slices(CubeType cube, size_type elem_first, size_type elem_last)
    {
        for(size_type i = 0; i < base::slices(); ++i)
        {
            auto matrix = fill_type::get(cube[i], elem_first, elem_last);
            base::operator[](i) = matrix;
        }
    }

    template<typename CubeType, typename FT>
    void
    Subcube<CubeType, FT>::set_slices(CubeType cube, std::initializer_list<size_type> elems)
    {
        for(size_type i = 0; i < base::slices(); ++i)
        {
            auto matrix = fill_type::get(cube[i], elems);
            base::operator[](i) = matrix;
        }
    }


} // namespace linalg

#endif // CUBE_SUBVIEW_TCC
