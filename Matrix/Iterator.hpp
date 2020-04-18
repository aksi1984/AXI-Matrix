#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "Matrix_size.hpp"
#include <iterator>

namespace linarg
{
    template<typename Iterator>
    inline typename std::iterator_traits<Iterator>::difference_type dist(Iterator first, Iterator last)
    {
        typename std::iterator_traits<Iterator>::difference_type diff = 0;

        while(first != last)
        {
            diff++;
            first++;
        }

        return diff;
    }

    template<typename T>
    struct matrix_iterator : public std::iterator< typename std::iterator_traits<T>::iterator_category,
                                                     typename std::iterator_traits<T>::value_type,
                                                     typename std::iterator_traits<T>::reference,
                                                     typename std::iterator_traits<T>::pointer,
                                                     typename std::iterator_traits<T>::difference_type>
    {
        using traits            = std::iterator_traits<T>;
        using iterator_category = typename traits::iterator_category;
        using value_type        = typename traits::value_type;
        using reference         = typename traits::reference;
        using pointer           = typename traits::pointer;
        using difference_type   = typename traits::difference_type;

        matrix_iterator() { }

        matrix_iterator(pointer ptr) :
            ptr_(ptr) { }

        pointer base()
        {
            return ptr_;
        }

        reference operator*()
        {
            return *ptr_;
        }

        pointer operator->()
        {
            return ptr_;
        }

        matrix_iterator operator++()
        {
            ptr_++;
            return *this;
        }

        matrix_iterator operator++(int)
        {
            matrix_iterator tmp = *this;
            ptr_++;
            return tmp;
        }

        matrix_iterator operator--()
        {
            ptr_--;
            return *this;
        }

        matrix_iterator operator--(int)
        {
            matrix_iterator tmp = *this;
            ptr_--;
            return tmp;
        }

        matrix_iterator operator+(std::size_t n)
        {
            return matrix_iterator(ptr_ + n);
        }

        matrix_iterator operator-(difference_type n)
        {
            return matrix_iterator(ptr_ - n);
        }

        matrix_iterator operator+=(difference_type n)
        {
            ptr_ += n;
            return *this;
        }

        matrix_iterator operator-=(difference_type n)
        {
            ptr_ -= n;

            return *this;
        }

        bool operator==(matrix_iterator rhs)
        {
            return (ptr_ == rhs.ptr_);
        }

        bool operator!=(matrix_iterator rhs)
        {
            return !(ptr_ == rhs.ptr_);
        }

        bool operator<(matrix_iterator rhs)
        {
            return (ptr_ < rhs.ptr_);
        }

    private:

        pointer ptr_;
    };

    template<typename Iterator>
    class matrix_reverse_iterator
    {
    public:

        Iterator current;

        using iterator_type     = Iterator;
        using iterator_category = typename iterator_type::iterator_category;
        using value_type        = typename iterator_type::value_type;
        using reference         = typename iterator_type::reference;
        using pointer           = typename iterator_type::pointer;
        using differenece_type  = typename iterator_type::difference_type;

        matrix_reverse_iterator() { }

        matrix_reverse_iterator(iterator_type iter) :
            current(iter) { }

        iterator_type base() const
        {
            return current;
        }

        reference operator*()
        {
            iterator_type tmp = current;
            return *--tmp;
        }

        pointer operator->()
        {
            return &(*operator*());
        }

        matrix_reverse_iterator& operator++()
        {
            --current;
            return *this;
        }

        matrix_reverse_iterator& operator++(int)
        {
            matrix_reverse_iterator tmp = *this;
            --current;
            return tmp;
        }

        matrix_reverse_iterator& operator--()
        {
            ++current;
        }

        matrix_reverse_iterator& operator--(int)
        {
            matrix_reverse_iterator tmp = *this;
            ++current;
            return *this;
        }

        matrix_reverse_iterator operator+=(differenece_type n)
        {
            current-= n;
            return *this;
        }

        matrix_reverse_iterator& operator-=(differenece_type n)
        {
            current+= n;
            return *this;
        }

        bool operator==(const matrix_reverse_iterator rhs)
        {
            return (current == rhs.base());
        }

        bool operator!=(const matrix_reverse_iterator& rhs)
        {
            return !(current == rhs.base());
        }

        bool operator<(const matrix_reverse_iterator& rhs)
        {
            return (current < rhs.base());
        }
    };


