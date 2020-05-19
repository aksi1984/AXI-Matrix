#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include <iostream>

namespace axi
{
    namespace conv
    {
        template<typename T> struct Conversion_type { };

        template<> struct Conversion_type<int>         { enum { value = 0 }; };
        template<> struct Conversion_type<float>       { enum { value = 1 }; };
        template<> struct Conversion_type<double>      { enum { value = 2 }; };
        template<> struct Conversion_type<long double> { enum { value = 3 }; };

        ////////////////////////////////////////////////////////

        struct Int
        {
            static int convert(const std::string& str)
            {
                return std::stoi(str);
            }
        };

        struct Float
        {
            static float convert(const std::string& str)
            {
                return std::stof(str);
            }
        };

        struct Double
        {
            static double convert(const std::string& str)
            {
                return std::stod(str);
            }
        };

        struct Long_double
        {
            static long double convert(const std::string& str)
            {
                return std::stold(str);
            }
        };

    } // namespace conv

} // namespace linarg

#endif // CONVERSIONS_HPP
