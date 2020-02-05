#ifndef MATRIX_BASE_TCC
#define MATRIX_BASE_TCC

#include "Unbounded_matrix.hpp"


namespace linarg
{
    template<typename Type, typename T>
    Unbounded_matrix<Type, T>::Unbounded_matrix(const allocator_type& alloc) :
        base(alloc) { }

    template<typename Type, typename T>
    Unbounded_matrix<Type, T>::Unbounded_matrix(size_type reqRows, size_type reqCols, const allocator_type& alloc) :
        base(reqRows, reqCols, alloc) { }

    template<typename Type, typename T>
    Unbounded_matrix<Type, T>::Unbounded_matrix(const Matrix_size& mat_size, const allocator_type& alloc) :
        base(mat_size, alloc) { }

    template<typename Type, typename T>
    Unbounded_matrix<Type, T>::Unbounded_matrix(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, const allocator_type& alloc) :
        base(random->mat_size(), alloc)
    {
        to_fill_random(random);
    }

    template<typename Type, typename T>
    Unbounded_matrix<Type, T>::Unbounded_matrix(size_type rows, size_type cols, std::function<T()> function) :
        base(rows, cols, allocator_type())
    {
        fill_random(function);
    }

    template<typename Type, typename T>
    Unbounded_matrix<Type, T>::Unbounded_matrix(const Matrix_size& size, std::function<T()> function, const allocator_type& alloc) :
        base(size.rows_, size.cols_, alloc)
    {
        fill_random(function);
    }

    template<typename Type, typename T>
    Unbounded_matrix<Type, T>::Unbounded_matrix(const Unbounded_matrix<Type, T>& copy) :
        base(copy) { }


    template<typename Type, typename T>
    Unbounded_matrix<Type, T>::Unbounded_matrix(Unbounded_matrix<Type, T>&& move) :
        base(std::move(move)) { }


    template<typename Type, typename T>
    Unbounded_matrix<Type, T>&
    Unbounded_matrix<Type, T>::operator=(const Unbounded_matrix<Type, T>& rhs)
    {
        base::operator=(rhs);

        return *this;
    }

    template<typename Type, typename T>
    Unbounded_matrix<Type, T>&
    Unbounded_matrix<Type, T>::operator=(Unbounded_matrix<Type, T>&& rhs)
    {
        base::operator=(std::move(rhs));
        rhs.clear();

        return *this;
    }

    template<typename Type, typename T>
    Unbounded_matrix<Type, T>&
    Unbounded_matrix<Type, T>::operator=(rd::Random_base<typename traits::Get_type<traits::is_complex<T>::value, T>::type >* random)
    {
        resize(random->mat_size());
        fill_random(random);

        return *this;
    }

    template<typename Type, typename T>
    bool
    Unbounded_matrix<Type, T>::is_square() const noexcept
    {
        return base::rows() == base::cols();
    }

    template<typename Type, typename T>
    Unbounded_matrix<Type, T>
    Unbounded_matrix<Type, T>::submat(size_type beg_rows, size_type beg_cols, size_type rows, size_type cols)
    {
        LINARG_CHECK((beg_rows < base::rows()) && (beg_cols < base::cols()), Out_of_bounds("Submat"))
        LINARG_CHECK((base::rows() > rows) && (base::cols()) > cols, Bad_size("Submat: submatrix size is greather than matrix"))
        LINARG_CHECK((beg_rows + rows < base::rows()) && (beg_cols + cols < base::cols()), Out_of_bounds("Submat"))

        Unbounded_matrix<Type, T> submatrix(rows, cols);

        for(size_type i = 0, x = beg_rows; i < submatrix.rows() ; ++i, ++x)
        {
            for(std::size_t j = 0, y = beg_cols; j < submatrix.cols(); ++j, ++y)
            {
                submatrix(i, j) = base::operator()(x, y);
            }
        }

        return submatrix;
    }

    template<typename Type, typename T>
        template<typename TriType>
        Trivec<typename Unbounded_matrix<Type, T>::self_type, TriType>
        Unbounded_matrix<Type, T>::triangle()
        {
            return Trivec<typename Unbounded_matrix<Type, T>::self_type, TriType>(*this);
        }

    template<typename Type, typename T>
    Diagvec<typename Unbounded_matrix<Type, T>::self_type>
    Unbounded_matrix<Type, T>::diagonal(int n)
    {
        return get_diagvec(n);
    }

    template<typename Type, typename T>
    void
    Unbounded_matrix<Type, T>::fill_zeros()
    {
        fill(0, traits::is_complex<T>{});
    }

    template<typename Type, typename T>
    void
    Unbounded_matrix<Type, T>::transpose()
    {
        algo::transpose(*this);
    }

    template<typename Type, typename T>
    void
    Unbounded_matrix<Type, T>::resize(size_type new_rows, size_type new_cols)
    {
        if( (new_rows == 0) && (new_cols == 0) )
        {
            base::clear();
        }
        else
        {
            Unbounded_matrix<Type, value_type> temp(new_rows, new_cols, base::get_allocator());

            size_type r_num = new_rows > base::rows() ? base::rows() : new_rows;
            size_type c_num = new_cols > base::cols() ? base::cols() : new_cols;

            base::copy_from_other(temp, r_num, c_num);

            *this = temp;
        }
    }

    template<typename Type, typename T>
    void
    Unbounded_matrix<Type, T>::resize(const Matrix_size& matrix_size)
    {
        resize(matrix_size.rows_, matrix_size.cols_);
    }

