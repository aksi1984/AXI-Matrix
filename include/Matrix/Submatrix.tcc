#ifndef MINOR_TCC
#define MINOR_TCC

#include "Submatrix.hpp"

namespace linalg
{

    template<typename M>
    Submatrix<M>::Submatrix(const M& mat, const Index<Range>& row_index, const Index<Range>& col_index) :
        base(row_index.size(), col_index.size()),
        indexes_{std::pair{row_index, col_index}}
    {
        fill(row_index, col_index, mat);
    }

    template<typename M>
    Submatrix<M>::Submatrix(const M& mat, const Index<Selected> &selected_rows, const Index<Selected> &selected_cols) :
        base(mat.rows() - selected_rows.size(), mat.cols() - selected_cols.size()),
        indexes_{std::pair{selected_rows, selected_cols}}
    {
        fill(selected_rows, selected_cols, mat);
    }

    template<typename M>
    std::size_t
    Submatrix<M>::init_size(const Index<Selected>& selected, std::size_t sz)
    {
        return sz - selected.size();
    }

    template<typename M>
    bool
    Submatrix<M>::equal_indexes(std::size_t current, const Index<Selected>& indexes)
    {
        bool are_equal = true;

        if(indexes.size() == 0)
        {
            are_equal = false;
        }
        else
        {
            for(std::size_t i = 0; i < indexes.size(); ++i)
            {
                if(current == indexes[i])
                {
                    are_equal = true;

                    break;
                }
                else
                {
                    are_equal = false;
                }
            }
        }

        return are_equal;
    }

    template<typename M>
    void
    Submatrix<M>::fill(const Index<Range>& rows, const Index<Range>& cols, const M& mat)
    {
        for(std::size_t i_1 = rows.first(), i_2 = 0; i_1 < rows.last(); ++i_1, ++i_2)
        {
            for(std::size_t j_1 = cols.first(), j_2 = 0; j_1 < cols.last(); ++j_1, ++j_2)
            {
                base::operator()(i_2, j_2) = mat(i_1, j_1);
            }
        }
    }

    template<typename M>
    void
    Submatrix<M>::fill(const Index<Selected> &rows, const Index<Selected> &cols, const M& mat)
    {
        for(std::size_t source_row = 0, dest_row = 0; source_row < mat.rows(); ++source_row)
        {
            if(equal_indexes(source_row, rows))
            {
                for(std::size_t source_col = 0, dest_col = 0; source_col < mat.cols(); ++source_col)
                {
                    if(equal_indexes(source_col, cols))
                    {
                        base::operator()(dest_row, dest_col) = mat(source_row, source_col);

                        dest_col++;
                    }
                }

                dest_row++;
            }
        }
    }

} // namespace linarg

#endif // MINOR_TCC
