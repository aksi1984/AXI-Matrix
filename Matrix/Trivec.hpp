#ifndef TRIVEC_HPP
#define TRIVEC_HPP

#include "Vector.hpp"

namespace linarg
{
    struct Upper_triangle { };
    struct Lower_triangle { };

    template<typename M, typename TriType>
    class Trivec : public Vector<typename M::value_type>
    {
    public:

        using base          = Vector<typename M::value_type>;
        using value_type    = typename base::value_type;
        using size_type     = typename base::size_type;

        Trivec() { }

        Trivec(const M& mat) :
            base( ((mat.rows() * mat.cols()) - mat.rows()) / 2 )
        {
            if(mat.is_square())
            {
                make(mat);
            }
        }

    private:

        void make(const M& mat)
        {
            std::size_t count = 0;

            for(std::size_t i = 0; i < mat.rows(); ++i)
            {
                for(std::size_t j = 0; j < mat.cols(); ++j)
                {
                    if(j > i)
                    {
                        base::operator[](count) = ( std::is_same_v<TriType, Upper_triangle> ? mat(i, j) : mat(j, i) );

                        if(count < base::size())
                        {
                            count++;
                        }
                    }
                }
            }
        }
    };

} // namespace Axi

#endif // TRIVEC_HPP
