#ifndef VECTOR_TCC
#define VECTOR_TCC

#include "Vector.hpp"
#include "Expression.hpp"

namespace linarg
{
    template<typename T, typename C>
    Vector<T, C>::Vector(const allocator_type& alloc) :
        data_(alloc) { }

    template<typename T, typename C>
    Vector<T, C>::Vector(size_type n, value_type v, const allocator_type& alloc) :
        data_(n, v, alloc) { }

    template<typename T, typename C>
    Vector<T, C>::Vector(List<value_type> list, const allocator_type& alloc) :
        data_(list.size(), 0, alloc)
    {
        std::copy(list.begin(), list.end(), data_.begin());
    }

    template<typename T, typename C>
    Vector<T, C>::Vector(const std::string& expression, const allocator_type& alloc) :
        data_(alloc)
    {
        Expression<T> expr(expression);
        expr.start();
        vector_of_vectors<value_type> vec = expr.get();

        Matrix_initializer<value_type, vector_of_vectors<value_type>> init(vec);
        data_.resize(init.get_size().total());

        Array<value_type> data = init.get_data();
        std::copy(data.begin(), data.end(), data_.begin());
    }

    template<typename T, typename C>
    Vector<T, C>::Vector(size_type req_size, Random<typename traits::Get_type<is_complex<T>::value, T>::type> random, const allocator_type& alloc) :
        data_(req_size, 0, alloc)
    {
        take_random_values(random);
    }

    template<typename T, typename C>
    Vector<T, C>::Vector(const Vector<T, C>& copy) :
        data_(copy.data_) { }

    template<typename T, typename C>
    Vector<T, C>::Vector(Vector<T, C>&& move) :
        data_(std::move(move.data_)) { }

    template<typename T, typename C>
    Vector<T, C>&
    Vector<T, C>::operator=(const Vector<T, C>& rhs)
    {
        data_ = rhs.data_;
        return *this;
    }

    template<typename T, typename C>
    Vector<T, C>&
    Vector<T, C>::operator=(Vector<T, C>&& rhs)
    {
        data_ = std::move(rhs.data_);
        return *this;
    }

    template<typename T, typename C>
    Vector<T, C>&
    Vector<T, C>::operator=(const List<value_type>& list)
    {
        data_.resize(list.size());
        std::copy(list.begin(), list.end(), data_.begin());
    }

    template<typename T, typename C>
    Vector<T, C>&
    Vector<T, C>::operator=(Random<typename traits::Get_type<is_complex<T>::value, T>::type> rhs)
    {
        auto sz = std::get<1>(rhs.size());

        if((size() != sz))
        {
            data_.resize(std::get<1>(rhs.size()));
        }

        take_random_values(rhs);

        return *this;
    }

    template<typename T, typename C>
    typename Vector<T, C>::iterator
    Vector<T, C>::begin()
    {
        return data_.begin();
    }

    template<typename T, typename C>
    typename Vector<T, C>::iterator
    Vector<T, C>::end()
    {
        return data_.end();
    }

    template<typename T, typename C>
    typename Vector<T, C>::const_iterator
    Vector<T, C>::cbegin() const
    {
        return data_.cbegin();
    }

    template<typename T, typename C>
    typename Vector<T, C>::const_iterator
    Vector<T, C>::cend() const
    {
        return data_.cend();
    }

    template<typename T, typename C>
    typename Vector<T, C>::reverse_iterator
    Vector<T, C>::rbegin()
    {
        return data_.rbegin();
    }

    template<typename T, typename C>
    typename Vector<T, C>::reverse_iterator
    Vector<T, C>::rend()
    {
        return data_.rend();
    }

    template<typename T, typename C>
    typename Vector<T, C>::const_reverse_iterator
    Vector<T, C>::crbegin() const
    {
        return data_.crbegin();
    }

    template<typename T, typename C>
    typename Vector<T, C>::const_reverse_iterator
    Vector<T, C>::crend() const
    {
        return data_.crend();
    }

    template<typename T, typename C>
    typename Vector<T, C>::size_type
    Vector<T, C>::size() const noexcept
    {
        return data_.size();
    }

    template<typename T, typename C>
    bool
    Vector<T, C>::empty() const noexcept
    {
        return data_.empty();
    }

    template<typename T, typename C>
    typename Vector<T, C>::reference
    Vector<T, C>::operator[](size_type n)
    {
        return data_[n];
    }

