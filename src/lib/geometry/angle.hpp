#ifndef CADYA_GEOMETRY_ANGLE_HPP
#define CADYA_GEOMETRY_ANGLE_HPP

#include "math.hpp"
#include "type_traits.hpp"

#include <cassert>
#include <cmath>
#include <compare>
#include <concepts>
#include <numbers>

namespace cdy {

namespace detail {

template <std::floating_point F>
constexpr auto degree_to_radian(F degrees) -> F
{
    return degrees / F{180.0} * std::numbers::pi_v<F>;
}

template <std::integral I>
constexpr auto degree_to_radian(I degrees) -> double
{
    return degree_to_radian(static_cast<double>(degrees));
}

template <std::floating_point F>
constexpr auto radian_to_degree(F radians) -> F
{
    return radians / std::numbers::pi_v<F> * F{180.0};
}

} // namespace detail

struct Degree {};
struct Radian {};

template <typename Unit>
concept AngleUnit = traits::is_any_of<Unit, Degree, Radian>;

template <AngleUnit Unit = Degree>
class Angle
{
public:
    Angle() = default;
    constexpr explicit Angle(double value)
        : value_{value}
    {
        assert(!is_nan(value));
        assert(!is_inf(value));
    }

    template <AngleUnit UnitOther>
    requires (!std::same_as<UnitOther, Unit>)
    constexpr Angle(Angle<UnitOther> other)
    {
        if constexpr (std::same_as<UnitOther, Radian>)
        {
            value_ = detail::radian_to_degree(other.value_);
        }
        else if constexpr (std::same_as<UnitOther, Degree>)
        {
            value_ = detail::degree_to_radian(other.value_);
        }
        else
        {
            static_assert(traits::dependent_false<UnitOther>);
        }
    }

    explicit constexpr operator double() const
    {
        return value_;
    }

    auto operator<=>(Angle const& other) const -> bool = default;

private:
    template <AngleUnit UnitOther>
    friend class Angle;

    double value_{};
};

template <AngleUnit Unit>
constexpr auto operator+(Angle<Unit> lhs, Angle<Unit> rhs) -> Angle<Unit>
{
    return Angle<Unit>{static_cast<double>(lhs) + static_cast<double>(rhs)};
}

namespace literals::angle_literals {

inline consteval auto operator ""_deg(long double value) -> Angle<Degree>
{
    return Angle<Degree>{static_cast<double>(value)};
}

inline consteval auto operator ""_deg(unsigned long long value) -> Angle<Degree>
{
    return Angle<Degree>{static_cast<double>(value)};
}

inline consteval auto operator ""_rad(long double value) -> Angle<Radian>
{
    return Angle<Radian>{static_cast<double>(value)};
}

inline consteval auto operator ""_rad(unsigned long long value) -> Angle<Radian>
{
    return Angle<Radian>{static_cast<double>(value)};
}

} // namespace cdy::literals::angle_literals

namespace numbers {

inline constexpr auto pi = Angle<Radian>{std::numbers::pi};

} // namespace cdy::numbers

} // namespace cdy

#endif
