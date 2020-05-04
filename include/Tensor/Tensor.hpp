#ifndef TENSOR_BASE_HPP
#define TENSOR_BASE_HPP

#include "include/Storage/Arrays.hpp"

namespace linalg
{
    template<typename Obj, typename C = Array<Obj>, typename Alloc = std::allocator<Obj>>
    class Tensor
    {
    public:

        using object_type       = Obj;
        using size_type         = std::size_t;
        using container_type    = C;
        using allocator_type    = Alloc;
        using reference         = object_type&;
        using const_reference   = const object_type&;

        Tensor(const allocator_type& alloc);
        Tensor(size_type req_slices, const allocator_type& alloc);
        Tensor(size_type req_slices, object_type obj, const allocator_type& alloc);
        Tensor(const Tensor& copy);
        Tensor(Tensor&& move);

        Tensor& operator=(const Tensor& rhs);
        Tensor& operator=(Tensor&& rhs);

        size_type slices() const noexcept;

        reference operator[](size_type n);
        const_reference operator[](size_type n) const;

        void clear();

    protected:

        container_type data_;
    };

} // namespace linalg

#endif // TENSOR_BASE_HPP
