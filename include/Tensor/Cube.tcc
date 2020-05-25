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
        template<typename FT>
        Subcube<typename Cube<Mat>::self_type, FT>
        Cube<Mat>::subcube(size_type elem_first, size_type elem_last)
        {
            return Subcube<self_type, FT>(*this, elem_first, elem_last);
        }

    template<typename Mat>
        template<typename FT>
        Subcube<typename Cube<Mat>::self_type, FT>
        Cube<Mat>::subcube(size_type elem)
        {
            return Subcube<self_type, FT>(*this, elem);
        }

    template<typename Mat>
    Cube<Mat>&
    Cube<Mat>::operator+=(const Cube& rhs)
    {
        Cube result = op::Plus<self_type, self_type, op::Op_cube>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename Mat>
    Cube<Mat>&
    Cube<Mat>::operator-=(const Cube& rhs)
    {
        Cube result = op::Minus<self_type, self_type, op::Op_cube>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename Mat>
    Cube<Mat>&
    Cube<Mat>::operator*=(const Cube& rhs)
    {
        Cube result = op::Multiplies<self_type, self_type, op::Op_cube>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename Mat>
    Cube<Mat>&
    Cube<Mat>::operator*=(mat_value_type rhs)
    {
        Cube result = op::Scalar_multiplies<self_type, mat_value_type, op::Op_cube>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename Mat>
    Cube<Mat>&
    Cube<Mat>::operator/=(mat_value_type rhs)
    {
        Cube result = op::Scalar_divide<self_type, mat_value_type, op::Op_cube>()(*this, rhs);
        *this = result;

        return result;
    }

} // namespace linalg

#endif // CUBE_TCC
