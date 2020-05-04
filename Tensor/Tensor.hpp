#ifndef TENSOR_BASE_HPP
#define TENSOR_BASE_HPP

#include "Matrix/Arrays.hpp"

namespace linalg
{
template<typename Obj, typename C = Array<Obj>, typename Alloc = std::allocator<Obj>>
class Tensor_base
{
public:

    using object_type       = Obj;
    using size_type         = std::size_t;
    using container_type    = C;
    using allocator_type    = Alloc;
    using reference         = object_type&;
    using const_reference   = const object_type&;

    Tensor_base(const allocator_type& alloc);
    Tensor_base(size_type req_slices, const allocator_type& alloc);
    Tensor_base(size_type req_slices, object_type obj, const allocator_type& alloc);

    size_type slices() const noexcept;

    reference operator[](size_type n);
    const_reference operator[](size_type n) const;

private:

    container_type data_;
};

} // namespace linalg

#endif // TENSOR_BASE_HPP
