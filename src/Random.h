#pragma once

#include <random>
#include <memory>

/** 
 * @brief  Basic random number generator
 */
class Random
{
private:
    std::unique_ptr<std::mt19937> m_engine;

public:
    static Random &Instance()
    {
        static Random instance;
        return instance;
    }
    /** 
	 * @brief  Function that returns a value between 
	 * min and max(inclusive for integer types, exclusive for
	 * floating point types) values
	 * @param  min: minimal value
	 * @param  max: maximal value
	 * @retval random number
	 */
    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    get(T min, T max)
    {
        std::uniform_real_distribution<T> d(min, max);
        return d(*m_engine);
    }

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    get(T min, T max)
    {
        std::uniform_int_distribution<T> d(min, max);
        return d(*m_engine);
    }

private:
    Random()
    {
        m_engine = std::make_unique<std::mt19937>(std::random_device()());
    }
    Random(const Random &) = delete;
    void operator=(const Random &) = delete;
};