    /*template<typename T, typename C>
    Matrix<T, C>&
    Matrix<T, C>::operator*=(value_type scalar)
    {
        Matrix result = op::Scalar_multiplies<self_type, value_type>()(*this, scalar);
        *this = result;

        return *this;
    }

    template<typename T, typename C>
    Matrix<T, C>&
    Matrix<T, C>::operator/=(const Matrix<T, C>& rhs)
    {
        Matrix result = op::Scalar_divide<self_type, self_type>()(*this, rhs);
        *this = result;

        return *this;
    }*/

    ///////////////////////////////////////////////////////


    template<typename Type, typename T>
        template<typename U>
        void Unbounded_matrix<Type, T>::fill(U value, std::false_type)
        {
            for(auto& x : *this) x = value;
        }

    template<typename Type, typename T>
        template<typename U>
        void Unbounded_matrix<Type, T>::fill(U value, std::true_type)
        {
            for(auto& x : *this)
            {
                x.real(value);
                x.imag(value);
            }
        }

    template<typename Type, typename T>
    void
    Unbounded_matrix<Type, T>::to_fill_random(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random)
    {
        fill_random(random, traits::is_complex<T>{});
    }

    /*template<typename T, typename C>
        template<typename R>
        void Matrix<T, C>::fill_random(R random)
        {
            for(auto& x : *this) x = random();
        }*/

     template<typename Type, typename T>
     void
     Unbounded_matrix<Type, T>::fill_random(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, std::false_type)
     {
        for(auto& x : *this) x = random->get();
     }

    template<typename Type, typename T>
    void
    Unbounded_matrix<Type, T>::fill_random(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, std::true_type)
    {
        for(auto& x : *this)
        {
            x.real(random->get());
            x.imag(random->get());
        }
    }

    /*template<typename T, typename C>
    void Matrix<T, C>::copy(const Base<T, C>& matrix_base)
    {
        std::copy(matrix_base.cbegin(), matrix_base.cend(), this->begin());
    }*/

    template<typename Type, typename T>
        template<typename VectorType>
        void Unbounded_matrix<Type, T>::copy(const VectorType& vector)
        {
            std::copy(vector.cbegin(), vector.cend(), base::data_.begin());
        }


    /*template<typename T, typename C>
        template<typename ContainerType>
        void
        Matrix<T, C>::Matrix::copy_from_container(ContainerType container)
        {
            Matrix_initializer<value_type, ContainerType> mat_init(container);
            base::set_size(mat_init.get_size());
            base::set_array(mat_init.get_data());
        }*/

    template<typename Type, typename T>
        template<typename Tp, typename U>
        void Unbounded_matrix<Type, T>::copy_from_other_mat(const Unbounded_matrix<Tp, U>& copy)
        {
            for(size_type i = 0; i < base::rows(); ++i)
            {
                for(size_type j = 0; j < base::cols(); ++j)
                {
                    base::operator()(i, j) = copy(i, j);
                }
            }
        }


     template<typename Type, typename T>
     Diagvec<typename Unbounded_matrix<Type, T>::self_type>
     Unbounded_matrix<Type, T>::get_diagvec(int n)
     {
         int row_offset = 0;
         int col_offset = 0;

         row_offset = ( n < 0 ? std::abs(n) : 0 );
         col_offset = ( n < 0 ? 0 : n );

         if(row_offset > base::rows() - 1 || col_offset > base::cols() - 1)
         {
             throw std::range_error("row offset, or col offset index out of bounds");
         }

         int length = base::rows();

         if(n >= base::cols() - 2)
         {
             length = base::cols() - n;
         }

         if(n < 0)
         {
             length = base::rows() - std::abs(n);
         }

         return Diagvec<self_type>(length, *this, row_offset, col_offset);
     }

    // Ops

    /*template<typename T>
    Matrix_base<T> operator+(const Matrix_base<T>& lhs, const Matrix_base<T>& rhs)
    {
        using current_type = Matrix_base<T>;
        return  op::Plus<current_type, current_type>()(lhs, rhs);
    }

    template<typename T>
    Matrix_base<T> operator-(const Matrix_base<T>& lhs, const Matrix_base<T>& rhs)
    {
        using current_type = Matrix_base<T>;
        return op::Minus<current_type, current_type>()(lhs, rhs);
    }

    template<typename T>
    Matrix_base<T> operator*(const Matrix_base<T>& lhs, const Matrix_base<T>& rhs)
    {
        using current_type = Matrix_base<T>;
        return op::Multiplies<current_type, current_type>()(lhs, rhs);
    }

    template<typename T, typename C>
    Matrix<T, C> operator*(const Matrix<T, C>& lhs, T scalar)
    {
        using current_type = Matrix<T, C>;
        return op::Scalar_multiplies<current_type, T>()(lhs, scalar);
    }

    template<typename T, typename C>
    Matrix<T, C> operator/(const Matrix<T, C>& lhs, T scalar)
    {
        using current_type = Matrix<T, C>;
        return op::Scalar_divide<current_type, T>()(lhs, scalar);
    }

    template<typename T, typename C>
    bool operator==(const Matrix<T, C>& lhs, const Matrix<T, C>& rhs)
    {
        using type = Matrix<T, C>;
        return op::Equal<type, type>()(lhs, rhs);
    }*/


} // namespace linarg

#endif // MATRIX_BASE_TCC
