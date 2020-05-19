#ifndef TENSOR_BASE_TCC
#define TENSOR_BASE_TCC

#include "Tensor.hpp"

namespace axi
{
    template<typename Obj, typename A, typename Alloc>
    Tensor<Obj, A, Alloc>::Tensor(const allocator_type& alloc) :
        data_(alloc) { }

    template<typename Obj, typename A, typename Alloc>
    Tensor<Obj, A, Alloc>::Tensor(size_type req_slices, const allocator_type& alloc) :
        data_(req_slices) { }

    template<typename Obj, typename A, typename Alloc>
    Tensor<Obj, A, Alloc>::Tensor(size_type req_slices, object_type obj, const allocator_type& alloc) :
        data_(req_slices, obj, alloc) { }

    template<typename Obj, typename A, typename Alloc>
    typename Tensor<Obj, A, Alloc>::size_type
    Tensor<Obj, A, Alloc>::slices() const noexcept
    {
        return data_.size();
    }

    template<typename Obj, typename A, typename Alloc>
    Tensor<Obj, A, Alloc>::Tensor(const Tensor<Obj, A, Alloc>& copy) :
        data_(copy.data_) { }

    template<typename Obj, typename A, typename Alloc>
    Tensor<Obj, A, Alloc>::Tensor(Tensor<Obj, A, Alloc>&& move) :
        data_(std::move(move.data_)) { }

    template<typename Obj, typename A, typename Alloc>
    Tensor<Obj, A, Alloc>&
    Tensor<Obj, A, Alloc>::operator=(const Tensor<Obj, A, Alloc>& rhs)
    {
        data_ = rhs.data_;

        return *this;
    }

    template<typename Obj, typename A, typename Alloc>
    Tensor<Obj, A, Alloc>&
    Tensor<Obj, A, Alloc>::operator=(Tensor<Obj, A, Alloc>&& rhs)
    {
        data_ = std::move(rhs.data_);

        return *this;
    }

    template<typename Obj, typename A, typename Alloc>
    typename Tensor<Obj, A, Alloc>::reference
    Tensor<Obj, A, Alloc>::operator[](size_type n)
    {
        return data_[n];
    }

    template<typename Obj, typename A, typename Alloc>
    typename Tensor<Obj, A, Alloc>::const_reference
    Tensor<Obj, A, Alloc>::operator[](size_type n) const
    {
        return data_[n];
    }

    template<typename Obj, typename A, typename Alloc>
    typename Tensor<Obj, A, Alloc>::reference
    Tensor<Obj, A, Alloc>::at(size_type n)
    {
        return data_[n];
    }

    template<typename Obj, typename A, typename Alloc>
    typename Tensor<Obj, A, Alloc>::const_reference
    Tensor<Obj, A, Alloc>::at(size_type n) const
    {
        return data_[n];
    }

    template<typename Obj, typename A, typename Alloc>
    typename Tensor<Obj, A, Alloc>::const_iterator
    Tensor<Obj, A, Alloc>::cbegin() const
    {
        return data_.cbegin();
    }

    template<typename Obj, typename A, typename Alloc>
    typename Tensor<Obj, A, Alloc>::const_iterator
    Tensor<Obj, A, Alloc>::cend() const
    {
        return data_.cend();
    }

    template<typename Obj, typename A, typename Alloc>
    typename Tensor<Obj, A, Alloc>::const_reverse_iterator
    Tensor<Obj, A, Alloc>::crbegin() const
    {
        return data_.crbegin();
    }

    template<typename Obj, typename A, typename Alloc>
    typename Tensor<Obj, A, Alloc>::const_reverse_iterator
    Tensor<Obj, A, Alloc>::crend() const
    {
        return data_.crend();
    }

    template<typename Obj, typename A, typename Alloc>
    void
    Tensor<Obj, A, Alloc>::clear()
    {
        data_.clear();
    }

    template<typename Obj, typename A, typename Alloc>
    Obj
    Tensor<Obj, A, Alloc>::slice(size_type req_slice)
    {
        return data_[req_slice];
    }

} // namespace linalg

#endif // TENSOR_BASE_TCC
