#include <iostream>
#include "Matrix/Linarg.hpp"
#include "Tensor/Cube.tcc"
#include <stdexcept>
#include <functional>

#include <armadillo>
#include <typeinfo>
#include <chrono>
#include <regex>
#include <list>

using Cplx_d = std::complex<int>;


int main()
{
    linalg::Cube<linalg::Sparse_matrix<int>> C(linalg::Matrix_size(4, 5), 50.0, 3, linalg::Random<int>{1, 9});


    for(std::size_t i = 0; i < C.slices(); ++i)
        std::cout << C[i] << "\n\n";

    return 0;
}
