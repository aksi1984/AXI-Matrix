#include <iostream>
#include "Matrix/Linarg.hpp"
#include <stdexcept>
#include <functional>

#include <armadillo>
#include <typeinfo>
#include <chrono>
#include <regex>
#include <list>

struct Foo;

int main()
{
    linarg::Vector<int> vector{1,2,3,4};

    linarg::Triangular_matrix<int, linarg::Diagonal> M(vector);
    std::cout << M;

    return 0;
}
