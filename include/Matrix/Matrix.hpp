#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <functional>
#include <complex>

#include "Expression.hpp"
#include "Matrix_initializer.hpp"
#include "Unbounded_matrix.tcc"


namespace linalg
{
    template<typename T>
    class Matrix : public Unbounded_matrix<tags::Dense_matrix_tag, T>
    {

    private:

        using self_type       = Matrix<T>;

    public:

        using base            = Unbounded_matrix<tags::Dense_matrix_tag, T>;
        using matrix_type     = typename base::matrix_type;
        using value_type      = typename base::value_type;
        using reference       = typename base::reference;
        using const_reference = typename base::const_reference;
        using pointer         = typename base::pointer;
        using const_pointer   = typename base::const_pointer;
        using size_type       = typename base::size_type;
        using allocator_type  = typename base::allocator_type;


        Matrix() = default;

        explicit Matrix(const Matrix_size& req_size, const allocator_type& alloc = allocator_type());

        explicit Matrix(size_type reqRows, size_type reqCols, const allocator_type& alloc = allocator_type());

        template<typename U, typename = std::enable_if_t<std::is_same_v<U, typename traits::Get_type<is_complex<T>::value, T>::type>>>
        explicit Matrix(size_type req_rows, size_type req_cols, Random<U> random, const allocator_type& alloc = allocator_type());

        template<typename U, typename = std::enable_if_t<std::is_same_v<U, typename traits::Get_type<is_complex<T>::value, T>::type>>>
        explicit Matrix(const Matrix_size& size, Random<U> random, const allocator_type& alloc = allocator_type{});

        Matrix(List<value_type> list, const allocator_type& alloc = allocator_type());

        Matrix(List_of_lists<value_type> list, const allocator_type& alloc = allocator_type());

        explicit Matrix(const std::string& expr, const allocator_type& alloc = allocator_type());

        template<typename Function, typename = std::enable_if_t<is_functor<Function>::value>>
        explicit Matrix(const Matrix_size& size, Function function, const allocator_type& alloc = allocator_type());

        template<typename Function, typename = std::enable_if_t<is_functor<Function>::value>>
        explicit Matrix(size_type rows, size_type cols, Function function, const allocator_type& alloc = allocator_type{});

        explicit Matrix(const Vector<T>& vector, const allocator_type& alloc = allocator_type{});

        Matrix(const std::vector<T>& vector, const allocator_type& alloc = allocator_type{});

        Matrix(const Matrix& copy);

        Matrix(Matrix&& move);

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Matrix(const Matrix<U>& copy) = delete;

        template<typename U, typename = std::enable_if_t<std::is_convertible_v<T, U>>>
        Matrix(Matrix<U>&& move) = delete;

        Matrix& operator=(const Matrix& rhs);

        Matrix& operator=(Matrix&& rhs);

        template<typename U, typename = std::enable_if_t<std::is_same_v<U, typename traits::Get_type<is_complex<T>::value, T>::type>>>
        Matrix& operator=(Random<U> rhs);

        Matrix& operator=(const std::vector<int>& rhs);

        template<typename U>
        Matrix& operator=(const Matrix<U>& rhs) = delete;

        template<typename U>
        Matrix& operator=(Matrix<U>&& rhs) = delete;

        Matrix& operator=(List<value_type> list);

        Matrix& operator=(List_of_lists<value_type> list);

        void fill_ones();

        void resize_rows(size_type new_rows);

        void resize_cols(size_type new_cols);

        void insert_row(size_type position, value_type value = {});

        void insert_rows(size_type position, base other);

        void insert_col(size_type position, value_type value = {});

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
