#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "include/Matrix/Matrix_size.tcc"
#include "include/Matrix/Index.hpp"

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


        struct Index_IO_visitor
        {
            void operator()(const std::pair<Index<Range>, Index<Range>>& indexes)
            {


                std::cout << "Cols: {" << indexes.first.first() << "-" << indexes.second.last() << "}, rows: {" << indexes.second.first() << "-" << indexes.second.last() << "}";
            }

            void operator()(const std::pair<Index<Selected>, Index<Selected>>& indexes)
            {
                //std::basic_ostream<Char, Traits> os;

                std::cout << "Cols : {";

                for(std::size_t i = 0; i < indexes.first.size(); ++i)
                {
                    std::cout << indexes.first[i];

                    if(i != indexes.first.size() - 1)
                    {
                       std::cout << ", ";
                    }
                }

                std::cout << "}, Rows: {";

                for(std::size_t i = 0; i < indexes.second.size(); ++i)
                {
                    std::cout << indexes.second[i];

                    if(i != indexes.second.size() - 1)
                    {
                        std::cout << ", ";
                    }
                }

                 std::cout << "}";
            }
        };

    } // namespace visitor
} // namespace linalg

#endif // VISITOR_HPP
