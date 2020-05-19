#ifndef TENSOR_BASE_HPP
#define TENSOR_BASE_HPP

#include "include/Storage/Arrays.hpp"
#include "include/Matrix/Iterator.hpp"

namespace axi
{

    template<typename Obj, typename A = Array<Obj>, typename Alloc = std::allocator<Obj>>
    class Tensor
    {
    public:

        using object_type       = Obj;
        using array_type        = A;
        using allocator_type    = Alloc;
        using reference         = object_type&;
        using const_reference   = const object_type&;
        using pointer           = object_type*;
        using const_pointer     = const object_type*;
        using const_iterator    = typename A::const_iterator;
        using const_reverse_iterator = typename A::const_reverse_iterator;
        using size_type         = std::size_t;


        explicit Tensor(const allocator_type& alloc = allocator_type{});

        explicit Tensor(size_type req_slices, const allocator_type& alloc = allocator_type{});

        explicit Tensor(size_type req_slices, object_type obj, const allocator_type& alloc = allocator_type{});

        Tensor(const Tensor& copy);

        Tensor(Tensor&& move);

        Tensor& operator=(const Tensor& rhs);

        Tensor& operator=(Tensor&& rhs);

        size_type slices() const noexcept;

        reference operator[](size_type n);

        const_reference operator[](size_type n) const;

        reference at(size_type n);

        const_reference at(size_type n) const;

        const_iterator cbegin() const;

        const_iterator cend() const;

        const_reverse_iterator crbegin() const;

        const_reverse_iterator crend() const;

        void clear();

        Obj slice(size_type req_slice);

    protected:

        array_type data_;
    };

} // namespace linalg

#endif // TENSOR_BASE_HPP