    template<typename Iterator>
    class matrix_col_iterator : std::iterator< typename std::iterator_traits<Iterator>::iterator_category,
                                          typename std::iterator_traits<Iterator>::value_type,
                                          typename std::iterator_traits<Iterator>::reference,
                                          typename std::iterator_traits<Iterator>::pointer,
                                          typename std::iterator_traits<Iterator>::difference_type
                                        >
    {

    public:

        using iterator_type     = Iterator;
        using traits_type       = std::iterator_traits<Iterator>;
        using iterator_category = typename traits_type::iterator_category;
        using value_type        = typename traits_type::value_type;
        using reference         = typename traits_type::reference;
        using pointer           = typename traits_type::pointer;
        using difference_type   = typename traits_type::difference_type;
        using size_type         = std::size_t;

        matrix_col_iterator() { }

        matrix_col_iterator(iterator_type it, Matrix_size size, size_type n_col) :
            current_(it + (size.rows_ * n_col)) { }

        matrix_col_iterator(iterator_type it, Matrix_size size, size_type n_col, size_type last_element) :
            current_(it + last_element + (size.rows_ * n_col)) { }

        iterator_type base() const
        {
            return current_;
        }

        reference operator*()
        {
            return *current_;
        }

        pointer operator->()
        {
            return &(operator*());
        }

        matrix_col_iterator operator++()
        {
            current_++;

            return *this;
        }

        matrix_col_iterator operator++(int)
        {
            matrix_col_iterator tmp;
            current_++;

            return tmp;
        }

        matrix_col_iterator operator+(difference_type n)
        {
            current_ += n;

            return *this;
        }

        matrix_col_iterator operator-(difference_type n)
        {
            current_ -= n;

            return *this;
        }

        matrix_col_iterator operator--()
        {
            current_--;
            return *this;
        }

        matrix_col_iterator operator--(int)
        {
            matrix_col_iterator tmp;
            current_--;

            return tmp;
        }

        bool operator==(matrix_col_iterator rhs)
        {
            return (current_ == rhs.current_);
        }

        bool operator!=(matrix_col_iterator rhs)
        {
            return !(current_ == rhs.current_);
        }

        bool operator<(matrix_col_iterator rhs)
        {
            return (current_ < rhs.current_);
        }

    private:

        Iterator current_;
    };

    template<typename Iterator>
    class matrix_row_iterator : public std::iterator< typename std::iterator_traits<Iterator>::iterator_category,
                                                 typename std::iterator_traits<Iterator>::value_type,
                                                 typename std::iterator_traits<Iterator>::reference,
                                                 typename std::iterator_traits<Iterator>::pointer,
                                                 typename std::iterator_traits<Iterator>::difference_type>
    {
    public:

        using iterator_type     = Iterator;

        using traits_type       = std::iterator_traits<Iterator>;
        using iterator_category = typename traits_type::iterator_category;
        using value_type        = typename traits_type::value_type;
        using reference         = typename traits_type::reference;
        using pointer           = typename traits_type::pointer;
        using difference_type   = typename traits_type::difference_type;

        matrix_row_iterator() { }

        matrix_row_iterator(iterator_type it, Matrix_size size, std::size_t n_row) :
            current_(it + n_row),
            stride_(size.rows_) { }

        matrix_row_iterator(Iterator it, std::size_t stride, std::size_t n_row) :
            current_(it + n_row),
            stride_(stride) { }

        iterator_type base() const
        {
            return current_;
        }

        reference operator*()
        {
            return *current_;
        }

        pointer operator->()
        {
            return &(operator*());
        }

        matrix_row_iterator operator++()
        {
            current_ += stride_;
            return *this;
        }

        matrix_row_iterator operator++(int)
        {
            matrix_row_iterator tmp;
            current_ += stride_;
            return tmp;
        }

        matrix_row_iterator operator--()
        {
            current_ -= 1;
            return *this;
        }

        matrix_row_iterator operator+(difference_type n)
        {
            current_ += (n * stride_);
            return *this;
        }

        matrix_row_iterator operator-(difference_type n)
        {
            current_ -= (n * stride_);
            return *this;
        }

        bool operator==(matrix_row_iterator rhs)
        {
            return current_ == rhs.current_;
        }

        bool operator!=(matrix_row_iterator rhs)
        {
            return !(current_ == rhs.current_);
        }

        bool operator<(matrix_row_iterator rhs)
        {
            return (current_ < rhs.current_);
        }

    private:

        iterator_type current_;
        std::size_t stride_;
    };



    template<typename Iterator>
    class matrix_diag_iterator : public std::iterator< typename std::iterator_traits<Iterator>::iterator_category,
                                                       typename std::iterator_traits<Iterator>::value_type,
                                                       typename std::iterator_traits<Iterator>::reference,
                                                       typename std::iterator_traits<Iterator>::pointer,
                                                       typename std::iterator_traits<Iterator>::difference_type >
    {
    public:

        using iterator_type     = Iterator;

        using traits_type       = std::iterator_traits<Iterator>;
        using iterator_category = typename traits_type::iterator_category;
        using value_type        = typename traits_type::value_type;
        using reference         = typename traits_type::reference;
        using pointer           = typename traits_type::pointer;
        using difference_type   = typename traits_type::difference_type;

        matrix_diag_iterator() { }

        matrix_diag_iterator(iterator_type it, std::size_t rows = 0) :
            current_{it},
            rows_{rows + 1} { }

        iterator_type base()
        {
            return current_;
        }

        reference operator*()
        {
            return *current_;
        }

        matrix_diag_iterator operator++()
        {
            current_ += rows_;
            rows_count_++;
            return *this;
        }

        matrix_diag_iterator operator++(int)
        {
            current_ += rows_;
            rows_count_++;
            return *this;
        }

        pointer operator->()
        {
            return &(operator*());
        }

        bool operator==(matrix_diag_iterator rhs)
        {
            return current_ == rhs.current_;
        }

        bool operator!=(matrix_diag_iterator rhs)
        {
            return !(current_ == rhs.current_);
        }

    private:

        iterator_type current_;
        std::size_t rows_;
        static std::size_t rows_count_;
    };

    template<typename Iterator>
    std::size_t matrix_diag_iterator<Iterator>::rows_count_;
}

#endif // ITERATOR_HPP