    template<typename T, typename C>
    typename Vector<T, C>::const_reference
    Vector<T, C>::operator[](size_type n) const
    {
        return data_[n];
    }

    template<typename T, typename C>
    typename Vector<T, C>::reference
    Vector<T, C>::at(size_type n)
    {
        if(n > size())
        {
            throw std::out_of_range("Vector::at(n): index out of range");
            return data_[n];
        }
    }

    template<typename T, typename C>
    typename Vector<T, C>::const_reference
    Vector<T, C>::at(size_type n) const
    {
        if(n > size())
        {
            throw std::out_of_range("Vector::at(n): index out of range");
            return data_[n];
        }
    }

    template<typename T, typename C>
    void
    Vector<T, C>::resize(size_type n)
    {
        data_.resize(n);
    }

    template<typename T, typename C>
    void
    Vector<T, C>::insert(size_type position, value_type value)
    {
        data_.insert(position, value);
    }

    template<typename T, typename C>
        template<typename Iterator, typename >
        void
        Vector<T, C>::insert(Iterator position, value_type value)
        {
            data_.insert(position, value);
        }


    template<typename T, typename C>
    Vector<T, C>&
    Vector<T, C>::operator+=(const Vector<T, C>& rhs)
    {
        Vector result = op::Plus<self_type, self_type, op::Op_vector>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename T, typename C>
    Vector<T, C>&
    Vector<T, C>::operator-=(const Vector<T, C>& rhs)
    {
        Vector result = op::Minus<self_type, self_type, op::Op_vector>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename T, typename C>
    Vector<T, C>&
    Vector<T, C>::operator*=(const Vector<T, C>& rhs)
    {
        Vector result = op::Multiplies<self_type, self_type, op::Op_vector>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename T, typename C>
    Vector<T, C>&
    Vector<T, C>::operator*=(value_type scalar)
    {
        Vector result = op::Scalar_multiplies<self_type, value_type, op::Op_vector>()(*this, scalar);
        *this = result;

        return *this;
    }

    template<typename T, typename C>
    Vector<T, C>&
    Vector<T, C>::operator/=(value_type scalar)
    {
        Vector result = op::Scalar_divide<self_type, value_type, op::Op_vector>()(*this, scalar);
        *this = result;

        return *this;
    }

    template<typename T, typename C>
    void
    Vector<T, C>::take_random_values(Random<typename traits::Get_type<is_complex<T>::value, T>::type> random)
    {
        size_type sz = is_complex<T>{} ? data_.size() * 2 : data_.size();
        random.apply_size(sz);
        auto values = random.get();

        size_type count = 0;

        if constexpr(is_complex<T>{})
        {
            for(auto& x : *this)
            {
                x.real(values[count++]);
                x.imag(values[count++]);
            }
        }
        else
        {
            for(auto& x : *this)
            {
                x = values[count++];
            }
        }
    }

    // Ops

    template<typename T, typename C>
    Vector<T, C>& operator+(const Vector<T, C>& lhs, const Vector<T, C>& rhs)
    {
        using type = Vector<T, C>;

        return op::Plus<type, type, op::Op_vector>()(lhs, rhs);
    }

    template<typename T, typename C>
    Vector<T, C>& operator-(const Vector<T, C>& lhs, const Vector<T, C>& rhs)
    {
        using type = Vector<T, C>;

        return op::Minus<type, type, op::Op_vector>()(lhs, rhs);
    }

    template<typename T, typename C>
    Vector<T, C>& operator*(const Vector<T, C>& lhs, const Vector<T, C>& rhs)
    {
        using type = Vector<T, C>;

        return op::Multiplies<type, type, op::Op_vector>()(lhs, rhs);
    }

    template<typename T, typename C>
    Vector<T, C>& operator*(const Vector<T, C>& lhs, const T scalar)
    {
        using type = Vector<T, C>;

        return op::Scalar_multiplies<type, T, op::Op_vector>()(lhs, scalar);
    }

    template<typename T, typename C>
    Vector<T, C>& operator/(const Vector<T, C>& lhs, const T scalar)
    {
        using type = Vector<T, C>;

        return op::Scalar_divide<type, T, op::Op_vector>()(lhs, scalar);
    }

    template<typename T, typename C>
    bool operator==(const Vector<T, C>& lhs, const Vector<T, C>& rhs)
    {
        using type = Vector<T, C>;

        return op::Equal<type, type, op::Op_vector>()(lhs, rhs);
    }


} // namespace linarg

#endif // VECTOR_TCC
