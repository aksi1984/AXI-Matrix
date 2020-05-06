#ifndef GENERATED_HPP
#define GENERATED_HPP

#include "include/Vector/Vector.hpp"
#include "Matrix.hpp"

namespace linalg
{
    template<typename T>
    Matrix<T> make_band(const Vector<T>& diag, const Vector<T>& upper, const Vector<T>& lower)
    {
        Matrix<T> mat(diag.size(), diag.size());

        for(std::size_t i = 0; i < mat.rows(); ++i)
        {
            mat(i, i) = diag[i];

            if(i < mat.rows())
            {
                mat(i + 1, i) = lower[i];

            }

            if(i + 1 < mat.rows())
            {
                mat(i, i + 1) = upper[i];
            }
        }

        return mat;
    }

    enum Triangle_type
    {
        Lower,
        Upper
    };

    template<typename T>
    void transform_to_triangle(Matrix<T>& mat, Triangle_type type)
    {
        for(std::size_t i = 0; i < mat.rows(); ++i)
        {
            for(std::size_t j = 0; j < mat.cols(); ++j)
            {
                bool cond = ( type == Triangle_type::Lower ? j > i : j < i );

                if(cond)
                {
                    mat(j, i) = 0;
                }
            }
        }
    }

    template<typename T>
    Matrix<T> make_symmetric(const Vector<T>& diag, const Vector<T>& triangle)
    {        
        LINALG_CHECK( (triangle.size() == (( std::pow(diag.size(), 2) - diag.size()) / 2)),
                      Bad_size("Bad size of triangle vector") )

        Matrix<T> mat = make_diagonal(diag);

        std::size_t count = 0;

        for(std::size_t i = 0; i < mat.rows(); ++i)
        {
            for(std::size_t j = 0; j < mat.cols(); ++j)
            {
                if(j > i)
                {
                    mat(i, j) = triangle[count];
                    mat(j, i) = triangle[count];

                    if(count < triangle.size())
                    {
                        count++;
                    }
                }
            }
        }

        return mat;
    }

    template<typename T>
    Matrix<T> make_toeplitz(const Vector<T>& vector)
    {
        Matrix<T> mat(vector.size(), vector.size());

        std::size_t init = 0;
        std::size_t count;

        bool is_min_index = true;
        bool is_max_index = false;

        for(std::size_t i = 0; i < mat.rows(); ++i)
        {
            count = init;

            for(std::size_t j = 0; j < mat.cols(); ++j)
            {
                mat(i, j) = vector[count];

                if(count == 0)
                {
                    is_min_index = true;
                    is_max_index = false;
                }

                if(count == vector.size() - 1)
                {
                    is_max_index = true;
                    is_min_index = false;
                }

                if(is_min_index)
                {
                    count++;
                }
                else if(is_max_index)
                {
                    count--;
                }
            }

            init++;

            is_max_index = true;
            is_min_index = false;
        }

        return mat;
    }

    template<typename T>
    Matrix<T> make_vandermonde(const Vector<T>& vec, double max_exponent)
    {
        Matrix<T> mat(vec.size(), max_exponent);

        for(std::size_t i = 0; i < mat.rows(); ++i)
        {
            for(std::size_t j = 0; j < mat.cols(); ++j)
            {
                mat(i, j) = std::pow(vec[i], j);
            }
        }

        return mat;
    }


} // namespace axi

#endif // GENERATED_HPP
