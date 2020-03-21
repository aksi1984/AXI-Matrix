#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>

namespace linarg
{
    #define LINARG_CHECK(expr, e)  \
            if( !(expr) )          \
            {                      \
                e.throw_except();  \
            }


    template<typename E>
    struct Exception_base : public E
    {
        Exception_base(const std::string& message) :
            E(message) { }

        [[noreturn]] void throw_except()
        {
            throw *this;
        }
    };

    struct Incompatible_size : public Exception_base<std::runtime_error>
    {

        Incompatible_size(const std::string& m, std::size_t rows_1, std::size_t cols_1, std::size_t rows_2, std::size_t cols_2) :
            Exception_base<std::runtime_error>(m + ": incompatible matrix dimensions: (" +
                               std::to_string(rows_1) + "x" + std::to_string(cols_1) +
                               ") and (" + std::to_string(rows_2) + "x" + std::to_string(cols_2) + ")") { }

        Incompatible_size(const std::string& m, std::size_t size_1, std::size_t size_2) :
            Exception_base<std::runtime_error>(m + ": incompatible vector dimensions: (" + std::to_string(size_1) +
                               ") and (" + std::to_string(size_2) + ")")   { }

        Incompatible_size() :
            Exception_base<std::runtime_error>("Multiplication: The number of columns in the first\n matrix is not equal "
                                               "the number of rows int the second matrix") {}
    };

    struct Incosistent_columns : public Exception_base<std::logic_error>
    {
        Incosistent_columns() :
            Exception_base<std::logic_error>("Incosisten numbers of columns") { }
    };

    struct Out_of_bounds : public Exception_base<std::out_of_range>
    {
        Out_of_bounds(const std::string& m) :
            Exception_base<std::out_of_range>(m + ": index out of bounds") { }
    };

    struct Divide_by_zero : public Exception_base<std::runtime_error>
    {
        Divide_by_zero(const std::string& m) :
            Exception_base<std::runtime_error>(m + ": divide by zero") { }
    };

    struct Not_square : public Exception_base<std::runtime_error>
    {
        Not_square() :
            Exception_base<std::runtime_error>("Not square matrix") { }
    };

    struct Bad_size : public Exception_base<std::runtime_error>
    {
        Bad_size(const std::string& m) :
            Exception_base<std::runtime_error>(m) { }
    };

    struct Invalid_expression : public Exception_base<std::logic_error>
    {
        Invalid_expression() :
            Exception_base<std::logic_error>("Invalid expression") { }
    };

    struct Invalid_density : public Exception_base<std::invalid_argument>
    {
        Invalid_density(double density) :
            Exception_base<std::invalid_argument>("Invalid density (" +
                                                  std::to_string(density) + "), "
                                                  "must be in the [0, 100] interval") { }
    };

    struct Bad_index : public Exception_base<std::logic_error>
    {
        Bad_index(std::size_t i, std::size_t j, const std::string& m) :
            Exception_base<std::logic_error>("Bad index (" + std::to_string(i) + ", " +
                                              std::to_string(j) + ") " + m) { }
    };

} // namespace linarg

#endif // EXCEPTION_HPP
