#include "circle_utils.hpp"

#include "vector_utils.hpp"

#include <numbers>

namespace cdy {

auto is_inside(
        Circle const& circle,
        Coordinate const& point)
    -> bool
{
    return distance(circle.center, point) < circle.radius;
}

auto projected(
        Circle const& circle,
        Coordinate const& point)
    -> std::optional<Coordinate>
{
    // TODO floating point comparison
    if (circle.center == point) {
        return std::nullopt;
    }
    auto const direction = point - circle.center;
    auto const normalized_direction = direction / norm(direction);

    return circle.center + circle.radius * normalized_direction;
}

auto distance(
        Circle const& circle,
        Coordinate const& point)
    -> Length
{
    auto const maybe_projected_point = projected(circle, point);
    return maybe_projected_point.has_value()
        ? distance(*maybe_projected_point, point)
        : circle.radius;
}

auto is_close(
        Circle const& circle,
        Coordinate const& point,
        double epsilon)
    -> bool
{
    return distance(circle, point) <= epsilon;
}

} // namespace cdy
