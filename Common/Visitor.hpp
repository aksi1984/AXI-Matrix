#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "Matrix/Matrix_size.hpp"

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

    } // namespace visitor
} // namespace linalg

#endif // VISITOR_HPP
