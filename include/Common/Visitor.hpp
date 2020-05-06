#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "include/Matrix/Matrix_size.tcc"

namespace linalg
{
    namespace visitor
    {
        struct Objects_size_visitor
        {
            std::size_t operator()(std::size_t size)
            {
                return size;
            }

            std::size_t operator()(const Matrix_size& size)
            {
                return size.total();
            }

        };

        struct Cube_subview_elements_visitor
        {
            std::pair<std::size_t, std::size_t> operator()(std::size_t elem)
            {
                return std::pair{elem, elem + 1};
            }

            std::pair<std::size_t, std::size_t> operator()(std::pair<std::size_t, std::size_t> elems)
            {
                return elems;
            }
        };

    } // namespace visitor
} // namespace linalg

#endif // VISITOR_HPP
