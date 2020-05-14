#ifndef TAGS_HPP
#define TAGS_HPP

namespace linalg
{
    namespace tags
    {
        struct Dense_matrix_tag { };
        struct Sparse_matrix_tag { };
        struct Triangular_matrix_tag { };
        struct Diagonal_matrix_tag { };
        struct Minor_submatrix_tag { };
        struct Submatrix_tag { };

    } // namespace tags

    struct Range { };
    struct Selected { };

} // namespace linalg

#endif // TAGS_HPP
