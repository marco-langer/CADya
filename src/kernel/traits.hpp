#ifndef CADYA_TRAITS_HPP
#define CADYA_TRAITS_HPP

#include <concepts>

namespace cy {

template <typename T>
struct get_tag;

template <typename T>
concept GeoObject = requires(T t)
{
    typename get_tag<T>::tag_t;
};

}

#endif