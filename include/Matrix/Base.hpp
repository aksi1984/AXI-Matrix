#ifndef BASE_HPP
#define BASE_HPP

#include <memory>
#include <math.h>

#include "Tags.hpp"
#include "include/Storage/Arrays.hpp"
#include "Iterator.hpp"
#include "Submatrix.hpp"
#include "Math.hpp"
#include "Algorithms.hpp"
#include "Cond.hpp"

namespace axi
{

    template<typename M>
    struct Matrix_traits
    {
        using matrix_type = typename M::matrix_type;
    };

    template<typename C, typename T, typename A, typename Alloc = std::allocator<T>>
    class Base
    {
        static_assert (std::is_arithmetic<T>::value || is_complex<T>::value, "Uncorrect type");

    private:

        using self_type               = Base<C, T, A, Alloc>;

    public:

        using traits_type             = Matrix_traits<self_type>;
        using matrix_type             = C;

        using array_type              = A;
        using value_type              = T;
        using reference               = T&;
        using const_reference         = const T&;
        using pointer                 = T*;
        using const_pointer           = const T*;
        using iterator                = matrix_iterator<pointer>;
        using const_iterator          = matrix_iterator<const_pointer>;
        using reverse_iterator        = matrix_reverse_iterator<iterator>;
        using col_iterator            = matrix_col_iterator<iterator>;
        using row_iterator            = matrix_row_iterator<iterator>;
        using diag_iterator           = matrix_diag_iterator<iterator>;
        using difference_type         = typename array_type::difference_type;
        using size_type               = std::size_t;
        using allocator_type          = Alloc;


        Base();

        Base(const allocator_type& alloc) :
            data_(alloc) { }

        Base(size_type req_rows, size_type req_cols, const allocator_type& alloc = allocator_type());


        Base(const Matrix_size& mat_size, const allocator_type& alloc);

        Base(const Base& copy);

        Base(Base&& move);

        Base& operator=(const Base& rhs);

        Base& operator=(Base&& rhs);

        allocator_type get_allocator() const noexcept;

        size_type rows() const noexcept;

        size_type cols() const noexcept;

        Matrix_size size() const noexcept;

        bool empty() const noexcept;

        reference operator[](size_type n);

        const_reference operator[](size_type n) const;

        virtual reference operator()(size_type i, size_type j);

        virtual const_reference operator()(size_type i, size_type j) const;

        virtual reference at(size_type i, size_type j);

        const_reference at(size_type i, size_type j) const;

        pointer data() noexcept;

        const_pointer data() const noexcept;

        iterator begin();

        iterator end();

        const_iterator cbegin() const;

        const_iterator cend() const;

        reverse_iterator rbegin();

        reverse_iterator rend();

        col_iterator begin_col(size_type n);

        col_iterator end_col(size_type n);

        row_iterator begin_row(size_type n_row);

        row_iterator end_row(size_type n_row);

        diag_iterator begin_diag();

        diag_iterator end_diag();

        value_type det();

        Submatrix<self_type> submatrix(const Index<Range>& row_index, const Index<Range>& col_index);

        Submatrix<self_type> submatrix(const Index<Selected>& selected_rows, const Index<Selected>& selecteed_cols);

        void clear();

        void swap_rows(size_type row_1, size_type row_2);

        void swap_rows(Base& other, size_type row_1, size_type row_2);

        void swap_cols(size_type col_1, size_type col_2);

        void swap_cols(Base& other, size_type col_1, size_type col_2);

        Base<C, T, A, Alloc>& operator+=(const Base<C, T, A, Alloc>& rhs);

        Base<C, T, A, Alloc>& operator-=(const Base<C, T, A, Alloc>& rhs);

        Base<C, T, A, Alloc>& operator*=(const Base<C, T, A, Alloc>& rhs);

        Base<C, T, A, Alloc>& operator*=(const value_type& rhs);

    protected:

        void set_size(const Matrix_size& mat_size);

        size_type get_new_size(size_type old_size, size_type new_size);

        void set_array(const Unbounded_array<T> &data);

        template<typename I>
        void swap_elems(I first_1, I last_1, I first_2, I last_2);

        void copy_from_other(Base& other);

        void copy_from_other(Base& other, size_type r, size_type c);

        array_type data_;

    private:

        Matrix_size size_;
    };
}

#endif // BASE_HPP
