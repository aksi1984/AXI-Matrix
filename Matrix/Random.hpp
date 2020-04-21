#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <chrono>
#include <variant>
#include <algorithm>

#include "Arrays.hpp"
#include "Matrix_size.hpp"
#include "Traits.hpp"
#include "Cond.hpp"

namespace linarg
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
            typename std::mt19937::result_type seed = std::chrono::_V2::system_clock::now().time_since_epoch().count();
            engine_.seed(seed);
        }

        std::mt19937 engine_;
        distribution dist_;
        params params_;
    };

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

        template<typename U>
        void apply_size(U u)
        {
            size_ = u;
        }

        std::variant<Matrix_size, std::size_t> size()
        {
            return size_;
        }

        Array<T> get()
        {
            auto size = std::visit(Size_visitor{}, size_);
            Array<T> numbers(size);

            using dist_type = std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>;

            Random_impl<dist_type> random{min_, max_};

            for(auto& x : numbers) x = random.get();

            return numbers;
        }

    private:

        std::variant<Matrix_size, std::size_t> size_;
        T min_;
        T max_;
    };


        Array<std::size_t> random_locations(const Matrix_size& size, double density)
        {
            //double n = static_cast<double>(size.rows_ * size.cols_);
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



} // namespace Axi

#endif // RANDOM_HPP
