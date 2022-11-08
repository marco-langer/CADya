#include "geometry/trigonometry.hpp"
#include "geometry/vector_utils.hpp"

#include <cassert>
#include <cmath>
#include <numbers>

namespace cdy {

auto sin(Angle<Radian> radians) -> double
{
    return std::sin(static_cast<double>(radians));
}

auto cos(Angle<Radian> radians) -> double
{
    return std::cos(static_cast<double>(radians));
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

} // namespace cdy
