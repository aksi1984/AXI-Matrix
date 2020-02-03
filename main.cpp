#include <iostream>
#include "Matrix/Linarg.hpp"
#include <stdexcept>
#include <functional>

#include <armadillo>
#include <typeinfo>
#include <chrono>
#include <regex>
#include <list>



int main()
{
    linarg::Matrix<int> M;
    std::cin >> M;

    std::cout << M;

    return 0;
}
