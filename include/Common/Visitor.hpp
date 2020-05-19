#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "include/Matrix/Matrix_size.tcc"
#include "include/Matrix/Index.hpp"

namespace axi
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


        template<typename Char, typename Traits>
        struct Index_IO_visitor
        {
            Index_IO_visitor(std::basic_ostream<Char, Traits>& os) :
                os_{os} { }

            void operator()(const std::pair<Index<Range>, Index<Range>>& indexes)
            {
                os_ << "Cols: {" << indexes.first.first() << "-" << indexes.second.last() << "}, rows: {" << indexes.second.first() << "-" << indexes.second.last() << "}";
            }

            void operator()(const std::pair<Index<Selected>, Index<Selected>>& indexes)
            {
                os_ << "Cols : {";

                for(std::size_t i = 0; i < indexes.first.size(); ++i)
                {
                    os_ << indexes.first[i];

                    if(i != indexes.first.size() - 1)
                    {
                       os_ << ", ";
                    }
                }

                os_ << "}, Rows: {";

                for(std::size_t i = 0; i < indexes.second.size(); ++i)
                {
                    os_ << indexes.second[i];

                    if(i != indexes.second.size() - 1)
                    {
                        os_ << ", ";
                    }
                }

                 os_ << "}";
            }

            std::basic_ostream<Char, Traits> os_;
        };

    } // namespace visitor
} // namespace linalg

#endif // VISITOR_HPP
