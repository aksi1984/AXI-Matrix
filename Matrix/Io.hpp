#ifndef IO_HPP
#define IO_HPP

#include "Base.hpp"
#include "Vector.hpp"
#include "Triangular_data.hpp"
#include "Algorithms.hpp"

#include <iostream>
#include <complex>
#include <iomanip>
#include <locale>

namespace linarg
{
    template<typename Char, typename Traits, typename M>
    std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, const M& mat)
    {
        using size_type = typename M::size_type;
        using mat_type = typename M::matrix_type;

        std::string text = " (" + std::to_string(mat.rows()) + ", " + std::to_string(mat.rows()) + ")\n";
        std::string name;

        std::ostringstream ost;
        ost.precision(1);

        if constexpr(std::is_same<mat_type, Sparse_tag>::value)
        {
            name = "Sparse matrix";
            std::string density_str = "\nDensity";
            std::string non_zeros_str = "\nNon zeros";

            std::size_t zeros = algo::zeros(mat);
            std::size_t non_zeros = mat.size().total() - zeros;
            double density = (static_cast<double>(non_zeros) / static_cast<double>(mat.size().total())) * 100.0;

            text.insert(0, name);

            ost << std::fixed << text << density_str << std::setw(4)
                << std::setfill(' ') << ":" << density << "%" << non_zeros_str
                << std::setw(2) << std::setfill(' ') << ":" << non_zeros;

        }
        else if constexpr(std::is_same<mat_type, Dense_tag>::value)
        {
            name = "Dense matrix";
            text.insert(0, name);
            ost << text;
        }
        else if constexpr(std::is_same<mat_type, Triangular_tag>::value)
        {
            using triangular_type = typename M::triangular_fill_type;


            std::string triangular_type_text = ( std::is_same<triangular_type, Upper>::value ? "upper" : (std::is_same<triangular_type, Lower>::value ? "lower" : "diagonal") );
            name = "Triangular matrix";
            text.insert(0, name);
            ost << text << '\n' << "Type" << std::setw(2) << std::setfill(' ') << ": " << triangular_type_text;
        }

        os << ost.str() << "\n\n";


        for(size_type i = 0; i < mat.rows(); ++i)
        {
            for(size_type j = 0; j < mat.cols(); ++j)
            {
                os << mat(i, j) << ' ';
            }

            os << '\n';
        }

        return os;
    }

    template<typename Char, typename Traits, typename M, typename = typename std::enable_if<!std::is_same<typename M::matrix_type, Sparse_tag>::value>::type>
    std::basic_istream<Char, Traits>& operator>>(std::basic_istream<Char, Traits>& is, M& mat)
    {
        Char ch;

        std::size_t rows;
        std::size_t cols;

        std::string expression;

        bool fill_success = true;

        if(is >> ch && ch != '(')
        {
            is.putback(ch);
            is.setstate(std::ios::failbit);

            fill_success = false;
        }
        else if(is >> rows >> ch && ch != ',')
        {
            is.putback(ch);
            is.setstate(std::ios::failbit);

            fill_success = false;
        }
        else if(is >> cols >> ch && ch != ')')
        {
            is.putback(ch);
            is.setstate(std::ios::failbit);

            fill_success = false;
        }
        else if(fill_success)
        {
            for(std::size_t i = 0; i < rows; ++i)
            {
                for(std::size_t j = 0; j < cols; ++j)
                {
                    Char number;

                    if(j == 0)
                    {
                        Char comma;

                        if(is >> ch >> number >> comma &&
                                ((ch != '{') || (!isdigit(number)) || (comma != ',')) )
                        {
                            is.putback(number);
                            is.putback(number);
                            is.putback(ch);
                            is.setstate(std::ios::failbit);

                            fill_success = false;

                            break;
                        }
                        else if(!is.fail())
                        {
                            expression.push_back(ch);
                            expression.push_back(number);
                            expression.push_back(comma);
                        }
                    }
                    else if(j == cols - 1)
                    {

                        if(is >> number >> ch && (!isdigit(number) || ch != '}') )
                        {
                            is.putback(number);
                            is.putback(ch);
                            is.setstate(std::ios::failbit);

                            fill_success = false;

                            break;
                        }
                        else if(!is.fail())
                        {
                            expression.push_back(number);
                            expression.push_back(ch);
                        }
                    }
                    else
                    {
                        if(is >> number >> ch && (!isdigit(number) || ch != ',') )
                        {
                            is.putback(number);
                            is.putback(ch);
                            is.setstate(std::ios::failbit);

                            fill_success = false;

                            break;
                        }
                        else if(!is.fail())
                        {
                            expression.push_back(number);
                            expression.push_back(ch);
                        }
                    }

                    if(!fill_success)
                    {
                        break;
                    }
                }
            }
        }

        if(fill_success)
        {
            mat = M(expression);
        }

        return is;
    }

    template<typename Char, typename Traits, typename T>
    std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, const Vector<T>& vec)
    {
        using size_type = typename Vector<T>::size_type;

        os << "Vector (" << vec.size() << "): {";

        for(size_type i = 0; i < vec.size(); ++i)
        {
            os << vec[i];

            if(i < vec.size() - 1)
            {
                os << ", ";
            }
        }

        os << "}";

        return os;
    }

    template<typename Char, typename Traits, typename T>
    std::basic_istream<Char, Traits>& operator>>(std::basic_istream<Char, Traits>& is, Vector<T>& vec)
    {
        using size_type = typename Vector<T>::size_type;

        size_type size;
        char char_t;
        std::string expr;

        bool fill_success = true;


        if(is >> char_t >> size && (char_t != '('))
        {
            is.putback(char_t);
            is.setstate(std::ios::failbit);
        }
        else if(is >> char_t && char_t != ')')
        {
            is.putback(char_t);
            is.setstate(std::ios::failbit);
        }
        else if(!is.fail())
        {
            if(is >> char_t && (char_t != '{'))
            {
                is.putback(char_t);
                is.setstate(std::ios::failbit);

                fill_success = false;
            }
            else if(!is.fail())
            {
                expr.push_back(char_t);

                char value;

                for(size_type i = 0; i < size - 1; ++i)
                {
                    if(is >> value >> char_t && (!isdigit(value) || (char_t != ',')) )
                    {
                        is.putback(char_t);
                        is.putback(value);
                        is.setstate(std::ios::failbit);

                        fill_success = false;

                    }
                    else if(!is.fail())
                    {
                        expr.push_back(value);
                        expr.push_back(char_t);
                    }
                }

                if(is >> value >> char_t && (char_t != '}'))
                {
                    is.putback(value);
                    is.putback(char_t);
                    is.setstate(std::ios::failbit);

                    fill_success = false;
                }
                else if(!is.fail())
                {
                    expr.push_back(value);
                    expr.push_back(char_t);
                }
            }

        }

        if(fill_success)
        {
            vec = Vector<T>(expr);
        }

        return is;
    }
}

#endif // IO_HPP
