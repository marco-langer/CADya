#ifndef CADYA_POINT_HPP
#define CADYA_POINT_HPP

#include <kernel/traits.hpp>

#include <array>
#include <type_traits>
#include <utility>

namespace cy {

struct point_tag {};

template <typename T>
struct get_value_type;

template <typename T>
struct get_dimension;

template <typename T>
struct get_point_type;

template <std::floating_point F, std::size_t Dim>
struct basic_point;

template <std::floating_point F>
struct basic_point<F, 2>
{
    basic_point() = default;
    basic_point(F x, F y) : xs({x, y}) {}
    auto operator[](std::size_t i) const noexcept -> F const &
    {
        return xs[i];
    }
    auto operator[](std::size_t i) noexcept -> F &
    {
        return xs[i];
    }

    std::array<F, 2> xs;
};

template <std::floating_point F>
struct basic_point<F, 3>
{
    basic_point() = default;
    basic_point(F x, F y, F z = F{}) : xs({x, y, z}) {}
    auto operator[](std::size_t i) const noexcept -> F const &
    {
        return xs[i];
    }
    auto operator[](std::size_t i) noexcept -> F &
    {
        return xs[i];
    }

    std::array<F, 3> xs;
};

template <std::floating_point F, std::size_t Dim>
struct get_value_type<basic_point<F, Dim>>
{
    using type = F;
};

template <std::floating_point F, std::size_t Dim>
struct get_dimension<basic_point<F, Dim>>
{
    static constexpr auto value = Dim;
};

template <std::floating_point F, std::size_t Dim>
struct get_tag<basic_point<F, Dim>>
{
    using type = point_tag;
};

template <typename T>
concept Point = requires(T t)
{
    typename get_tag<T>::type;
    std::same_as<typename get_tag<T>::type, point_tag>;
};

template <std::floating_point F, std::size_t Dim>
auto operator+(basic_point<F, Dim> const & lhs, basic_point<F, Dim> const & rhs) noexcept
    -> basic_point<F, Dim>
{
    auto result = basic_point<F, Dim>{};
    [&]<std::size_t ...Is>(std::index_sequence<Is...>)
    {
        (..., (result.xs[Is] = lhs.xs[Is] + rhs.xs[Is]));
    }(std::make_index_sequence<Dim>());
    return result;
}

template <std::floating_point F, std::size_t Dim>
auto operator-(basic_point<F, Dim> const & lhs, basic_point<F, Dim> const & rhs) noexcept
    -> basic_point<F, Dim>
{
    auto result = basic_point<F, Dim>{};
    [&]<std::size_t ...Is>(std::index_sequence<Is...>)
    {
        (..., (result.xs[Is] = lhs.xs[Is] - rhs.xs[Is]));
    }(std::make_index_sequence<Dim>());
    return result;
}

template <std::floating_point F, std::size_t Dim>
auto operator*(basic_point<F, Dim> const & pt, F scalar) noexcept
    -> basic_point<F, Dim>
{
    auto result = basic_point<F, Dim>{};
    [&]<std::size_t ...Is>(std::index_sequence<Is...>)
    {
        (..., (result.xs[Is] = pt.xs[Is] * scalar));
    }(std::make_index_sequence<Dim>());
    return result;
}

template <std::floating_point F, std::size_t Dim>
auto operator*(F scalar, basic_point<F, Dim> const & pt) noexcept
    -> basic_point<F, Dim>
{
    return pt * scalar;
}

template <std::floating_point F, std::size_t Dim, std::integral I>
auto operator*(I scalar, basic_point<F, Dim> const & pt) noexcept
    -> basic_point<F, Dim>
{
    return pt * static_cast<F>(scalar);
}


} // namespace cy

#endif