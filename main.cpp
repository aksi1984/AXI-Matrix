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
    linarg::Square_size size(5);
    linarg::rd::tr_int_mt19937<int>(size, 1, 9);
    linarg::Triangular_matrix<int, linarg::Lower> M(linarg::rd::tr_int_mt19937<int>(size, 1, 9));


    //std::cout << M;


    return 0;
}
