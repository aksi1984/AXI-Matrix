#include <iostream>
#include <stdexcept>
#include <functional>

#include <armadillo>
#include <typeinfo>
#include <chrono>
#include <regex>
#include <list>

#include "include/Linalg.hpp"
#include "include/Matrix/Submatrix.tcc"


template<typename T>
using cube = linalg::Cube<linalg::Matrix<T>>;


struct Visitor
{
    void operator()(std::pair<linalg::Index<linalg::Range>, linalg::Index<linalg::Range>> ind)
    {

    }

};

int main()
{
    linalg::Matrix<int> M
    {
        {1,2,3,4},
        {5,4,3,2},
        {6,3,2,5},
        {5,3,6,7}
    };

    linalg::Submatrix<linalg::Matrix<int>> SM(M, linalg::Index<linalg::Range>{0, 2}, linalg::Index<linalg::Range>{1, 2});

    std::cout << SM;

    //std::cout << SM;

    return 0;
}
