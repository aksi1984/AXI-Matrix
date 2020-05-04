#ifndef TENSOR_BASE_TCC
#define TENSOR_BASE_TCC

#include "Tensor_base.hpp"

namespace linalg
{
    template<typename Obj, typename T, typename Alloc>
    Tensor_base<Obj, T, Alloc>::Tensor_base(const allocator_type& alloc) :
        data_(alloc) { }

    template<typename Obj, typename T, typename Alloc>
    Tensor_base<Obj, T, Alloc>::Tensor_base(size_type req_slices, const allocator_type& alloc) :
        data_(req_slices) { }

    template<typename Obj, typename T, typename Alloc>
    Tensor_base<Obj, T, Alloc>::Tensor_base(size_type req_slices, object_type obj, const allocator_type& alloc) :
        data_(req_slices, obj, alloc) { }

    template<typename Obj, typename T, typename Alloc>
    typename Tensor_base<Obj, T, Alloc>::size_type
    Tensor_base<Obj, T, Alloc>::slices() const noexcept
    {
        return data_.size();
    }

    template<typename Obj, typename T, typename Alloc>
    typename Tensor_base<Obj, T, Alloc>::reference
    Tensor_base<Obj, T, Alloc>::operator[](size_type n)
    {
        return data_[n];
    }

    template<typename Obj, typename T, typename Alloc>
    typename Tensor_base<Obj, T, Alloc>::const_reference
    Tensor_base<Obj, T, Alloc>::operator[](size_type n) const
    {
        return data_[n];
    }

} // namespace linalg

#endif // TENSOR_BASE_TCC
