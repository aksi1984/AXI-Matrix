#ifndef MINOR_TCC
#define MINOR_TCC

#include "Minor.hpp"

namespace linarg
{
    template<typename M>
    Minor<M>::Minor(M mat, size_type n, const Minor_initializer& minor_init, const allocator_type& alloc) :
        base(minor_init.size(), alloc)
    {
        init_minor(mat, n, minor_init);
    }

    template<typename M>
    Minor<M>::Minor(const M& mat, const Minor_initializer& minor_init, const allocator_type& alloc) :
        base(minor_init.size(), alloc)
    {
        init(mat, minor_init);
    }

    template<typename M>
    bool
    Minor<M>::has_minor_value(size_type n, Container<size_type> array)
    {
        for(size_type i = 0; i < array.size(); ++i)
        {
            if(n == array[i])
            {
                return false;
            }
        }

        return true;
    }

    template<typename M>
    void
    Minor<M>::init(M mat, size_type n, const Minor_initializer& init)
    {
        init.dim() == Dimension::Row ? mat.erase_row(n) : mat.erase_col(n);
        base::copy_from_other(mat);
    }

    template<typename M>
    void
    Minor<M>::init(M mat, Minor_initializer init)
    {
        size_type row = 0;

        for(size_type i = 0; i < mat.rows(); ++i)
        {
            if(has_minor_value(i, init.n_rows()))
            {
                size_type col = 0;

                for(size_type j = 0; j < mat.cols(); ++j)
                {
                    if(has_minor_value(j, init.n_cols()))
                    {
                        base::operator()(row, col) = mat(i, j);

                        col++;
                    }
                }

                row++;
            }
        }
    }

} // namespace linarg

#endif // MINOR_TCC
