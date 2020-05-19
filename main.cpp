#include <iostream>
#include <stdexcept>
#include <functional>

#include <armadillo>
#include <typeinfo>
#include <chrono>
#include <regex>
#include <list>

#include "include/Axi.hpp"



template<typename T>
using cube = axi::Cube<axi::Matrix<T>>;

using mat_ptr = std::shared_ptr<axi::Matrix<int>>;

using tr_int = axi::Triangular_matrix<int, axi::Upper>;

int main()
{
    tr_int tr(5, 5);


    axi::Submatrix<tr_int> SM(tr, axi::Index<axi::Range>{0, 2}, axi::Index<axi::Range>{1, 2});
    SM.fill(1);
    //auto SM = M.submatrix(axi::Index<axi::Selected>{1, 3}, axi::Index<axi::Selected>{0, 1});

    //std::cout << "\n\n";

    //SM.fill(1);
    //std::cout << M;

    std::cout << SM;


    //std::cout << SM;

    return 0;
}
