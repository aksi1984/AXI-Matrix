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
    }

    ////////////////////////////////////////
    ///
    ///
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

} // namespace linarg

#endif // SPARSE_MATRIX_TCC
