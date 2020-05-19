#ifndef INDEX_HPP
#define INDEX_HPP

#include <iostream>
#include <set>

#include "Tags.hpp"

namespace axi
{
    template<typename T>
    class Index;

    template<>
    class Index<Range>
    {
    public:

        Index() :
            first_{},
            last_{} { }

        Index(std::size_t req_first, std::size_t req_last) :
            first_{req_first},
            last_{req_last} { }

        std::size_t first() const noexcept
        {
            return first_;
        }

        std::size_t last() const noexcept
        {
            return last_ + 1;
        }

        std::size_t size() const noexcept
        {
            return last_ - first_ + 1;
        }

    private:

        std::size_t first_;
        std::size_t last_;
    };

    template<>
    class Index<Selected>
    {
    public:

        Index() { }

        Index(std::initializer_list<std::size_t> req_indexes) :
            indexes_{req_indexes.begin(), req_indexes.end()} { }

        std::size_t size() const noexcept
        {
            return indexes_.size();
        }

        std::size_t operator[](std::size_t n) const
        {
            return *std::next(indexes_.begin(), n);
        }

    private:

        std::set<std::size_t> indexes_;
    };

} // namespace linalg

#endif // INDEX_HPP
