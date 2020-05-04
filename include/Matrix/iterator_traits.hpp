#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

#include <memory>

namespace linarg
{
    struct mat_random_access_iterator_tag { };
    struct dimensions_iterator_tag { };

    template<typename Category, typename T, typename Ref = T&,
             typename Ptr = T*, typename Distance = std::ptrdiff_t>
    struct iterator
    {
        using iterator_category = Category;
        using value_type        = T;
        using reference         = Ref;
        using pointer           = Ptr;
        using difference_type   = Distance;
    };

    template<typename Iterator>
    struct iterator_traits
    {
        using iterator_category = typename Iterator::iterator_category;
        using value_type        = typename Iterator::value_type;
        using reference         = typename Iterator::reference;
        using pointer           = typename Iterator::pointer;
        using difference_type   = typename Iterator::difference_type;
    };

    template<typename T>
    struct iterator_traits<T*>
    {
        using iterator_category = mat_random_access_iterator_tag;
        using value_type        = T;
        using reference         = T&;
        using pointer           = T*;
        using difference_type   = std::ptrdiff_t;
    };

    template<typename T>
    struct iterator_traits<const T*>
    {
        using iterator_category = mat_random_access_iterator_tag;
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using difference_type   = std::ptrdiff_t;
    };

    template<typename T>
    struct dimensions_iterator_traits
    {
        using iterator_category = dimensions_iterator_tag;
        //using value_type        = T;
        //using reference         = T&;
        using pointer           = T;
        using difference_type   = std::ptrdiff_t;
    };
}

#endif // ITERATOR_TRAITS_H
