#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <chrono>

#include "Arrays.hpp"
#include "Matrix_size.hpp"
#include "Traits.hpp"

namespace linarg
{
    namespace rd
    {
        struct Rd_mat { };
        struct Rd_vec { };
        struct Rd_spmat { };
        struct Rd_spvec { };

        template<typename T>
        class Random_base
        {
        public:

            using result_type   = T;

            Random_base(std::size_t n) :
                vec_size_{n} { }

            Random_base(const Matrix_size& mat_size) :
                vec_size_{},
                mat_size_{mat_size} { }

            virtual ~Random_base() { }

            std::size_t vec_size() const noexcept
            {
                return vec_size_;
            }

            Matrix_size mat_size() const
            {
                return mat_size_;
            }

            virtual T get() = 0;

        private:

            std::size_t vec_size_;
            Matrix_size mat_size_;
        };

        template<typename Dist, typename Engine>
        class Random : public Random_base<typename Dist::result_type>
        {
        public:

            using distribution      = Dist;
            using params            = typename distribution::param_type;
            using result_type       = typename distribution::result_type;
            using engine            = Engine;

            Random(std::size_t n, result_type val) :
                Random_base<typename Dist::result_type> (n),
                dist_{params{val}}
            {                
                add_seed();
            }

            Random(std::size_t n, result_type min, result_type max) :
                Random_base<typename Dist::result_type> (n),
                dist_{params{min, max}}
            {          
                add_seed();
            }

            Random(const Matrix_size& mat_size, result_type val) :
                Random_base<typename Dist::result_type>(mat_size),
                dist_{params{val}}
            {
                add_seed();
            }

            Random(const Matrix_size& mat_size, result_type min, result_type max) :
                Random_base<typename Dist::result_type> (mat_size),
                dist_{params{min, max}}
            {
                add_seed();
            }

            virtual result_type get() override
            {
                return dist_(engine_);
            }

        private:

            void add_seed()
            {
                typename engine::result_type seed = std::chrono::_V2::system_clock::now().time_since_epoch().count();
                engine_.seed(seed);
            }

            engine engine_;
            distribution dist_;
        };

        template<typename Dist, typename Engine>
        class Sparse_random : public Random<Dist, Engine>
        {
        public:

            using distribution      = typename Random<Dist, Engine>::distribution;
            using params            = typename distribution::param_type;
            using result_type       = typename distribution::result_type;
            using engine            = Engine;

            Sparse_random(const Matrix_size& size, result_type val) :
                Random<Dist, Engine>(size, val) { }

            Sparse_random(const Matrix_size& size, result_type min, result_type max) :
                Random<Dist, Engine>(size, min, max)
            {
                random_locations();
            }

            Unbounded_array<std::size_t> get_locations() const noexcept
            {
                return locations_;
            }

        private:

            void random_locations()
            {
                std::size_t max_elem = Random_base<typename distribution::result_type>::mat_size().rows_ *
                                       Random_base<typename distribution::result_type>::mat_size().cols_;

                std::size_t half_of_max = (max_elem / 2) - 1;

                auto seed = std::chrono::_V2::system_clock::now().time_since_epoch().count();
                std::default_random_engine engine(seed);
                std::uniform_int_distribution<std::size_t> dist(1, half_of_max);

                std::size_t elems = dist(engine);

                locations_.resize(elems);

                for(std::size_t i = 0; i < elems; ++i)
                {
                    locations_[i] = dist(engine);
                }

                for(std::size_t i = 0; i < elems; ++i)
                {
                    std::cout << locations_[i] << ' ';
                }
            }

             Unbounded_array<std::size_t> locations_;
        };

        Array<std::size_t> random_locations(const Matrix_size& size, double density)
        {
            double n = static_cast<double>(size.rows_ * size.cols_);
            std::size_t elems = static_cast<std::size_t>((density / 100.0) * n);

            auto seed = std::chrono::_V2::system_clock::now().time_since_epoch().count();
            std::default_random_engine engine(seed);
            std::uniform_int_distribution<std::size_t> dist(0, size.rows_ * size.cols_);

            Array<std::size_t> locations(elems);

            for(std::size_t i = 0; i < locations.size(); ++i)
            {
                locations[i] = dist(engine);
            }

            return locations;
        }

        ////////////////////////////////////////////////

        template<typename T>
        using Rd_ptr = std::shared_ptr<Random_base<T>>;

        template<typename RdType1, typename RdType2>
        void assertion()
        {
            static_assert (std::is_same<RdType1, RdType2>::value, "Uncorrect random constructor");
        }

