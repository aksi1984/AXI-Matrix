#include <iostream>
#include "Matrix/Linarg.hpp"
#include <stdexcept>
#include <functional>

#include <armadillo>
#include <typeinfo>
#include <chrono>
#include <regex>
#include <list>

using Cplx_d = std::complex<int>;


template<typename T>
struct Function
{
    Function() { }
    Function(T val) : value{val} { }

    T operator()()
    {
        return value;
    }

    T value = {};
};

int main()
{
    linalg::Sparse_matrix<int> M_1{3, 4, 40.0, linalg::Random<int>{1, 9}};
    linalg::Sparse_matrix<int> M_2;
    M_2 = linalg::Random<int>{4, 4, 1, 9};

    std::cout << M_2;

    return 0;
}
