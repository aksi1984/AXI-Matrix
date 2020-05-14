#ifndef BASE_TCC
#define BASE_TCC

#include "Base.hpp"

namespace linalg
{
    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>::Base() { }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>::Base(size_type req_rows, size_type req_cols, const allocator_type& alloc) :
        data_(req_rows * req_cols, 0, alloc),
        size_(req_rows, req_cols) { }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>::Base(const Matrix_size& mat_size, const allocator_type& alloc) :
        Base(mat_size.rows_, mat_size.cols_, alloc) { }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>::Base(const Base<C, T, A, Alloc>& copy) :
        data_(copy.data_),
        size_(copy.size_) {}

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>::Base(Base<C, T, A, Alloc>&& move) :
        data_(move.data_),
        size_(move.size_)
    {
        move.clear();
    }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>&
    Base<C, T, A, Alloc>::operator=(const Base<C, T, A, Alloc>& rhs)
    {
        size_ = rhs.size_;
        data_ = rhs.data_;

        return *this;
    }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>&
    Base<C, T, A, Alloc>::operator=(Base<C, T, A, Alloc>&& rhs)
    {
        data_ = rhs.data_;
        size_ = rhs.size_;

        rhs.size_ = Matrix_size{};

        return *this;
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>:: allocator_type
    Base<C, T, A, Alloc>::get_allocator() const noexcept
    {
        return data_.get_allocator();
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::size_type
    Base<C, T, A, Alloc>::rows() const noexcept
    {
        return size_.rows_;
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::size_type
    Base<C, T, A, Alloc>::cols() const noexcept
    {
        return  size_.cols_;
    }

    template<typename C, typename T, typename A, typename Alloc>
    Matrix_size
    Base<C, T, A, Alloc>::size() const noexcept
    {
        return size_;
    }

    template<typename C, typename T, typename A, typename Alloc>
    bool
    Base<C, T, A, Alloc>::empty() const noexcept
    {
        return data_.empty();
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::reference
    Base<C, T, A, Alloc>::operator[](size_type n)
    {
        return data_[n];
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::const_reference
    Base<C, T, A, Alloc>::operator[](size_type n) const
    {
        return data_[n];
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::reference
    Base<C, T, A, Alloc>::operator()(size_type i, size_type j)
    {
        LINALG_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("operator()") )

        return data_[size_.rows_ * j + i];
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::const_reference
    Base<C, T, A, Alloc>::operator()(size_type i, size_type j) const
    {
        LINALG_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("operator()") )

        return data_[size_.rows_ * j + i];
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::reference
    Base<C, T, A, Alloc>::at(size_type i, size_type j)
    {
        LINALG_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("at()") )

        return data_[size_.rows_ * j + i];
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::const_reference
    Base<C, T, A, Alloc>::at(size_type i, size_type j) const
    {
        LINALG_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("at()") )

        return data_[size_.rows_ * j + i];
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::pointer
    Base<C, T, A, Alloc>::data() noexcept
    {
        return data_.begin();
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::const_pointer
    Base<C, T, A, Alloc>::data() const noexcept
    {
        return data_.begin();
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::iterator
    Base<C, T, A, Alloc>::begin()
    {
        return iterator(data_.begin());
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::iterator
    Base<C, T, A, Alloc>::end()
    {
        return iterator(data_.end());
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::const_iterator
    Base<C, T, A, Alloc>::cbegin() const
    {
        return const_iterator(data_.cbegin());
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::const_iterator
    Base<C, T, A, Alloc>::cend() const
    {
        return const_iterator(data_.cend());
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::reverse_iterator
    Base<C, T, A, Alloc>::rbegin()
    {
        return reverse_iterator(end());
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::reverse_iterator
    Base<C, T, A, Alloc>::rend()
    {
        return reverse_iterator(begin());
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::col_iterator
    Base<C, T, A, Alloc>::begin_col(size_type n)
    {
        return col_iterator(begin(), size_, n);
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::col_iterator
    Base<C, T, A, Alloc>::end_col(size_type n)
    {
        return col_iterator(begin(), size_, n, size_.rows_);
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::row_iterator
    Base<C, T, A, Alloc>::begin_row(size_type n_row)
    {
        return row_iterator(begin(), size_, n_row);
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::row_iterator
    Base<C, T, A, Alloc>::end_row(size_type n_row)
    {
        return row_iterator(begin(), size_.cols_, size_.rows_ * (size_.cols_ ) + n_row);
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::diag_iterator
    Base<C, T, A, Alloc>::begin_diag()
    {
        return diag_iterator(begin(), rows());
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::diag_iterator
    Base<C, T, A, Alloc>::end_diag()
    {
        return diag_iterator(begin() + ((cols() * rows()) - 1) + (rows() + 1));
    }

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::value_type
    Base<C, T, A, Alloc>::det()
    {
        return math::det(*this);
    }

    template<typename C, typename T, typename A, typename Alloc>
    void
    Base<C, T, A, Alloc>::clear()
    {
        data_.clear();
        size_ = Matrix_size();
    }

    template<typename C, typename T, typename A, typename Alloc>
    void
    Base<C, T, A, Alloc>::swap_rows(size_type row_1, size_type row_2)
    {
        swap_elems(begin_row(row_1), end_row(row_1), begin_row(row_2), end_row(row_2));
    }

    template<typename C, typename T, typename A, typename Alloc>
    void
    Base<C, T, A, Alloc>::swap_rows(Base& other, size_type row_1, size_type row_2)
    {
        swap_elems(begin_row(row_1), end_row(row_1), other.begin_row(row_2), other.end_row(row_2));
    }

    template<typename C, typename T, typename A, typename Alloc>
    void
    Base<C, T, A, Alloc>::swap_cols(size_type col_1, size_type col_2)
    {
        swap_elems(begin_col(col_1), end_col(col_1), begin_col(col_2), end_col(col_2));
    }

    template<typename C, typename T, typename A, typename Alloc>
    void
    Base<C, T, A, Alloc>::swap_cols(Base<C, T, A, Alloc>& other, size_type col_1, size_type col_2)
    {
        swap_elems(begin_col(col_1), end_col(col_1), other.begin_col(col_2), other.end_col(col_2));
    }

    template<typename C, typename T, typename A, typename Alloc>
    void
    Base<C, T, A, Alloc>::set_size(const Matrix_size& mat_size)
    {
        size_ = mat_size;
    }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>&
    Base<C, T, A, Alloc>::operator+=(const Base<C, T, A, Alloc>& rhs)
    {
        Base<T, A, Alloc> result = op::Plus<self_type, self_type>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>&
    Base<C, T, A, Alloc>::operator-=(const Base<C, T, A, Alloc>& rhs)
    {
        Base<C, T, A, Alloc> result = op::Minus<self_type, self_type>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>&
    Base<C, T, A, Alloc>::operator*=(const Base<C, T, A, Alloc>& rhs)
    {
        Base<C, T, A, Alloc> result = op::Multiplies<self_type, self_type>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc>&
    Base<C, T, A, Alloc>::operator*=(const value_type& scalar)
    {
        Base<C, T, A, Alloc> result = op::Scalar_multiplies<self_type, value_type>()(*this, scalar);
        *this = result;

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////

    template<typename C, typename T, typename A, typename Alloc>
    typename Base<C, T, A, Alloc>::size_type
    Base<C, T, A, Alloc>::get_new_size(size_type old_size, size_type new_size)
    {
        return ( new_size > old_size ? old_size : new_size );
    }

    template<typename C, typename T, typename A, typename Alloc>
    void
    Base<C, T, A, Alloc>::set_array(const Unbounded_array<T> &data)
    {
        data_ = data;
    }

    template<typename C, typename T, typename A, typename Alloc>
        template<typename I>
        void
        Base<C, T, A, Alloc>::swap_elems(I first_1, I last_1, I first_2, I last_2)
        {
            auto d = dist(first_1, last_1);

            Vector<T> vec(d);

            for(size_type i = 0 ; first_2 != last_2; ++first_2, ++i, ++first_1)
            {
                vec[i] = *first_2;
                *first_2 = *first_1;
                *first_1 = vec[i];
            }
        }

    template<typename C, typename T, typename A, typename Alloc>
    void
    Base<C, T, A, Alloc>::copy_from_other(Base<C, T, A, Alloc>& other)
    {
        for(size_type i = 0; i < rows(); ++i)
        {
            for(size_type j = 0; j < cols(); ++j)
            {
                data_[rows() * j + i] = other(i, j);
            }
        }
    }

    template<typename C, typename T, typename A, typename Alloc>
    void
    Base<C, T, A, Alloc>::copy_from_other(Base<C, T, A, Alloc>& other, size_type r, size_type c)
    {
        for(size_type i = 0; i < r; ++i)
        {
            for(size_type j = 0; j < c; ++j)
            {
                other(i, j) = data_[rows() * j + i];
            }
        }
    }

    //Ops

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc> operator+(const Base<C, T, A, Alloc>& lhs, const Base<C, T, A, Alloc>& rhs)
    {
        using current_type = Base<T, C, Alloc>;
        return  op::Plus<current_type, current_type>()(lhs, rhs);
    }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc> operator-(const Base<C, T, A, Alloc>& lhs, const Base<C, T, A, Alloc>& rhs)
    {
        using current_type = Base<T, C, Alloc>;
        return op::Minus<current_type, current_type>()(lhs, rhs);
    }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc> operator*(const Base<C, T, A, Alloc>& lhs, const Base<C, T, A, Alloc>& rhs)
    {
        using current_type = Base<C, T, A, Alloc>;
        return op::Multiplies<current_type, current_type>()(lhs, rhs);
    }

    template<typename C, typename T, typename A, typename Alloc>
    Base<C, T, A, Alloc> operator*(const Base<C, T, A, Alloc>& lhs, const T& scalar)
    {
        using current_type = Base<C, T, A, Alloc>;
        return op::Scalar_multiplies<current_type, T>()(lhs, scalar);
    }

    template<typename C, typename T, typename A, typename Alloc>
    bool operator==(const Base<C, T, A, Alloc>& lhs, const Base<C, T, A, Alloc>& rhs)
    {
        using type = Base<C, T, A, Alloc>;
        return op::Equal<type, type>()(lhs, rhs);
    }

}

#endif // BASE_TCC
