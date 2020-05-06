#ifndef TENSOR_BASE_TCC
#define TENSOR_BASE_TCC

#include "Tensor.hpp"

namespace linalg
{
    template<typename Obj, typename C, typename Alloc>
    Tensor<Obj, C, Alloc>::Tensor(const allocator_type& alloc) :
        data_(alloc) { }

    template<typename Obj, typename C, typename Alloc>
    Tensor<Obj, C, Alloc>::Tensor(size_type req_slices, const allocator_type& alloc) :
        data_(req_slices) { }

    template<typename Obj, typename C, typename Alloc>
    Tensor<Obj, C, Alloc>::Tensor(size_type req_slices, object_type obj, const allocator_type& alloc) :
        data_(req_slices, obj, alloc) { }

    template<typename Obj, typename T, typename Alloc>
    typename Tensor<Obj, T, Alloc>::size_type
    Tensor<Obj, T, Alloc>::slices() const noexcept
    {
        return data_.size();
    }

    template<typename Obj, typename C, typename Alloc>
    Tensor<Obj, C, Alloc>::Tensor(const Tensor<Obj, C, Alloc>& copy) :
        data_(copy.data_) { }

    template<typename Obj, typename C, typename Alloc>
    Tensor<Obj, C, Alloc>::Tensor(Tensor<Obj, C, Alloc>&& move) :
        data_(std::move(move.data_)) { }

    template<typename Obj, typename C, typename Alloc>
    Tensor<Obj, C, Alloc>&
    Tensor<Obj, C, Alloc>::operator=(const Tensor<Obj, C, Alloc>& rhs)
    {
        data_ = rhs.data_;

        return *this;
    }

    template<typename Obj, typename C, typename Alloc>
    Tensor<Obj, C, Alloc>&
    Tensor<Obj, C, Alloc>::operator=(Tensor<Obj, C, Alloc>&& rhs)
    {
        data_ = std::move(rhs.data_);

        return *this;
    }

    template<typename Obj, typename C, typename Alloc>
    typename Tensor<Obj, C, Alloc>::reference
    Tensor<Obj, C, Alloc>::operator[](size_type n)
    {
        return data_[n];
    }

    template<typename Obj, typename C, typename Alloc>
    typename Tensor<Obj, C, Alloc>::const_reference
    Tensor<Obj, C, Alloc>::operator[](size_type n) const
    {
        return data_[n];
    }

    template<typename Obj, typename C, typename Alloc>
    void
    Tensor<Obj, C, Alloc>::clear()
    {
        data_.clear();
    }

    template<typename Obj, typename C, typename Alloc>
    Obj
    Tensor<Obj, C, Alloc>::slice(size_type req_slice)
    {
        return data_[req_slice];
    }

} // namespace linalg

#endif // TENSOR_BASE_TCC
