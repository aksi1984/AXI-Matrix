#ifndef SPARSE_MATRIX_TCC
#define SPARSE_MATRIX_TCC

#include "Sparse_matrix.hpp"

namespace axi
{
    template<typename T>
    Sparse_matrix<T>::Sparse_matrix(const allocator_type& alloc) :
        base(alloc) { }

    template<typename T>
    Sparse_matrix<T>::Sparse_matrix(const Matrix_size& size, const allocator_type& alloc) :
        base(size.rows_, size.cols_, alloc) { }

    template<typename T>
    Sparse_matrix<T>::Sparse_matrix(size_type rows, size_type cols, const allocator_type& alloc) :
        base(rows, cols, alloc),
        zeros_(rows * cols) { }

    template<typename T>
        template<typename U, typename>
        Sparse_matrix<T>::Sparse_matrix(const Matrix_size& req_size, double density, Random<U> random, const allocator_type& alloc) :
            base{req_size.rows_, req_size.cols_, alloc}
        {
            LINALG_CHECK(((density >= 0.0) && (density < 100.0)), Invalid_density(density))

            Array<std::size_t> locations = detail::random_locations(base::size(), density);

            random.set_size(req_size);
            Array<T> values = random.get(std::is_arithmetic<T>{});

            for(size_type i = 0; i < locations.size(); ++i)
            {
                base::operator[](locations[i]) = values[i];
            }
        }

    template<typename T>
        template<typename U, typename>
        Sparse_matrix<T>::Sparse_matrix(size_type req_rows, size_type req_cols, double density, Random<U> random, const allocator_type& alloc) :
            self_type(Matrix_size{req_rows, req_cols}, density, random, alloc) { }

    template<typename T>
    Sparse_matrix<T>::Sparse_matrix(const Sparse_matrix<T>& copy) :
        base{copy} { }

    template<typename T>
    Sparse_matrix<T>::Sparse_matrix(Sparse_matrix<T>&& move) :
        base{std::move(move)} { }

    template<typename T>
    Sparse_matrix<T>&
    Sparse_matrix<T>::operator=(const Sparse_matrix<T>& rhs)
    {
        base::operator=(rhs);

        return *this;
    }

    template<typename T>
    Sparse_matrix<T>&
    Sparse_matrix<T>::operator=(Sparse_matrix<T>&& rhs)
    {
        base::operator=(std::move(rhs));

        return *this;
    }

    template<typename T>
        template<typename U, typename>
        Sparse_matrix<T>&
        Sparse_matrix<T>::operator=(Random<U> random)
        {
            if(Matrix_size new_size = std::get<0>(random.size()); new_size.total() != base::size().total())
            {
                Sparse_matrix temp{new_size};
                *this = temp;
            }

            double density = detail::random_density();
            Array<std::size_t> locations = detail::random_locations(base::size(), density);
            Array<T> values = random.get(std::is_arithmetic<T>{});

            for(size_type i = 0; i < locations.size(); ++i)
            {
                base::operator[](locations[i]) = values[i];
            }

            return *this;
        }

} // namespace linarg

#endif // SPARSE_MATRIX_TCC
