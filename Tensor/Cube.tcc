#ifndef CUBE_TCC
#define CUBE_TCC

#include "Cube.hpp"

namespace linalg
{
    template<typename Mat>
    Cube<Mat>::Cube(const allocator_type& alloc) :
        base(alloc) { }

    template<typename Mat>
    Cube<Mat>::Cube(const Matrix_size& req_size, size_type slices, const allocator_type& alloc) :
        base(slices, Mat(req_size), alloc) { }

    template<typename Mat>
    Cube<Mat>::Cube(size_type req_rows, size_type req_cols, size_type slices, const allocator_type& alloc) :
        self_type(Matrix_size{req_rows, req_cols}, slices, alloc) { }

    template<typename Mat>
        template<typename U>
        Cube<Mat>::Cube(const Matrix_size& req_size, size_type slices, Random<U> random, const allocator_type& alloc) :
            base(slices, alloc)
        {
            for(size_type i = 0; i < base::slices(); ++i)
            {
                base::operator[](i) = Mat(req_size, random);
            }
        }

    template<typename Mat>
        template<typename U>
        Cube<Mat>::Cube(const Matrix_size& req_size, double density, size_type slices, Random<U> random, const allocator_type& alloc) :
            base(slices, alloc)
        {
            for(size_type i = 0; i < base::slices(); ++i)
            {
                base::operator[](i) = Mat(req_size, density, random);
            }
        }

    template<typename Mat>
        template<typename U>
        Cube<Mat>::Cube(const Square_matrix_size& req_size, size_type slices, Random<U> random, const allocator_type& alloc) :
            base(slices, alloc)
        {
            for(size_type i = 0; i < base::slices(); ++i)
            {
                base::operator[](i) = Mat(req_size, random);
            }
        }

    template<typename Mat>
    std::vector<typename Cube<Mat>::mat_value_type>
    Cube<Mat>::row(size_type row, size_type slice)
    {
        for(auto x : base::operator[](slice))
        {

        }
    }

} // namespace linalg

#endif // CUBE_TCC
