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
    Sparse_matrix<T>::Sparse_matrix(size_type req_rows, size_type req_cols, double dens, Random<T> random, const allocator_type& alloc) :
        base(req_rows, req_cols, alloc)
    {
        LINARG_CHECK(((density_ >= 0.0) && (density_ <= 100.0)), Invalid_density(density_))

        Array<std::size_t> locations = random_locations(base::size(), dens);

        random.apply_size(Matrix_size{req_rows, req_cols});
        auto values = random.get();

        for(size_type i = 0; i < locations.size(); ++i)
        {
            base::operator[](locations[i]) = values[i];
        }
    }

} // namespace linarg

#endif // SPARSE_MATRIX_TCC
