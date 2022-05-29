#ifndef CADYA_BOX_HPP
#define CADYA_BOX_HPP

#include <kernel/point.hpp>

#include <algorithm>
#include <iterator>

namespace cy {

struct box_tag {};

template <Point Point>
struct basic_box
{
    template <std::input_iterator InIt>
    requires std::same_as
    <
        Point,
        typename std::iterator_traits<InIt>::value_type
    >
    basic_box(InIt first, InIt last) noexcept
    {
        if (first == last)
        {
            return;
        }

        min = max = *first++;
        for (; first != last; ++first)
        {
            auto const pt = *first;
            // TODO unroll
            for (auto i{0u}; i < get_dimension<Point>::value; ++i)
            {
                if (pt[i] < min[i])
                {
                    min[i] = pt[i];
                }
                if (pt[i] > max[i])
                {
                    max[i] = pt[i];
                }
            }
        }
    }

    basic_box(Point const & first, Point const & second) noexcept
    requires (get_dimension<Point>::value == 3)
        : min({
            std::min(first[0], second[0]),
            std::min(first[1], second[1]),
            std::min(first[2], second[2])
        })
        , max({
            std::max(first[0], second[0]),
            std::max(first[1], second[1]),
            std::max(first[2], second[2])
        })
    {}

    basic_box(Point const & first, Point const & second) noexcept
    requires (get_dimension<Point>::value == 2)
        : min({
            std::min(first[0], second[0]),
            std::min(first[1], second[1]),
        })
        , max({
            std::max(first[0], second[0]),
            std::max(first[1], second[1]),
        })
    {}

    // TODO constructor with variadic Point args

    Point min{};
    Point max{};
};

template <Point Point>
struct get_tag<basic_box<Point>>
{
    using type = box_tag;
};

template <typename T>
concept Box = requires(T t)
{
    typename get_tag<T>::type;
    std::same_as<typename get_tag<T>::type, box_tag>;
};

}

#endif