#include "geometry/trigonometry.hpp"
#include "geometry/vector_utils.hpp"

#include <cassert>
#include <cmath>
#include <numbers>

namespace cdy {

auto sin(Angle<Radian> angle) -> double
{
    return std::sin(static_cast<double>(angle));
}

auto cos(Angle<Radian> angle) -> double
{
    return std::cos(static_cast<double>(angle));
}

auto angle(Vector const& first, Vector const& second) -> Angle<Radian>
{
    auto const norm_first = norm(first);
    auto const norm_second = norm(second);
    assert(norm_first > 0.0);
    assert(norm_second > 0.0);

    auto const dot_result = dot_product(first, second);
    auto const result = std::acos(dot_result / norm_first / norm_second);
    if (std::isnan(result)) [[unlikely]]
    {
        // TODO document why this branch is necessary
        return dot_result > 0.0 ? Angle<Radian>{} : Angle<Radian>{std::numbers::pi};
    }
    return Angle<Radian>{result};
}

auto direction(Angle<Radian> angle) -> Vector
{
    auto const x_axis = cdy::Vector{1.0, 0.0};
    auto const sine = sin(angle);
    auto const cosine = cos(angle);

    return cdy::Vector{
        .x = x_axis.x * cosine - x_axis.y * sine,
        .y = x_axis.x * sine + x_axis.y * cosine};
}

} // namespace cdy
