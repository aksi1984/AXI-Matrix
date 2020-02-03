#ifndef MINOR_HPP
#define MINOR_HPP

#include "Base.tcc"
#include "Minor_initializer.tcc"

namespace linarg
{
    template<typename M>
    class Minor : public Base<Minor_tag,
                              Array<typename M::value_type>,
                              typename M::allocator_type
                              >
    {
        static_assert (traits::is_matrix<M>::value, "Invalid template parameter (must be Matrix).");

    public:

        using base              = Base<Minor_tag,
                                       Array<typename M::value_type>,
                                       typename M::allocator_type
                                      >;
        using value_type        = typename M::value_type;
        using size_type         = typename M::size_type;
        using allocator_type    = typename base::allocator_type;


        Minor(M mat, size_type n, const Minor_initializer& minor_init, const allocator_type& alloc = allocator_type());

        Minor(const M& mat, const Minor_initializer& minor_init, const allocator_type& alloc = allocator_type());

        Minor& operator=(const Minor_initializer& minor_init);

    private:

        bool has_minor_value(size_type n, Container<size_type> array);

        void init(M mat, size_type n, const Minor_initializer& init);

        void init(M mat, Minor_initializer init);
    };

} // namespace axi

#endif // MINOR_HPP
