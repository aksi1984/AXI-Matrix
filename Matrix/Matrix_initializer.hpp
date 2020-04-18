#ifndef MAT_INITIALIZER_HPP
#define MAT_INITIALIZER_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>

#include "Arrays.hpp"
#include "Cond.hpp"
#include "Matrix_size.tcc"
#include "Traits.hpp"
#include "Exception.hpp"


namespace linarg
{

    template<typename T, typename C>
    class Matrix_initializer
    {
    public:

        Matrix_initializer(C container);

        Matrix_size get_size() const noexcept;

        Unbounded_array<T> get_data() const noexcept;

    private:

        void check_dimension(C container);

        void set_data(C container);

        Unbounded_array<T> data_;
        Matrix_size size_;
    };
}

#endif // MAT_INITIALIZER_HPP
