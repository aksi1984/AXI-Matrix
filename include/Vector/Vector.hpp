#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "include/Matrix/Matrix_initializer.tcc"
#include "include/Matrix/Random.hpp"
#include "include/Matrix/Operations.hpp"
#include "include/Matrix/Traits.hpp"
#include "include/Matrix/Cond.hpp"
#include "include/Matrix/Aliases.h"
#include "include/Matrix/Iterator.hpp"


namespace axi
{

    template<typename T, typename C = Unbounded_array<T>>
    class Vector
    {
    private:

        using self_type                 = Vector<T, C>;

    public:

        using storage_type              = Unbounded_array<T>;
        using value_type                = typename storage_type::value_type;
        using reference                 = typename storage_type::reference;
        using const_reference           = typename storage_type::const_reference;
        using size_type                 = typename storage_type::size_type;
        using allocator_type            = typename storage_type::allocator_type;
        using pointer                   = typename storage_type::pointer;
        using iterator                  = T*;
        using const_iterator            = const T*;
        using reverse_iterator          = std::reverse_iterator<iterator>;
        using const_reverse_iterator    = std::reverse_iterator<const_iterator>;


        explicit Vector(const allocator_type& alloc = allocator_type{});

        explicit Vector(size_type n, value_type v = {}, const allocator_type& alloc = allocator_type{});

        explicit Vector(List<value_type> list, const allocator_type& alloc = allocator_type{});

        explicit Vector(const std::string& expression, const allocator_type& alloc = allocator_type());

        explicit Vector(size_type req_size, Random<typename traits::Get_type<is_complex<T>::value, T>::type> random, const allocator_type& alloc = allocator_type());


        Vector(const Vector& copy);


        Vector(Vector&& move);


        Vector& operator=(const Vector& rhs);


        Vector& operator=(Vector&& rhs);


        Vector& operator=(const List<value_type>& list);

        Vector& operator=(Random<typename traits::Get_type<is_complex<T>::value, T>::type> rhs);


        iterator begin();


        iterator end();


        const_iterator cbegin() const;


        const_iterator cend() const;


        reverse_iterator rbegin();


        reverse_iterator rend();


        const_reverse_iterator crbegin() const;


        const_reverse_iterator crend() const;


        size_type size() const noexcept;


        bool empty() const noexcept;


        reference operator[](size_type n);


        const_reference operator[](size_type n) const;


        reference at(size_type n);


        const_reference at(size_type n) const;


        void resize(size_type n);


        void insert(size_type position, value_type value);


        template<typename Iterator, typename = typename std::enable_if<std::is_pointer<Iterator>::value>::type>
        void insert(Iterator position, value_type value);


        Vector& operator+=(const Vector& rhs);


        Vector& operator-=(const Vector& rhs);


        Vector& operator*=(const Vector& rhs);


        Vector& operator*=(value_type scalar);


        Vector& operator/=(value_type scalar);


    private:

        void take_random_values(Random<typename traits::Get_type<is_complex<T>::value, T>::type> random);

        storage_type data_;
    };

} // namespace axi


#endif // VECTOR_HPP
