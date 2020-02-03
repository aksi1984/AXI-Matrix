#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Container.hpp"
#include "Matrix_initializer.hpp"
#include "Random.hpp"

#include "Operations.hpp"
#include "Traits.hpp"
#include "Type_aliases.h"
#include "Iterator.hpp"
#include "Base.hpp"

namespace linarg
{
    template<typename T>
    using Random_ptr = std::shared_ptr<rd::Random_base<T>>;



    template<typename T, typename C = Unbounded_array<T>>
    class Vector
    {
    private:

        using self_type                 = Vector<T, C>;

    public:

        using storage_type            = Unbounded_array<T>;
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


        explicit Vector(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, const allocator_type& alloc = allocator_type{});


        Vector(const Vector& copy);


        Vector(Vector&& move);


        Vector& operator=(const Vector& rhs);


        Vector& operator=(Vector&& rhs);


        Vector& operator=(const List<value_type>& list);


        Vector& operator=(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random);


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

        template<typename R>
        void fill_random(R random, std::true_type);

        template<typename R>
        void fill_random(R random, std::false_type);

        storage_type data_;
    };

} // namespace axi


#endif // VECTOR_HPP
