#ifndef CADYA_MATH_HPP
#define CADYA_MATH_HPP

#include <cmath>
#include <concepts>
#include <numbers>

namespace cy {

template <std::floating_point F>
[[nodiscard]] constexpr auto radians_to_degrees(F radians) noexcept -> F
{
    constexpr auto f = F{180.0} / std::numbers::pi_v<F>;
    return radians * f;
}

template <std::floating_point F>
[[nodiscard]] constexpr auto degrees_to_radians(F degree) noexcept -> F
{
    constexpr auto f = F{180.0} / std::numbers::pi_v<F>;
    return degree / f;
}

template <std::integral I>
[[nodiscard]] constexpr auto degrees_to_radians(I degree) noexcept -> double
{
    return degrees_to_radians(static_cast<double>(degree));
}

} // namespace cy

#endif