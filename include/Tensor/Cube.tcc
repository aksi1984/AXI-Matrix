#ifndef CUBE_TCC
#define CUBE_TCC

#include "Cube.hpp"

namespace axi
{
    template<typename Mat>
    Cube<Mat>::Cube() { }

    template<typename Mat>
    Cube<Mat>::Cube(const Matrix_size& req_size, size_type slices) :
        base(slices, Mat(req_size)) { }

    template<typename Mat>
    Cube<Mat>::Cube(size_type req_rows, size_type req_cols, size_type slices) :
        self_type(Matrix_size{req_rows, req_cols}, slices) { }

    template<typename Mat>
        template<typename U>
        Cube<Mat>::Cube(const Matrix_size& req_size, size_type slices, Random<U> random) :
            base(slices)
        {
            for(size_type i = 0; i < base::slices(); ++i)
            {
                base::operator[](i) = Mat(req_size, random);
            }
        }

    template<typename Mat>
        template<typename U>
        Cube<Mat>::Cube(const Matrix_size& req_size, double density, size_type slices, Random<U> random) :
            base(slices)
        {
            for(size_type i = 0; i < base::slices(); ++i)
            {
                base::operator[](i) = Mat(req_size, density, random);
            }
        }

    template<typename Mat>
        template<typename U>
        Cube<Mat>::Cube(const Square_matrix_size& req_size, size_type slices, Random<U> random) :
            base(slices)
        {
            for(size_type i = 0; i < base::slices(); ++i)
            {
                base::operator[](i) = Mat(req_size, random);
            }
        }

    template<typename Mat>
    Cube<Mat>::Cube(const Cube<Mat>& copy) :
        base(copy) { }

    template<typename Mat>
    Cube<Mat>::Cube(Cube<Mat>&& move) :
        base(std::move(move)) { }

    template<typename Mat>
    Cube<Mat>&
    Cube<Mat>::operator=(const Cube& rhs)
    {
        base::operator=(rhs);

        return *this;
    }

    template<typename Mat>
    Cube<Mat>&
    Cube<Mat>::operator=(Cube<Mat>&& rhs)
    {
        base::operator=(std::move(rhs));

        return *this;
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
