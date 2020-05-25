#include <iostream>
#include <stdexcept>
#include <functional>

#include <armadillo>
#include <typeinfo>
#include <chrono>
#include <regex>
#include <list>
#include <chrono>

#include "include/Axi.hpp"

int main()
{
    /*arma::cube C_1 = arma::randu(3,4,3);
    arma::cube C_2 = arma::randu(3,4,3);
    arma::mat M = arma::randu(3, 4);

    std::cout << C_1;
    auto tube = C_1.tube(0, 0);
    std::cout << "\n";
    std::cout << tube;*/

    axi::Cube<axi::Matrix<int>> c_1(axi::Matrix_size(3, 4), 3, axi::Random<int>(1, 9));
    axi::Cube<axi::Matrix<int>> c_2(axi::Matrix_size(4, 3), 3, axi::Random<int>(1, 9));

    axi::Matrix<int> m_1(3,4);
    axi::Matrix<int> m_2(3,4);

    auto c = c_1 + c_2;
    std::cout << m_3;


    return 0;
}
