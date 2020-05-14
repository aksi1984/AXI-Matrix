#ifndef SUBMATRIX_HPP
#define SUBMATRIX_HPP

#include "Base.tcc"
#include "Index.hpp"

namespace linalg
{
    template<typename M>
    class Submatrix : public Base<tags::Submatrix_tag, typename M::value_type, Array<typename M::value_type>, typename M::allocator_type>
    {

    private:

        using base = Base<tags::Submatrix_tag, typename M::value_type, Array<typename M::value_type>, typename M::allocator_type>;

    public:

        using value_type        = typename base::value_type;
        using size_type         = typename base::size_type;


        Submatrix(const M& mat, const Index<Range>& row_index, const Index<Range>& col_index);

        Submatrix(const M& mat, const Index<Selected>& selected_rows, const Index<Selected>& selected_cols);

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
    };

} // namespace axi

#endif // SUBMATRIX_HPP
