#ifndef MATRIX_TCC
#define MATRIX_TCC

#include "Matrix.hpp"
#include "Container.hpp"
#include "Matrix_initializer.tcc"

namespace axi
{
    template<typename T>
    Matrix<T>::Matrix(const Matrix_size& req_size, const allocator_type& alloc) :
        base(req_size, alloc) { }

    template<typename T>
    Matrix<T>::Matrix(size_type reqRows, size_type reqCols, const allocator_type& alloc) :
        base(reqRows, reqCols, alloc) { }

    template<typename T>
        template<typename U, typename>
        Matrix<T>::Matrix(const Matrix_size& req_size, Random<U> random, const allocator_type& alloc) :
            Matrix{req_size.rows_, req_size.cols_, alloc}
        {
            random.set_size(req_size);
            Array<T> values = random.get(std::is_arithmetic<T>{});
            size_type count = 0;

            for(auto& x : *this) x = values[count++];
        }

    template<typename T>
        template<typename U, typename>
        Matrix<T>::Matrix(size_type req_rows, size_type req_cols, Random<U> random, const allocator_type& alloc) :
            Matrix(Matrix_size{req_rows, req_cols}, random, alloc) { }

    template<typename T>
    Matrix<T>::Matrix(List<value_type> list, const allocator_type& alloc) :
        base(1, list.size(), alloc)
    {
        copy_from_list(list);
    }

    template<typename T>
    Matrix<T>::Matrix(List_of_lists<value_type> list, const allocator_type& alloc) :
        base(alloc)
    {
        copy_from_container(list);
    }

    template<typename T>
    Matrix<T>::Matrix(const std::string& expr, const allocator_type& alloc) :
        base(alloc)
    {
        Expression<T> expression(expr);
        expression.start();
        vector_of_vectors<value_type> result = expression.get();

        copy_from_container(result);
    }

    template<typename T>
        template<typename Function, typename>
        Matrix<T>::Matrix(const Matrix_size& size, Function function, const allocator_type& alloc) :
            base(size.rows_, size.cols_, alloc)
        {
            fill_from_function(function);
        }

    template<typename T>
        template<typename Function, typename>
        Matrix<T>::Matrix(size_type req_rows, size_type req_cols, Function function, const allocator_type& alloc) :
            Matrix{Matrix_size{req_rows, req_cols}, function, alloc} { }

    template<typename T>
    Matrix<T>::Matrix(const Vector<T>& vector, const allocator_type& alloc) :
        base(1, vector.size(), alloc)
    {
        copy(vector);
    }

    template<typename T>
    Matrix<T>::Matrix(const std::vector<T>& vector, const allocator_type& alloc) :
        base(1, vector.size(), alloc)
    {
        copy(vector);
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix<T>& copy) :
        base(copy) { }

    template<typename T>
    Matrix<T>::Matrix(Matrix<T>&& move) :
        base(std::move(move)) { }

    template<typename T>
    Matrix<T>&
    Matrix<T>::operator=(const Matrix<T>& rhs)
    {
        base::operator=(rhs);

        return *this;
    }

    template<typename T>
    Matrix<T>&
    Matrix<T>::operator=(Matrix<T>&& rhs)
    {
        base::operator=(std::move(rhs));

        return *this;
    }

    template<typename T>
        template<typename U, typename>
        Matrix<T>&
        Matrix<T>::operator=(Random<U> random)
        {
            LINALG_CHECK(std::holds_alternative<Matrix_size>(random.size()), Bad_constructor{})

            if(Matrix_size new_size = std::get<0>(random.size()); new_size.total() != base::size().total())
            {
                Matrix temp{new_size};
                *this = temp;
            }

            Array<T> values = random.get(std::is_arithmetic<T>{});
            size_type count = 0;

            for(auto& x : *this) x = values[count++];

            return *this;
        }

    template<typename T>
    Matrix<T>&
    Matrix<T>::operator=(const std::vector<int>& rhs)
    {
        base::resize(Matrix_size(1, rhs.size()));
        copy(rhs);

        return *this;
    }

    template<typename T>
    Matrix<T>&
    Matrix<T>::operator=(List<value_type> list)
    {
        base::resize(Matrix_size(1, list.size()));
        copy_from_list(list);

        return *this;
    }

    template<typename T>
    Matrix<T>&
    Matrix<T>::operator=(List_of_lists<value_type> list)
    {
        copy_from_container(list);
        return *this;
    }

    template<typename T>
    void
    Matrix<T>::fill_ones()
    {
        base::fill(1, is_complex<T>{});
    }

    template<typename T>
    void
    Matrix<T>::resize_rows(size_type new_rows)
    {
        base::resize(base::cols(), new_rows);
    }

    template<typename T>
    void
    Matrix<T>::resize_cols(size_type new_cols)
    {
        base::resize(new_cols, base::rows());
    }

