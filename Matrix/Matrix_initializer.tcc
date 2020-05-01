#ifndef MATRIX_INITIALIZER_TCC
#define MATRIX_INITIALIZER_TCC

#include "Matrix_initializer.hpp"

namespace linalg
{
    template<typename T, typename C>
    Matrix_initializer<T, C>::Matrix_initializer(C container)
    {
        check_dimension(container);
        set_data(container);
    }

    template<typename T, typename C>
    Matrix_size
    Matrix_initializer<T, C>::get_size() const noexcept
    {
        return size_;
    }

    template<typename T, typename C>
    Unbounded_array<T>
    Matrix_initializer<T, C>::get_data() const noexcept
    {
        return data_;
    }

    template<typename T, typename C>
    void
    Matrix_initializer<T, C>::check_dimension(C container)
    {
        std::size_t rows = container.size();
        std::vector<std::size_t> cols_num(rows);

        using sub_container = typename is_initializer_list<T, typename C::value_type>::type;

        std::transform(container.begin(), container.end(), cols_num.begin(), [](sub_container sc){ return sc.size(); });

        auto first_column = cols_num[0];
        std::size_t total = std::count_if(cols_num.begin(), cols_num.end(),
                                          [first_column](std::size_t x){ return x == first_column; });

        LINALG_CHECK(total == rows, Incosistent_columns())

        size_.rows_ = rows;
        size_.cols_ = cols_num[0];
    }

    template<typename T, typename C>
    void
    Matrix_initializer<T, C>::set_data(C container)
    {
        data_.resize(size_.rows_ * size_.cols_);
        std::size_t i = 0;

        for(auto iter = container.begin(); iter != container.end(); ++iter, ++i)
        {
            std::size_t j = 0;

            for(auto iter_2 = iter->begin(); iter_2 != iter->end(); ++iter_2, ++j)
            {
                data_[size_.rows_ * j + i] = *iter_2;
            }
        }
    }


} // namespace linarg

#endif // MATRIX_INITIALIZER_TCC
