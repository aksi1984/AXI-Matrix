#ifndef MATRIX_BASE_HPP
#define MATRIX_BASE_HPP

#include "Base.tcc"
#include "Arrays.hpp"
#include "Diagvec.hpp"
#include "Trivec.hpp"
#include "Random.hpp"
#include "Operations.hpp"

namespace linarg
{
    template<typename Type, typename T>
    class Matrix_base : public Base<Type, T, Unbounded_array<T>>
    {
    public:

        using base            = Base<Type, T, Unbounded_array<T>>;
        using self_type       = Matrix_base<Type, T>;
        using matrix_type     = typename base::matrix_type;

        using value_type      = typename base::value_type;
        using reference       = typename base::reference;
        using const_reference = typename base::const_reference;
        using pointer         = typename base::pointer;
        using const_pointer   = typename base::const_pointer;
        using size_type       = typename base::size_type;
        using allocator_type  = typename base::allocator_type;

        Matrix_base(const allocator_type& alloc = allocator_type());


        /*!
         * \brief Create a matrix with defined size.
         * \param reqRows number of rows.
         * \param reqCols number of cols.
         * \param alloc type of allocator.
         */
        explicit Matrix_base(size_type reqRows, size_type reqCols, const allocator_type& alloc = allocator_type());


        /*!
         * \brief Create a matrix with defined size
         * \param mat_size object of Matrix_size.
         * \param alloc type of allocator.
         */
        explicit Matrix_base(const Matrix_size& mat_size, const allocator_type& alloc = allocator_type());


        /*!
         * \brief Create a matrix with defined size and fill elements with random numbers.
         * \tparam R type of random.
         * \param mat_size object of Matrix_size.
         * \param random object of Random class.
         */
        explicit Matrix_base(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, const allocator_type& alloc = allocator_type());

#if __cplusplus >= 201103L

#endif

        /*!
         * \brief Create a matrix from function wrapper, functor or lambda function.
         * \param rows numer of matrix rows.
         * \param cols number of matrix cols.
         * \param function function wrapper, functor or lambda function.
         */
        Matrix_base(size_type rows, size_type cols, std::function<T()> function);

        /*!
         * \brief Create a matrix from function wrapper, functor or lambda function.
         * \param size matrix size class.
         * \param function function wrapper, functor or lambda function.
         */
        explicit Matrix_base(const Matrix_size& size, std::function<T()> function, const allocator_type& alloc = allocator_type());

        /*!
         * \brief Matrix copy constructor.
         * \param copy other matrix.
         */
        Matrix_base(const Matrix_base& copy);


#if __cplusplus >= 201103L

        /*!
         * \brief Matrix move constructor.
         * \param move other matrix.
         */
        Matrix_base(Matrix_base&& move);

#endif

        /*!
         * \brief Matrix assignment operator from other object.
         * \param rhs Other matrix.
         */
        Matrix_base& operator=(const Matrix_base& rhs);

        /*!
         * \brief Matrix assignment operator from stl vector<T>.
         * \param rhs stl vector<T>.
         */
        Matrix_base& operator=(const std::vector<int>& rhs);

        Matrix_base& operator=(Matrix_base&& rhs);


#if __cplusplus >= 201103L

#endif

        /*!
         * \brief Matrix assignment operator from random class;
         * \tparam R random type.
         * \param random random class.
         */
        Matrix_base& operator=(rd::Random_base<typename traits::Get_type<traits::is_complex<T>::value, T>::type >* random);

        bool is_square() const noexcept;

        /*!
         * \brief Return submatrix.
         * \param init Submatrix initializer.
         */
        Matrix_base<Type, T> submat(size_type beg_row, size_type beg_col, size_type rows, size_type cols);

        /*!
         * \brief Return vector of values from lower or upper triangular.
         */
        template<typename TriType>
        Trivec<self_type, TriType> triangle();

        /*!
         * \brief Check if Matrix is unit.
         */
        Diagvec<self_type> diagonal(int n = 0);

        /*!
         * \brief Fill Matrix zeros values.
         */
        void fill_zeros();

        /**
         * @brief transpose the matrix
         */
        void transpose();

        /**
         * @brief resize the matrix
         * @param new_cols number of new cols
         * @param new_rows number of new rows
         *
         * @note if the matrix is empty, the function
         * does not perform any operations.
         */
        void resize(size_type new_cols, size_type new_rows);

        /**
         * @brief resize the matrix
         * @param matrix_size matrix size class
         *
         * @note if the matrix is empty, the function
         * does not perform any operations.
         */
        void resize(const Matrix_size& matrix_size);

    protected:

        template<typename U = typename traits::Get_type<traits::is_complex<T>::value, T>::type>
        void fill(U value, std::false_type);

        template<typename U = typename traits::Get_type<traits::is_complex<T>::value, T>::type>
        void fill(U value, std::true_type);

    private:

        template<typename R>
        void fill_random(R random);

        virtual void to_fill_random(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random);

        void fill_random(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, std::true_type);

        virtual void fill_random(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, std::false_type);

        void copy(const Base<Type, T, Unbounded_array<T>>& matrix_base);

        template<typename VectorType>
        void copy(const VectorType& vector);

        template<typename ContainerType>
        void copy_from_container(ContainerType container);

        template<typename Tp, typename U>
        void copy_from_other_mat(const Matrix_base<Tp, U>& mat);

        Diagvec<self_type> get_diagvec(int n);

    };

} // namespace lianrg

#endif // MATRIX_BASE_HPP