        //

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> int_mt19937(std::size_t size, T val)
        {
            assertion<RdType, Rd_vec>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937>>(new Random<std::uniform_int_distribution<T>, std::mt19937>(size, val));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> int_mt19937(std::size_t size, T min, T max)
        {
            assertion<RdType, Rd_vec>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937>>(new Random<std::uniform_int_distribution<T>, std::mt19937>(size, min, max));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> int_mt19937(const Matrix_size& size, T min, T max)
        {
            assertion<RdType, Rd_mat>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937>>(new Random<std::uniform_int_distribution<T>, std::mt19937>(size, min, max));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> int_mt19937(const Matrix_size& size, T val)
        {
            assertion<RdType, Rd_mat>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937>>(new Random<std::uniform_int_distribution<T>, std::mt19937>(size, val));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        Rd_ptr<T> real_mt19937(std::size_t size, T min, T max)
        {
            assertion<RdType, Rd_vec>();

            return std::shared_ptr<Random<std::uniform_real_distribution<T>, std::mt19937>>(new Random<std::uniform_real_distribution<T>, std::mt19937>(size, min, max));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        Rd_ptr<T> real_mt19937(std::size_t size, T val)
        {
            assertion<RdType, Rd_vec>();

            return std::shared_ptr<Random<std::uniform_real_distribution<T>, std::mt19937>>(new Random<std::uniform_real_distribution<T>, std::mt19937>(size, val));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        Rd_ptr<T> real_mt19937(const Matrix_size& size, T min, T max)
        {
            assertion<RdType, Rd_mat>();

            return std::shared_ptr<Random<std::uniform_real_distribution<T>, std::mt19937>>(new Random<std::uniform_real_distribution<T>, std::mt19937>(size, min, max));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        Rd_ptr<T> real_mt19937(const Matrix_size& size, T val)
        {
            assertion<RdType, Rd_mat>();

            return std::shared_ptr<Random<std::uniform_real_distribution<T>, std::mt19937>>(new Random<std::uniform_real_distribution<T>, std::mt19937>(size, val));
        }

        //

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> int_mt19937_64(std::size_t size, T val)
        {
            assertion<RdType, Rd_vec>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937_64>>(new Random<std::uniform_int_distribution<T>, std::mt19937_64>(size, val));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> int_mt19937_64(std::size_t size, T min, T max)
        {
            assertion<RdType, Rd_vec>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937_64>>(new Random<std::uniform_int_distribution<T>, std::mt19937_64>(size, min, max));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> int_mt19937_64(const Matrix_size& size, T min, T max)
        {
            assertion<RdType, Rd_mat>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937_64>>(new Random<std::uniform_int_distribution<T>, std::mt19937_64>(size, min, max));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> int_mt19937_64(const Matrix_size& size, T val)
        {
            assertion<RdType, Rd_mat>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937_64>>(new Random<std::uniform_int_distribution<T>, std::mt19937_64>(size, val));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        Rd_ptr<T> real_mt19937_64(std::size_t size, T min, T max)
        {
            assertion<RdType, Rd_vec>();

            return std::shared_ptr<Random<std::uniform_real_distribution<T>, std::mt19937_64>>(new Random<std::uniform_real_distribution<T>, std::mt19937_64>(size, min, max));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        Rd_ptr<T> real_mt19937_64(std::size_t size, T val)
        {
            assertion<RdType, Rd_vec>();

            return std::shared_ptr<Random<std::uniform_real_distribution<T>, std::mt19937_64>>(new Random<std::uniform_real_distribution<T>, std::mt19937_64>(size, val));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        Rd_ptr<T> real_mt19937_64(const Matrix_size& size, T min, T max)
        {
            assertion<RdType, Rd_mat>();

            return std::shared_ptr<Random<std::uniform_real_distribution<T>, std::mt19937_64>>(new Random<std::uniform_real_distribution<T>, std::mt19937_64>(size, min, max));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
        Rd_ptr<T> real_mt19937_64(const Matrix_size& size, T val)
        {
            assertion<RdType, Rd_mat>();

            return std::shared_ptr<Random<std::uniform_real_distribution<T>, std::mt19937_64>>(new Random<std::uniform_real_distribution<T>, std::mt19937_64>(size, val));
        }

        //

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> sp_int_mt19937(std::size_t size, T val)
        {
            assertion<RdType, Rd_spvec>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937>>(new Random<std::uniform_int_distribution<T>, std::mt19937>(size, val));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> sp_int_mt19937(std::size_t size, T min, T max)
        {
            assertion<RdType, Rd_spvec>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937>>(new Random<std::uniform_int_distribution<T>, std::mt19937>(size, min, max));
        }

        template<typename T, typename RdType, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        Rd_ptr<T> sp_int_mt19937(const Matrix_size& size, T min, T max)
        {
            assertion<RdType, Rd_spmat>();

            return std::shared_ptr<Random<std::uniform_int_distribution<T>, std::mt19937>>(new Random<std::uniform_int_distribution<T>, std::mt19937>(size, min, max));
        }

    } // namespace rd

} // namespace Axi

#endif // RANDOM_HPP
