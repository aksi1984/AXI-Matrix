#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <memory>
#include <iostream>
#include <type_traits>

#include "Iterator.hpp"

namespace linarg
{
    template<typename T, typename Alloc = std::allocator<T>>
    class Container
    {
    public:

        using value_type      = T;
        using reference       = T&;
        using const_reference = const T&;
        using pointer         = T*;
        using const_pointer   = const T*;
        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;
        using allocator_type  = Alloc;

        using iterator        = pointer;
        using const_iterator  = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        Container(const allocator_type& alloc = allocator_type{}) :
            alloc_{alloc},
            data_{nullptr},
            size_{} { }

        Container(size_type n, value_type v = value_type{}, const allocator_type& alloc = allocator_type{}) :
            alloc_{alloc},
            data_(alloc_.allocate(n)),
            size_(n)
        {
            for(size_type i = 0; i < size_; ++i)
            {
                alloc_.construct(data_ + i, v);
            }
        }

        Container(const Container& copy) :
            alloc_(copy.alloc_),
            size_(copy.size_)
        {
            data_ = alloc_.allocate(size_);
            std::uninitialized_copy(copy.cbegin(), copy.cend(), data_);
        }

        Container(Container&& move) :
            alloc_{move.alloc_},
            data_{move.data_},
            size_{move.size_}
        {
            move.data_ = nullptr;
            move.size_ = 0;
        }

        ~Container()
        {
            if(!empty())
            {
                alloc_.deallocate(data_, size_);
                size_ = 0;
            }
        }

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Container(const Container<U>& copy) :
            size_{copy.size()},
            alloc_{copy.get_allocator()}
        {
            data_ = alloc_.allocate(size_);
            std::uninitialized_copy(copy.cbegin(), copy.cend(), data_);
        }

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Container(Container<U>&& move) :
            size_{move.size()},
            alloc_{move.get_allocator()}
        {
            data_ = alloc_.allocate(size_);
            std::uninitialized_copy(move.cbegin(), move.cend(), data_);
            move.clear();
        }

        Container& operator=(const Container& rhs)
        {
            alloc_ = rhs.alloc_;

            if(size_ != rhs.size_)
            {
                resize(rhs.size_);
            }

            std::uninitialized_copy(rhs.cbegin(), rhs.cend(), data_);

            return *this;

        }

        Container& operator=(Container&& rhs)
        {
            if(this != &rhs)
            {
                swap(rhs);
                rhs.clear();
            }

            return *this;
        }

        allocator_type get_allocator() const noexcept
        {
            return alloc_;
        }

        iterator begin()
        {
            return data_;
        }

        iterator end()
        {
            return data_ + size();
        }

        const_iterator cbegin() const
        {
            return data_;
        }

        const_iterator cend() const
        {
            return data_ + size();
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator(cend());
        }

        const_reverse_iterator crend() const
        {
            return const_reverse_iterator(cbegin());
        }

        bool empty() const noexcept
        {
            return size_ == 0;
        }

        reference operator[](size_type n)
        {
            return *(data_ + n);
        }

        const_reference operator[](size_type n) const
        {
            return *(data_ + n);
        }

        size_type size() const noexcept
        {
            return size_;
        }

        void resize(size_type n, value_type v = value_type{})
        {
            pointer helper = alloc_.allocate(n);

            if(size() > n)
            {
                std::uninitialized_copy(begin(), begin() + n, helper);
            }
            else if(size() < n)
            {
                std::uninitialized_copy(begin(), end(), helper);

                for(auto p = helper + size_; p != helper + n; ++p)
                {
                    *p = v;
                }
            }

            data_ = helper;
            size_ = n;
        }

        void insert(size_type position, value_type value)
        {
            pointer helper = alloc_.allocate(size_ + 1);

            std::uninitialized_copy(begin(), begin() + position, helper);
            *(helper + position) = value;
            std::uninitialized_copy(data_ + (position), data_ + size_, helper + (position + 1));

            data_ = helper;
            size_++;
        }

        template<typename Iterator>
        void insert(Iterator position, value_type value)
        {
            difference_type offset = position - begin();

            insert(static_cast<size_type>(offset), value);
        }

        void erase(size_type position)
        {
            if(empty())
            {
                return;
            }

            pointer helper = alloc_.allocate(size_ - 1);

            std::uninitialized_copy(begin(), begin() + position, helper);
            std::uninitialized_copy(begin() + (position + 1), begin() + size_, helper + position);

            data_ = helper;
            size_--;
        }

        void clear()
        {
            if(!empty())
            {
                resize(0);
                size_ = 0;
            }
        }

        void swap(Container& other)
        {
            if(this != &other)
            {
                std::swap(size_, other.size_);
                std::swap(data_, other.data_);
            }
        }

    private:

        allocator_type alloc_;
        pointer data_;
        size_type size_;
    };


}

#endif // CONTAINER_HPP
