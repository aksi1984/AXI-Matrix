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
        zeros_(rows * cols) { }


    template<typename T>
    Sparse_matrix<T>::Sparse_matrix(const Matrix_size& size, const allocator_type& alloc) :
        Sparse_matrix<T>(size.rows_, size.cols_, alloc) { }

    template<typename T>
        template<typename U, typename>
        Sparse_matrix<T>::Sparse_matrix(size_type req_rows, size_type req_cols, double density, Random<U> random, const allocator_type& alloc) :
            base(req_rows, req_cols, alloc)
        {
            LINARG_CHECK(((density >= 0.0) && (density < 100.0)), Invalid_density(density))

            Array<std::size_t> locations = random_locations(base::size(), density);

            random.apply_size(Matrix_size{req_rows, req_cols});
            Array<T> values = random.get(std::is_arithmetic<T>{});

            for(size_type i = 0; i < locations.size(); ++i)
            {
                base::operator[](locations[i]) = values[i];
            }
        }

} // namespace linarg

#endif // SPARSE_MATRIX_TCC
