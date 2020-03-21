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
    linarg::rd::sp_int_mt19937<int, linarg::rd::Rd_spmat>(size, 1, 9) ;
    linarg::Triangular_matrix<int, linarg::Upper> M(linarg::rd::tr_int_mt19937<int>(size, 1, 9));




    return 0;
}
