#ifndef SPARSE_MATRIX_TCC
#define SPARSE_MATRIX_TCC

#include "Sparse_matrix.hpp"

namespace linarg
{
    template<typename T>
    Sparse_matrix<T>::Sparse_matrix(const allocator_type& alloc) :
        base(alloc) { }

    template<typename T>
    Sparse_matrix<T>::Sparse_matrix(size_type rows, size_type cols, const allocator_type& alloc) :
        base(rows, cols, alloc),
        density_(),
        zeros_(rows * cols) { }


    template<typename T>
    Sparse_matrix<T>::Sparse_matrix(const Matrix_size& size, const allocator_type& alloc) :
        Sparse_matrix<T>(size.rows_, size.cols_, alloc) { }

    template<typename T>
    Sparse_matrix<T>::Sparse_matrix(rd::Rd_ptr<T> random, double dens, const allocator_type& alloc) :
        base(random->mat_size(), alloc),
        density_(dens)
    {
        LINARG_CHECK(((density_ >= 0.0) && (density_ <= 100.0)), Invalid_density(density_))

        fill_random(random, std::integral_constant<bool, false>{});
        check_values();
    }

    template<typename T>
    double
    Sparse_matrix<T>::Sparse_matrix::density() noexcept
    {
        check_density();

        return density_;
    }

    template<typename T>
    typename Sparse_matrix<T>::size_type
    Sparse_matrix<T>::zeros() noexcept
    {
        check_values();

        return zeros_;
    }

    template<typename T>
    typename Sparse_matrix<T>::size_type
    Sparse_matrix<T>::non_zeros() noexcept
    {
        check_values();

        return non_zeros_;
    }

    ////////////////////////////////////////

    template<typename T>
    void
    Sparse_matrix<T>::set_value(size_type i, size_type j, value_type value)
    {
        base::operator()(i, j) = value;
        check_values();
    }

    template<typename T>
    void
    Sparse_matrix<T>::fill_random(rd::Rd_ptr<T> random, std::false_type)
    {
        Array<std::size_t> locations = rd::random_locations(base::size(), density_);

        for(size_type i = 0; i < locations.size(); ++i)
        {
            base::operator[](locations[i]) = random->get();
        }
    }

    template<typename T>
    void
    Sparse_matrix<T>::check_values()
    {
        size_type zeros_count = 0;
        size_type non_zeros_count = 0;

        for(auto x : *this)
        {
            if(x == 0)
            {
                zeros_count++;
            }
            else
            {
                non_zeros_count++;
            }
        }

        zeros_ = zeros_count;
        non_zeros_ = non_zeros_count;
    }

    template<typename T>
    void
    Sparse_matrix<T>::check_density()
    {
        density_ = (static_cast<double>(non_zeros()) / static_cast<double>(base::size().total())) * 100.0;
    }

} // namespace linarg

#endif // SPARSE_MATRIX_TCC