    template<typename T>
    void
    Matrix<T>::insert_row(size_type position, value_type value)
    {
        Matrix<value_type> mat(base::rows() + 1, base::cols(), base::get_allocator());

        size_type count = 0;

        for(size_type i = 0; i < mat.rows(); ++i)
        {
            if( (i < position) || (i > position))
            {
                algo::copy(base::begin_row(count), base::end_row(count), mat.begin_row(i));
                count++;
            }
            else if(i == position)
            {
                algo::copy(mat.begin_row(i), mat.end_row(i), value);
            }
        }

        *this = mat;
    }

    template<typename T>
    void
    Matrix<T>::insert_rows(size_type position, base other)
    {
        Matrix<value_type> mat(base::rows() + other.rows(), base::cols(), base::get_allocator());

        size_type count_1 = 0;
        size_type count_2 = 0;
        size_type length = other.rows() + position;

        for(size_type i = 0; i < mat.rows(); ++i)
        {
            if( (((i <= position - 1) || (i > length - 1 )) && (position != 0)) ||
                (!((i >= position) && (i <= length - 1)) && (position == 0)) )
            {
                algo::copy(base::begin_row(count_1), base::end_row(count_1), mat.begin_row(i));

                count_1++;
            }
            else
            {
                algo::copy(other.begin_row(count_2), other.end_row(count_2), mat.begin_row(i));
                count_2++;
            }
        }

        *this = mat;
    }

    template<typename T>
    void
    Matrix<T>::insert_col(size_type position, value_type value)
    {
        Matrix<value_type> mat(base::rows(), base::cols() + 1, base::get_allocator());

        size_type count = 0;

        for(size_type i = 0; i < mat.cols(); ++i)
        {
            if( (i < position) || (i > position) )
            {
                algo::copy(base::begin_col(count), base::end_col(count), mat.begin_col(i));
                count++;
            }
            else if(i == position)
            {
                algo::copy(mat.begin_col(i), mat.end_col(i), value);
            }
        }

        *this = mat;
    }

    template<typename T>
    void
    Matrix<T>::insert_cols(size_type position, base other)
    {
        Matrix<value_type> mat(base::rows(), base::cols() + other.cols(), base::get_allocator());

        size_type count_1 = 0;
        size_type count_2 = 0;
        size_type length = other.cols() + position;

        for(size_type i = 0; i < mat.cols(); ++i)
        {
            if( (((i <= position - 1) || (i > length - 1 )) && (position != 0)) ||
                (!((i >= position) && (i <= length - 1)) && (position == 0)) )
            {
                algo::copy(base::begin_col(count_1), base::end_col(count_1), mat.begin_col(i));
                count_1++;
            }
            else
            {
                algo::copy(other.begin_col(count_2), other.end_col(count_2), mat.begin_col(i));
                count_2++;
            }
        }

        *this = mat;
    }

    template<typename T>
    void
    Matrix<T>::erase_row(size_type position)
    {
        Matrix<value_type> mat(base::rows() - 1, base::cols(), allocator_type());

        size_type count = 0;

        for(size_type i = 0; i < base::rows(); ++i)
        {
            if(i != position)
            {
                for(size_type j = 0; j < base::cols(); ++j)
                {
                    mat(count, j) = base::operator()(i, j); //base::data_[base::rows() * j + i];
                }

                count++;
            }
        }

        *this = mat;
    }

    template<typename T>
    void
    Matrix<T>::erase_col(size_type position)
    {
        Matrix<value_type> mat(base::rows(), base::cols() - 1, allocator_type());

        for(size_type i = 0; i < base::rows(); ++i)
        {
            size_type count = 0;

            for(size_type j = 0; j < base::cols(); ++j)
            {
                if(j != position)
                {
                    mat(i, count) = base::operator()(i, j);// data_[rows() * j + i];

                    count++;
                }
            }
        }

        *this = mat;
    }

    ///////////////////////////////////////////////////////


    template<typename T>
        template<typename Function>
        void Matrix<T>::fill_from_function(Function function)
        {
            for(auto& x : *this) x = function();
        }

    template<typename T>
        template<typename VectorType>
        void Matrix<T>::copy(const VectorType& vector)
        {
            std::copy(vector.cbegin(), vector.cend(), base::data_.begin());
        }

    template<typename T>
    void Matrix<T>::copy_from_list(List<value_type> list)
    {
        if(base::data_.size() != list.size())
        {
            base::data_.resize(list.size());
        }

        std::copy(list.begin(), list.end(), base::data_.begin());
    }

    template<typename T>
        template<typename ContainerType>
        void
        Matrix<T>::Matrix::copy_from_container(ContainerType container)
        {
            Matrix_initializer<value_type, ContainerType> mat_init(container);
            base::set_size(mat_init.get_size());
            base::set_array(mat_init.get_data());
        }
}

#endif // MATRIX_TCC
