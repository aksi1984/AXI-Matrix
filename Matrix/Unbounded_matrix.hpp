#ifndef UNBOUNDED_MATRIX_HPP
#define UNBOUNDED_MATRIX_HPP

#include "Base.tcc"
#include "Arrays.hpp"
#include "Diagvec.hpp"
#include "Trivec.hpp"
#include "Random.hpp"
#include "Operations.hpp"

namespace linarg
{
    template<typename Type, typename T>
    class Unbounded_matrix : public Base<Type, T, Unbounded_array<T>>
    {
    public:

        using base            = Base<Type, T, Unbounded_array<T>>;
        using self_type       = Unbounded_matrix<Type, T>;
        using matrix_type     = typename base::matrix_type;

        using value_type      = typename base::value_type;
        using reference       = typename base::reference;
        using const_reference = typename base::const_reference;
        using pointer         = typename base::pointer;
        using const_pointer   = typename base::const_pointer;
        using size_type       = typename base::size_type;
        using allocator_type  = typename base::allocator_type;

        Unbounded_matrix(const allocator_type& alloc = allocator_type());

        explicit Unbounded_matrix(size_type reqRows, size_type reqCols, const allocator_type& alloc = allocator_type());

        explicit Unbounded_matrix(const Matrix_size& mat_size, const allocator_type& alloc = allocator_type());

        explicit Unbounded_matrix(Random_ptr<typename traits::Get_type<traits::is_complex<T>::value, T>::type> random, const allocator_type& alloc = allocator_type());

        Unbounded_matrix(size_type rows, size_type cols, std::function<T()> function);

        explicit Unbounded_matrix(const Matrix_size& size, std::function<T()> function, const allocator_type& alloc = allocator_type());

        Unbounded_matrix(const Unbounded_matrix& copy);

        Unbounded_matrix(Unbounded_matrix&& move);

        Unbounded_matrix& operator=(const Unbounded_matrix& rhs);

        Unbounded_matrix& operator=(const std::vector<int>& rhs);

        Unbounded_matrix& operator=(Unbounded_matrix&& rhs);

        Unbounded_matrix& operator=(rd::Random_base<typename traits::Get_type<traits::is_complex<T>::value, T>::type >* random);

        bool is_square() const noexcept;

        Unbounded_matrix<Type, T> submat(size_type beg_row, size_type beg_col, size_type rows, size_type cols);

        template<typename TriType>
        Trivec<self_type, TriType> triangle();

        Diagvec<self_type> diagonal(int n = 0);

        void fill_zeros();

        void transpose();

        void resize(size_type new_cols, size_type new_rows);

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
        void copy_from_other_mat(const Unbounded_matrix<Tp, U>& mat);

        Diagvec<self_type> get_diagvec(int n);

    };

} // namespace lianrg

#endif // UNBOUNDED_MATRIX_HPP