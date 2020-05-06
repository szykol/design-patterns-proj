#pragma once

#include <random>
#include <memory>

template <typename T>
class RandRange
{
    std::vector<T> m_range;

public:
    RandRange(std::vector<T> range)
    {
        m_range = std::move(range);
    }

    auto begin() -> decltype(m_range.begin())
    {
        return m_range.begin();
    }

    auto end() -> decltype(m_range.end())
    {
        return m_range.end();
    }

    constexpr auto cbegin() -> decltype(m_range.cbegin())
    {
        return m_range.cbegin();
    }

    constexpr auto cend() -> decltype(m_range.cend())
    {
        return m_range.cend();
    }
};

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

    /** 
	 * @brief  Function that returns a range of values between 
	 * min and max(inclusive for integer types, exclusive for
	 * floating point types)
	 * @param  min:  minimal value
	 * @param  max:  maximal value
     * @param  size: size of range
	 * @retval random number
	 */
    template <typename T>
    RandRange<T>
    get_range(T min, T max, size_t size)
    {
        std::vector<T> temp;
        temp.reserve(size);

        for (size_t i = 0; i < size; i++)
        {
            temp.emplace_back(get<T>(min, max));
        }
        return RandRange<T>(temp);
    }

private:
    Random()
    {
        m_engine = std::make_unique<std::mt19937>(std::random_device()());
    }
    Random(const Random &) = delete;
    void operator=(const Random &) = delete;
};