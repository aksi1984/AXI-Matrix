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

int main()
{
    linarg::Triangular_matrix<Cplx_d, linarg::Diagonal> M(4, linarg::Random<int>(1, 9));
    std::cout << M;

    return 0;
}
