#include <iostream>
#include "Matrix/Linarg.hpp"
#include <stdexcept>
#include <functional>

#include <armadillo>
#include <typeinfo>
#include <chrono>
#include <regex>
#include <list>

using Cplx_d = std::complex<double>;

template<typename T>
struct Function
{
    Function(T val) : value{val} { }

    Cplx_d operator()()
    {
        return Cplx_d{value , value + 1};
    }

    T value = {};
};

int main()
{
    std::vector<int> vec{1,2,3};
    linarg::Triangular_matrix<int, linarg::Diagonal> M{std::vector<int>{1,2,3,4,5}};

    std::cout << M;

    //std::variant<int, std::string> variant(std::in_place_index<1>, "23");
    //std::cout << std::boolalpha << std::holds_alternative<int>(variant);

    return 0;
}
