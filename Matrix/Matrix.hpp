#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <functional>
#include <complex>

//#include "Diagvec.hpp"
//#include "Trivec.hpp"
#include "Expression.hpp"
#include "Matrix_initializer.hpp"
//#include "Operations.hpp"
//#include "Random.hpp"
#include "Matrix_base.tcc"


namespace linarg
{

    /*! \brief Dense matrix template class for values \cT.
     *
     * \tparam T the types of stored objects in the matrix.
     * \tparam Alloc type of allocator, default is std::allocator<T>.
     * \tparam A type of storage array, default is Unbounded_array<T, Alloc>.
     *
     * If you use a std::string or const char* as the stord objects, don't try
     * to do calculations on the matrix.
     */
    template<typename T>
    class Matrix : public Matrix_base<Dense_tag, T>
    {
        static_assert (std::is_arithmetic<T>::value || traits::is_complex<T>::value, "Uncorrect type");

    public:

        using base            = Matrix_base<Dense_tag, T>;
        using self_type       = Matrix<T>;
        using matrix_type     = typename base::matrix_type;

        using value_type      = typename base::value_type;
        using reference       = typename base::reference;
        using const_reference = typename base::const_reference;
        using pointer         = typename base::pointer;
        using const_pointer   = typename base::const_pointer;
        using size_type       = typename base::size_type;
        using allocator_type  = typename base::allocator_type;


        /*!
         * \brief Create a matrix with size(0, 0).
         */
        Matrix() = default;


        /*!
         * \brief Create a matrix with defined size.
         * \param reqRows number of rows.
         * \param reqCols number of cols.
         * \param alloc type of allocator.
         */
        explicit Matrix(size_type reqRows, size_type reqCols, const allocator_type& alloc = allocator_type());


        /*!
         * \brief Create a matrix with defined size
         * \param mat_size object of Matrix_size.
         * \param alloc type of allocator.
         */
        explicit Matrix(const Matrix_size& mat_size, const allocator_type& alloc = allocator_type());


        /*!
         * \brief Create a matrix with defined size and fill elements with random numbers.
         * \tparam R type of random.
         * \param mat_size object of Matrix_size.
         * \param random object of Random class.
         */
        explicit Matrix(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, const allocator_type& alloc = allocator_type());

#if __cplusplus >= 201103L

        /*!
         * \brief Create a matrix from initializer list.
         * \param list initializer list of elements.
         * \param alloc allocator
         */
        explicit Matrix(List<value_type> list, const allocator_type& alloc = allocator_type());


        /*!
         * \brief Create a matrix from list of initialiser list.
         * \param list of initializer list of elements.
         * \param alloc allocator.
         */
        explicit Matrix(List_of_lists<value_type> list, const allocator_type& alloc = allocator_type());

        explicit Matrix(const std::string& expr, const allocator_type& alloc = allocator_type());

#endif

        /*!
         * \brief Create a matrix from function wrapper, functor or lambda function.
         * \param rows numer of matrix rows.
         * \param cols number of matrix cols.
         * \param function function wrapper, functor or lambda function.
         */
        Matrix(size_type rows, size_type cols, std::function<T()> function);

        /*!
         * \brief Create a matrix from function wrapper, functor or lambda function.
         * \param size matrix size class.
         * \param function function wrapper, functor or lambda function.
         */
        explicit Matrix(const Matrix_size& size, std::function<T()> function, const allocator_type& alloc = allocator_type());

        /*!
         * \brief Create a matrix from linarg Vector<T>.
         * \brief vector linarg Vector<T>
         * \param alloc allocator.
         */
        explicit Matrix(const Vector<T>& vector, const allocator_type& alloc = allocator_type{});

        /*!
         * \brief Create a matrix from stl vector<T>.
         * \brief vector stl vector<T>
         * \param alloc allocator.
         */
        explicit Matrix(const std::vector<T>& vector, const allocator_type& alloc = allocator_type{});

        /*!
         * \brief Matrix copy constructor.
         * \param copy other matrix.
         */
        Matrix(const Matrix& copy);

#if __cplusplus >= 201103L

        /*!
         * \brief Matrix move constructor.
         * \param move other matrix.
         */
        Matrix(Matrix&& move);


        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Matrix(const Matrix<U>& copy) = delete;

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Matrix(Matrix<U>&& move) = delete;

#endif

        /*!
         * \brief Matrix assignment operator from other object.
         * \param rhs Other matrix.
         */
        Matrix& operator=(const Matrix& rhs);

        Matrix& operator=(Matrix&& rhs);

        /*!
         * \brief Matrix assignment operator from stl vector<T>.
         * \param rhs stl vector<T>.
         */
        Matrix& operator=(const std::vector<int>& rhs);

        template<typename U>
        Matrix& operator=(const Matrix<U>& rhs) = delete;

        template<typename U>
        Matrix& operator=(Matrix<U>&& rhs) = delete;

#if __cplusplus >= 201103L

        /*!
         * \brief Matrix assignment operator from initializer list.
         * \param list Initializer list of elements.
         */
        Matrix& operator=(List<value_type> list);


        /*!
         * \brief Matrix assignment operator from list of initializer lists.
         * \param list List of initialiser lists.
         */
        Matrix& operator=(List_of_lists<value_type> list);

#endif

        /*!
         * \brief Matrix assignment operator from random class;
         * \tparam R random type.
         * \param random random class.
         */
        Matrix& operator=(rd::Random_base<typename traits::Get_type<traits::is_complex<T>::value, T>::type >* random);

        /*!
         * \brief Fill Matrix ones values.
         */
        void fill_ones();

        /**
         * @brief resize matrix at the given new size
         * @param new_rows new rows number
         */
        void resize_rows(size_type new_rows);

        /**
         * @brief resize matrix cols at the given new size
         * @param new_cols new cols number
         */
        void resize_cols(size_type new_cols);

        /**
         * @brief insert row in required position
         * @param position new row position
         * @param value
         *
         * @note if given position is out of range,
         * is thrown Out_of_range exception.
         */
        void insert_row(size_type position, value_type value = {});

        /**
         * @brief insert a few rows from the desired position
         * @param position
         * @param other
         *
         * @note if given position is out of range,
         * is throwing Out_of_range exception.
         */
        void insert_rows(size_type position, base other);

        /**
         * @brief insert col in required position
         * @param position new col position
         * @param value
         *
         * @note if given position is out of range,
         * is thrown Out_of_range exception.
         */
        void insert_col(size_type position, value_type value = {});

        /**
         * @brief insert a few cols from the desired position
         * @param position
         * @param other
         *
         * @note if given position is out of range,
         * is throwing Out_of_range exception.
         */
        void insert_cols(size_type position, base other);

        void erase_row(size_type position);

        void erase_col(size_type position);

    private:

        template<typename Function>
        void fill_from_function(Function function);

        template<typename VectorType>
        void copy(const VectorType& vector);

        void copy_from_list(List<value_type> list);

        template<typename ContainerType>
        void copy_from_container(ContainerType container);

        template<typename U>
        void copy_from_other_mat(const Matrix<U>& mat);

    };
}

#endif // MATRIX_HPP
