#ifndef BASE_TCC
#define BASE_TCC

#include "Base.hpp"
#include "Arrays.hpp"

namespace linalg
{
    template<typename Type, typename T, typename A, typename Alloc>
    Base<Type, T, A, Alloc>&
    Base<Type, T, A, Alloc>::operator=(const Base<Type, T, A, Alloc>& rhs)
    {
        size_ = rhs.size_;
        data_ = rhs.data_;

        return *this;
    }

    template<typename Type, typename T, typename A, typename Alloc>
    Base<Type, T, A, Alloc>&
    Base<Type, T, A, Alloc>::operator=(Base<Type, T, A, Alloc>&& rhs)
    {
        size_ = rhs.size_;
        data_ = std::move(rhs.data_);

        rhs.size_ = Matrix_size{};

        return *this;
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>:: allocator_type
    Base<Type, T, A, Alloc>::get_allocator() const noexcept
    {
        return data_.get_allocator();
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::size_type
    Base<Type, T, A, Alloc>::rows() const noexcept
    {
        return size_.rows_;
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::size_type
    Base<Type, T, A, Alloc>::cols() const noexcept
    {
        return  size_.cols_;
    }

    template<typename Type, typename T, typename A, typename Alloc>
    Matrix_size
    Base<Type, T, A, Alloc>::size() const noexcept
    {
        return size_;
    }

    template<typename Type, typename T, typename A, typename Alloc>
    bool
    Base<Type, T, A, Alloc>::empty() const noexcept
    {
        return data_.empty();
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::reference
    Base<Type, T, A, Alloc>::operator()(size_type i, size_type j)
    {
        LINARG_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("operator()") )

        return data_[size_.rows_ * j + i];
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::const_reference
    Base<Type, T, A, Alloc>::operator()(size_type i, size_type j) const
    {
        LINARG_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("operator()") )

        return data_[size_.rows_ * j + i];
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::reference
    Base<Type, T, A, Alloc>::at(size_type i, size_type j)
    {
        LINARG_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("at()") )

        return data_[size_.rows_ * j + i];
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::const_reference
    Base<Type, T, A, Alloc>::at(size_type i, size_type j) const
    {
        LINARG_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("at()") )

        return data_[size_.rows_ * j + i];
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::pointer
    Base<Type, T, A, Alloc>::data() noexcept
    {
        return data_.begin();
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::const_pointer
    Base<Type, T, A, Alloc>::data() const noexcept
    {
        return data_.begin();
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::iterator
    Base<Type, T, A, Alloc>::begin()
    {
        return iterator(data_.begin());
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::iterator
    Base<Type, T, A, Alloc>::end()
    {
        return iterator(data_.end());
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::const_iterator
    Base<Type, T, A, Alloc>::cbegin() const
    {
        return const_iterator(data_.cbegin());
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::const_iterator
    Base<Type, T, A, Alloc>::cend() const
    {
        return const_iterator(data_.cend());
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::reverse_iterator
    Base<Type, T, A, Alloc>::rbegin()
    {
        return reverse_iterator(end());
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::reverse_iterator
    Base<Type, T, A, Alloc>::rend()
    {
        return reverse_iterator(begin());
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::col_iterator
    Base<Type, T, A, Alloc>::begin_col(size_type n)
    {
        return col_iterator(begin(), size_, n);
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::col_iterator
    Base<Type, T, A, Alloc>::end_col(size_type n)
    {
        return col_iterator(begin(), size_, n, size_.rows_);
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::row_iterator
    Base<Type, T, A, Alloc>::begin_row(size_type n_row)
    {
        return row_iterator(begin(), size_, n_row);
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::row_iterator
    Base<Type, T, A, Alloc>::end_row(size_type n_row)
    {
        return row_iterator(begin(), size_.cols_, size_.rows_ * (size_.cols_ ) + n_row);
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::diag_iterator
    Base<Type, T, A, Alloc>::begin_diag()
    {
        return diag_iterator(begin(), rows());
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::diag_iterator
    Base<Type, T, A, Alloc>::end_diag()
    {
        return diag_iterator(begin() + ((cols() * rows()) - 1) + (rows() + 1));
    }

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::value_type
    Base<Type, T, A, Alloc>::det()
    {
        return math::det(*this);
    }

    template<typename Type, typename T, typename A, typename Alloc>
    void
    Base<Type, T, A, Alloc>::clear()
    {
        data_.clear();
        size_ = Matrix_size();
    }

    template<typename Type, typename T, typename A, typename Alloc>
    void
    Base<Type, T, A, Alloc>::swap_rows(size_type row_1, size_type row_2)
    {
        swap_elems(begin_row(row_1), end_row(row_1), begin_row(row_2), end_row(row_2));
    }

    template<typename Type, typename T, typename A, typename Alloc>
    void
    Base<Type, T, A, Alloc>::swap_rows(Base& other, size_type row_1, size_type row_2)
    {
        swap_elems(begin_row(row_1), end_row(row_1), other.begin_row(row_2), other.end_row(row_2));
    }

    template<typename Type, typename T, typename A, typename Alloc>
    void
    Base<Type, T, A, Alloc>::swap_cols(size_type col_1, size_type col_2)
    {
        swap_elems(begin_col(col_1), end_col(col_1), begin_col(col_2), end_col(col_2));
    }

    template<typename Type, typename T, typename A, typename Alloc>
    void
    Base<Type, T, A, Alloc>::swap_cols(Base<Type, T, A, Alloc>& other, size_type col_1, size_type col_2)
    {
        swap_elems(begin_col(col_1), end_col(col_1), other.begin_col(col_2), other.end_col(col_2));
    }

    template<typename Type, typename T, typename A, typename Alloc>
    void
    Base<Type, T, A, Alloc>::set_size(const Matrix_size& mat_size)
    {
        size_ = mat_size;
    }

    template<typename Type, typename T, typename A, typename Alloc>
    Base<Type, T, A, Alloc>&
    Base<Type, T, A, Alloc>::operator+=(const Base<Type, T, A, Alloc>& rhs)
    {
        Base<T, A, Alloc> result = op::Plus<self_type, self_type>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename Type, typename T, typename A, typename Alloc>
    Base<Type, T, A, Alloc>&
    Base<Type, T, A, Alloc>::operator-=(const Base<Type, T, A, Alloc>& rhs)
    {
        Base<Type, T, A, Alloc> result = op::Minus<self_type, self_type>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename Type, typename T, typename A, typename Alloc>
    Base<Type, T, A, Alloc>&
    Base<Type, T, A, Alloc>::operator*=(const Base<Type, T, A, Alloc>& rhs)
    {
        Base<Type, T, A, Alloc> result = op::Multiplies<self_type, self_type>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename Type, typename T, typename A, typename Alloc>
    Base<Type, T, A, Alloc>&
    Base<Type, T, A, Alloc>::operator*=(const value_type& scalar)
    {
        Base<Type, T, A, Alloc> result = op::Scalar_multiplies<self_type, value_type>()(*this, scalar);
        *this = result;

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////

    template<typename Type, typename T, typename A, typename Alloc>
    typename Base<Type, T, A, Alloc>::size_type
    Base<Type, T, A, Alloc>::get_new_size(size_type old_size, size_type new_size)
    {
        return ( new_size > old_size ? old_size : new_size );
    }

    template<typename Type, typename T, typename A, typename Alloc>
    void
    Base<Type, T, A, Alloc>::set_array(const Unbounded_array<T> &data)
    {
        data_ = data;
    }

    template<typename Type, typename T, typename A, typename Alloc>
        template<typename I>
        void
        Base<Type, T, A, Alloc>::swap_elems(I first_1, I last_1, I first_2, I last_2)
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

    template<typename Type, typename T, typename A, typename Alloc>
    void
    Base<Type, T, A, Alloc>::copy_from_other(Base<Type, T, A, Alloc>& other)
    {
        for(size_type i = 0; i < rows(); ++i)
        {
            for(size_type j = 0; j < cols(); ++j)
            {
                data_[rows() * j + i] = other(i, j);
            }
        }
    }

    template<typename Type, typename T, typename A, typename Alloc>
    void
    Base<Type, T, A, Alloc>::copy_from_other(Base<Type, T, A, Alloc>& other, size_type r, size_type c)
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

    template<typename Type, typename T, typename C, typename Alloc>
    Base<Type, T, C, Alloc> operator+(const Base<Type, T, C, Alloc>& lhs, const Base<Type, T, C, Alloc>& rhs)
    {
        using current_type = Base<T, C, Alloc>;
        return  op::Plus<current_type, current_type>()(lhs, rhs);
    }

    template<typename Type, typename T, typename C, typename Alloc>
    Base<Type, T, C, Alloc> operator-(const Base<Type, T, C, Alloc>& lhs, const Base<Type, T, C, Alloc>& rhs)
    {
        using current_type = Base<T, C, Alloc>;
        return op::Minus<current_type, current_type>()(lhs, rhs);
    }

    template<typename Type, typename T, typename C, typename Alloc>
    Base<Type, T, C, Alloc> operator*(const Base<Type, T, C, Alloc>& lhs, const Base<Type, T, C, Alloc>& rhs)
    {
        using current_type = Base<T, C, Alloc>;
        return op::Multiplies<current_type, current_type>()(lhs, rhs);
    }

    template<typename Type, typename T, typename C, typename Alloc>
    Base<Type, T, C, Alloc> operator*(const Base<Type, T, C, Alloc>& lhs, const T& scalar)
    {
        using current_type = Base<T, C, Alloc>;
        return op::Scalar_multiplies<current_type, T>()(lhs, scalar);
    }

    template<typename Type, typename T, typename C, typename Alloc>
    bool operator==(const Base<Type, T, C, Alloc>& lhs, const Base<Type, T, C, Alloc>& rhs)
    {
        using type = Base<Type, T, C, Alloc>;
        return op::Equal<type, type>()(lhs, rhs);
    }

}

#endif // BASE_TCC
