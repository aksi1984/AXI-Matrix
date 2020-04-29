#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <chrono>
#include <variant>
#include <algorithm>
#include <complex>

#include "Arrays.hpp"
#include "Matrix_size.hpp"
#include "Traits.hpp"
#include "Cond.hpp"

namespace linalg
{
    namespace detail
    {
        struct Size_visitor
        {
            Size_visitor() { }

            std::size_t operator()(std::size_t size)
            {
                return size;
            }

            std::size_t operator()(const Matrix_size& size)
            {
                return size.total();
            }

        };

        template<typename D>
        class Random_impl
        {
        public:

            using distribution = D;
            using params       = typename distribution::param_type;
            using result_type  = typename distribution::result_type;

            Random_impl(result_type min, result_type max) :
                dist_{params{min, max}}
            {
                add_seed();
            }

            result_type get()
            {
                return dist_(engine_);
            }

        private:

            void add_seed()
            {
                auto seed = std::chrono::_V2::system_clock::now().time_since_epoch().count();
                engine_.seed(seed);
            }

            std::mt19937 engine_;
            distribution dist_;
            params params_;
        };

        Array<std::size_t> random_locations(const Matrix_size& size, double density)
        {
            std::size_t elems = static_cast<std::size_t>((density / 100.0) * static_cast<double>(size.total()));

            auto seed = std::chrono::_V2::system_clock::now().time_since_epoch().count();
            std::default_random_engine engine(seed);

            Array<std::size_t> indexes(size.total() - 1);
            std::iota(indexes.begin(), indexes.end(), 0);
            std::shuffle(indexes.begin(), indexes.end(), engine);

            Array<std::size_t> locations(elems);
            std::copy_n(indexes.begin(), elems, locations.begin());

            return locations;
        }

        double random_density()
        {
            auto seed = std::chrono::_V2::system_clock::now().time_since_epoch().count();
            std::default_random_engine engine(seed);

            using param_type = std::uniform_real_distribution<double>::param_type;
            param_type params{10.0, 40.0};

            return std::uniform_real_distribution<double>{params}(engine);
        }

    } // namespace detail


        template<typename T>
        class Random
        {
        public:

            Random() { }

            Random(T min, T max) :
                min_{min},
                max_{max} { }

            Random(std::size_t req_size, T min, T max) :
                size_{req_size},
                min_{min},
                max_{max} { }

            Random(const Matrix_size& req_size, T min, T max) :
                size_{req_size},
                min_{min},
                max_{max} { }

            Random(const Square_matrix_size& req_size, T min, T max) :
                size_{req_size},
                min_{min},
                max_{max} { }

            template<typename U>
            void set_size(U u)
            {
                size_ = u;
            }

            std::variant<Matrix_size, Square_matrix_size, std::size_t> size()
            {
                return size_;
            }

            Array<T> get(std::true_type)
            {
                auto size = std::visit(detail::Size_visitor{}, size_);
                Array<T> values(size);

                using dist_type = std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>;

                detail::Random_impl<dist_type> random{min_, max_};

                for(auto& x : values) x = random.get();

                return values;
            }

            Array<std::complex<T>> get(std::false_type)
            {
                auto size = std::visit(detail::Size_visitor{}, size_);
                Array<std::complex<T>> values(size);

                using dist_type = std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>;

                detail::Random_impl<dist_type> random{min_, max_};

                std::size_t count = 0;

                for(auto& x : values)
                {
                    std::complex<T> cplx;
                    cplx.real(random.get());
                    cplx.imag(random.get());
                    values[count++] = cplx;
                }

                return values;
            }

        private:

            std::variant<Matrix_size, Square_matrix_size, std::size_t> size_;
            T min_;
            T max_;

        };

} // namespace Axi

#endif // RANDOM_HPP
