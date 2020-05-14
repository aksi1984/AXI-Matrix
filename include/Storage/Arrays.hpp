#ifndef ARRAYS_HPP
#define ARRAYS_HPP
#include <iostream>
#include <memory>

namespace linalg
{
    template<typename T, typename Alloc = std::allocator<T>>
    class Array
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

        Array(const allocator_type& alloc = allocator_type{}) :
            alloc_{alloc},
            data_{nullptr},
            size_{} { }

        Array(size_type n, value_type v = value_type{}, const allocator_type& alloc = allocator_type{}) :
            alloc_{alloc},
            data_(alloc_.allocate(n)),
            size_(n)
        {
            for(size_type i = 0; i < size_; ++i)
            {
                alloc_.construct(data_ + i, v);
            }
        }

        Array(const Array& copy) :
            alloc_(copy.alloc_),
            size_(copy.size_)
        {
            data_ = alloc_.allocate(size_);
            std::uninitialized_copy(copy.cbegin(), copy.cend(), data_);
        }

        Array(Array&& move) :
            alloc_{move.alloc_},
            data_{move.data_},
            size_{move.size_}
        {
            move.data_ = nullptr;
            move.size_ = 0;
        }

        virtual ~Array()
        {
            if(!empty())
            {
                alloc_.deallocate(data_, size_);
                size_ = 0;
            }
        }

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Array(const Array<U>& copy) :
            size_{copy.size()},
            alloc_{copy.get_allocator()}
        {
            data_ = alloc_.allocate(size_);
            std::uninitialized_copy(copy.cbegin(), copy.cend(), data_);
        }

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Array(Array<U>&& move) :
            size_{move.size()},
            alloc_{move.get_allocator()}
        {
            data_ = alloc_.allocate(size_);
            std::uninitialized_copy(move.cbegin(), move.cend(), data_);
            move.clear();
        }

        Array& operator=(const Array& rhs)
        {
            alloc_ = rhs.alloc_;

            if(size_ != rhs.size_)
            {
                pointer helper = alloc_.allocate(rhs.size());
                data_ = helper;
                size_ = rhs.size();
            }

            std::uninitialized_copy(rhs.cbegin(), rhs.cend(), data_);

            return *this;
        }

        Array& operator=(Array&& rhs)
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

        iterator begin() noexcept
        {
            return data_;
        }

        const_iterator begin() const noexcept
        {
            return data_;
        }

        iterator end() noexcept
        {
            return data_ + size();
        }

        const_iterator end() const noexcept
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

        reverse_iterator rbegin() noexcept
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const noexcept
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() noexcept
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const noexcept
        {
            return const_reverse_iterator(begin());
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

        virtual void clear()
        {
            if(!empty())
            {
                pointer helper = alloc_.allocate(0);
                data_ = helper;
                size_ = 0;
            }
        }

        void swap(Array& other)
        {
            if(this != &other)
            {
                std::swap(size_, other.size_);
                std::swap(data_, other.data_);
            }
        }

    protected:

        pointer get_data()
        {
            return data_;
        }

        void set_data(pointer data)
        {
            data_ = data;
        }

        void set_size(size_type n)
        {
            size_ = n;
        }

    private:

        allocator_type alloc_;
        pointer data_;
        size_type size_;
    };

    ///////////////////////////////////////////////////////////

    template<typename T, typename Alloc = std::allocator<T>>
    class Unbounded_array : public Array<T, Alloc>
    {
    public:

        using array_base      = Array<T, Alloc>;
        using value_type      = typename array_base::value_type;
        using reference       = typename array_base::reference;
        using const_reference = typename array_base::const_reference;
        using pointer         = typename array_base::pointer;
        using const_pointer   = typename array_base::const_pointer;
        using size_type       = typename array_base::size_type;
        using difference_type = typename array_base::difference_type;
        using allocator_type  = typename array_base::allocator_type;

        using iterator        = pointer;
        using const_iterator  = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        Unbounded_array(const allocator_type& alloc = allocator_type{}) :
            array_base(alloc) { }

        Unbounded_array(size_type n, value_type v = value_type{}, const allocator_type& alloc = allocator_type{}) :
            array_base(n, v, alloc) { }

        Unbounded_array(const Unbounded_array& copy) :
            array_base(copy) { }

        Unbounded_array(Unbounded_array&& move) :
            array_base(std::move(move)) { }

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Unbounded_array(const Unbounded_array<U>& copy) :
            array_base(copy) { }

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Unbounded_array(Unbounded_array<U>&& move) :
            array_base(std::move(move)) { }

        Unbounded_array& operator=(const Unbounded_array& rhs)
        {
            if(array_base::size() != rhs.size())
            {
                pointer helper = array_base::get_allocator().allocate(rhs.size());
                array_base::set_size(rhs.size());
                array_base::set_data(helper);
            }

            std::uninitialized_copy(rhs.begin(), rhs.end(), array_base::begin());

            return *this;
        }

        Unbounded_array& operator=(Unbounded_array&& rhs)
        {
            array_base::swap(rhs);

            rhs.clear();

            return *this;
        }

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Unbounded_array& operator=(const Unbounded_array<U>& rhs)
        {
            if(array_base::size() != rhs.size())
            {
                resize(rhs.size());
            }

            std::uninitialized_copy(rhs.begin(), rhs.end(), array_base::begin());

            return *this;
        }

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Unbounded_array& operator=(Unbounded_array<U>&& rhs)
        {
            *this = rhs;
            rhs.clear();

            return *this;
        }

        void resize(size_type n, value_type v = value_type{})
        {
            pointer helper = array_base::get_allocator().allocate(n);

            if(array_base::size() > n)
            {
                std::uninitialized_copy(array_base::begin(), array_base::begin() + n, helper);
            }
            else if(array_base::size() < n)
            {
                std::uninitialized_copy(array_base::begin(), array_base::end(), helper);

                for(auto p = helper + array_base::size(); p != helper + n; ++p)
                {
                    *p = v;
                }
            }

            array_base::set_data(helper);
            array_base::set_size(n);
        }

        void insert(size_type position, value_type value)
        {
            pointer helper = array_base::get_allocator().allocate(array_base::size() + 1);

            std::uninitialized_copy(array_base::begin(), array_base::begin() + position, helper);
            *(helper + position) = value;
            std::uninitialized_copy(array_base::get_data() + (position), array_base::get_data() + array_base::size(), helper + (position + 1));

            array_base::set_data(helper);
            array_base::set_size(array_base::size() + 1);
        }

        template<typename Iterator, typename = typename std::enable_if<std::is_pointer<Iterator>::value>::type>
        void insert(Iterator position, value_type value)
        {
            difference_type offset = position - array_base::begin();

            insert(static_cast<size_type>(offset), value);
        }

        void erase(size_type position)
        {
            if(array_base::empty())
            {
                return;
            }

            pointer helper = array_base::get_allocator().allocate(array_base::size() - 1);

            std::uninitialized_copy(array_base::begin(), array_base::begin() + position, helper);
            std::uninitialized_copy(array_base::begin() + (position + 1), array_base::begin() + array_base::size(), helper + position);

            array_base::set_data(helper);
            array_base::set_size(array_base::size() - 1);
        }

        void clear()
        {
            if(!array_base::empty())
            {
                resize(0);
                array_base::set_size(0);
            }
        }
    };

} // namespace linarg

#endif // ARRAYS_HPP
