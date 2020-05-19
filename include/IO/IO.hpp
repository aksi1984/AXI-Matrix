#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <iomanip>

#include "include/Vector/Vector.hpp"
#include "include/Matrix/Matrix.hpp"
#include "include/Matrix/Sparse_matrix.hpp"
#include "include/Matrix/Triangular_matrix.hpp"
#include "include/Matrix/Submatrix.hpp"
#include "include/Tensor/Cube.hpp"
#include "include/Tensor/Cube_subview.hpp"

namespace axi
{
    namespace detail
    {
        template<typename Char, typename Traits, typename M>
        void print(std::basic_ostream<Char, Traits>& os, const M& mat)
        {
            for(std::size_t i = 0; i < mat.rows(); ++i)
            {
                for(std::size_t j = 0; j < mat.cols(); ++j)
                {
                    os << mat(i, j) << ' ';
                }

                os << '\n';
            }
        }

    } // namespace detail


    template<typename Char, typename Traits, typename T>
    std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, const Vector<T>& vec)
    {
        for(std::size_t i = 0; i < vec.size(); ++i)
        {
            os << vec[i];

            if(i < vec.size() - 1)
            {
                os << ", ";
            }
        }

        os << "}";

        return os;
    }


    template<typename Char, typename Traits, typename T>
    std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, Matrix<T> mat)
    {
        detail::print(os, mat);

        return os;
    }

    template<typename Char, typename Traits, typename T>
    std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, Sparse_matrix<T> mat)
    {
        std::size_t zeros = algo::zeros(mat);
        std::size_t non_zeros = mat.size().total() - zeros;
        double density = (static_cast<double>(non_zeros) / static_cast<double>(mat.size().total())) * 100.0;

        std::ostringstream ost;

        ost << std::fixed << "Density" << std::setw(4)
            << std::setfill(' ') << ":" << density << "%" << "Non zeros"
            << std::setw(2) << std::setfill(' ') << ":" << non_zeros;

        os << ost.str() << "\n\n";

        detail::print(os, mat);

        return os;
    }

    template<typename Char, typename Traits, typename T, typename Tr>
    std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, const Triangular_matrix<T, Tr>& mat)
    {
        using triangular_fill_type = Tr;
        std::string triangular_fill_type_str = ( std::is_same<triangular_fill_type, Upper>::value ? "upper" : (std::is_same<triangular_fill_type, Lower>::value ? "lower" : "diagonal") );

        os << triangular_fill_type_str << "\n\n";

        detail::print(os, mat);

        return os;
    }

    template<typename Char, typename Traits, typename M>
    std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, const Submatrix<M>& sub)
    {
        os << "Submatrix: ";

        auto variant = sub.indexes();

        std::visit(visitor::Index_IO_visitor<Char, Traits>{os}, variant);

        os << "\n\n";

        detail::print(os, sub);

        return os;
    }

    template<typename Char, typename Traits, typename M>
    std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, Cube<M> cube)
    {
        for(std::size_t i = 0; i < cube.slices(); ++i)
        {
            os << "Slice " << i << ":" << "\n\n";
            detail::print(os, cube[i]);
            os << "\n\n";
        }

        return os;
    }

    template<typename Char, typename Traits, typename C, typename L>
    std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, Cube_subview<C, L> subview)
    {
        std::string fill_type_str = ( std::is_same_v<L, Row> ? "rows" : "cols" );

        os << "Cube subview<" << fill_type_str << "> {" << subview.slices() << "}\n\n";

        for(std::size_t i = 0; i < subview.slices(); ++i)
        {
            os << "Slice " << i << ":" << "\n\n";
            detail::print(os, subview[i]);
            os << "\n\n";
        }

        return os;
    }

} // namespace linalg

#endif // IO_HPP
