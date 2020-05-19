#ifndef SUBMATRIX_HPP
#define SUBMATRIX_HPP

#include <variant>
#include "include/Storage/Arrays.hpp"
#include "Index.hpp"



namespace axi
{
    template<typename C, typename T, typename A, typename Alloc>
    class Base;


    inline bool are_same_indexes(std::size_t current, const Index<Selected>& indexes)
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


    template<typename M, typename T>
    struct Submatrix_fill
    {
        Submatrix_fill(M& mat, T value) :
            mat_{mat},
            value_{value} { }

        void operator()(const std::pair<Index<Range>, Index<Range>>& ranges)
        {
            std::size_t row_begin = ranges.first.first();
            std::size_t row_end = ranges.first.last();

            std::size_t col_begin = ranges.second.first();
            std::size_t col_end = ranges.second.last();

            for(std::size_t i = row_begin; i < row_end; ++i)
            {
                for(size_t j = col_begin; j < col_end; ++j)
                {
                    mat_(i, j) = value_;
                }
            }
        }

        void operator()(const std::pair<Index<Selected>, Index<Selected>>& ranges)
        {
            for(std::size_t i = 0; i < mat_.rows(); ++i)
            {
                if(are_same_indexes(i, ranges.first))
                {
                    for(std::size_t j = 0; j < mat_.cols(); ++j)
                    {
                        if(are_same_indexes(j, ranges.second))
                        {
                            if(mat_(i, j) != value_)
                            {
                                mat_(i, j) = value_;
                            }
                        }
                    }
                }
            }
        }

        M& mat_;
        T value_;
    };


    template<typename M>
    class Submatrix : public Base<tags::Submatrix_tag, typename M::value_type, Array<typename M::value_type>, typename M::allocator_type>
    {

    private:

        using base = Base<tags::Submatrix_tag, typename M::value_type, Array<typename M::value_type>, typename M::allocator_type>;

    public:

        using value_type        = typename base::value_type;
        using reference         = typename base::reference;
        using const_reference   = typename base::const_reference;
        using size_type         = typename base::size_type;


        Submatrix(M& mat, const Index<Range>& row_index, const Index<Range>& col_index);

        Submatrix(M &mat, const Index<Selected>& selected_rows, const Index<Selected>& selected_cols);

        void fill(value_type value);

        std::variant<std::pair<Index<Range>, Index<Range>>, std::pair<Index<Selected>, Index<Selected>>> indexes() const noexcept
        {
            return indexes_;
        }

    private:

        std::size_t init_size(const Index<Selected>& selected, std::size_t sz);

        bool equal_indexes(std::size_t current, const Index<Selected>& indexes);

        void fill(const Index<Range>& rows, const Index<Range>& cols, const M& mat);

        void fill(const Index<Selected>& rows, const Index<Selected>& cols, const M& mat);

    private:

        std::variant<std::pair<Index<Range>, Index<Range>>, std::pair<Index<Selected>, Index<Selected>>> indexes_;

        M& mat_;
    };

} // namespace axi

#endif // SUBMATRIX_HPP
