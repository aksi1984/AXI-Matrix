#ifndef DIAGVEC_HPP
#define DIAGVEC_HPP

#include "include/Storage/Arrays.hpp"

namespace axi
{
    template<typename M>
    class Diagonal_elems : public Array<typename M::value_type>
    {
    public:

        using base_type     = Array<typename M::value_type>;
        using value_type    = typename M::value_type;
        using size_type     = typename M::size_type;


        Diagonal_elems(size_type size, const M& mat, size_type row, size_type col) :
            base_type(size)
        {
            make_vec(mat, row, col);
        }

        friend std::ostream& operator<<(std::ostream& os, Diagonal_elems diagvec)
        {
            for(size_type i = 0; i < diagvec.size(); ++i)
            {
                os << diagvec[i] << ' ';
            }

            return os;
        }

    private:

        void make_vec(const M& mat, size_type row, size_type col)
        {
            for(std::size_t i = 0; i < base_type::size() ; ++i, ++row, ++col)
            {
                base_type::operator[](i) = mat(row, col);
            }
        }
    };
}

#endif // DIAGVEC_HPP
