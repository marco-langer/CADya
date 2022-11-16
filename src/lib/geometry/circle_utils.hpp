#ifndef CADYA_GEOMETRY_CIRCLE_UTILS_HPP
#define CADYA_GEOMETRY_CIRCLE_UTILS_HPP

#include "geometry/circle.hpp"
#include "geometry/coordinate.hpp"

#include <optional>

namespace cdy {

auto is_inside(
        Circle const& circle,
        Coordinate const& point)
    -> bool;

auto projected(
        Circle const& circle,
        Coordinate const& point)
    -> std::optional<Coordinate>;

auto distance(
        Circle const& circle,
        Coordinate const& point)
    -> Length;

auto is_close(
        Circle const& circle,
        Coordinate const& point,
        double epsilon)
    -> bool;

} // namespace cdy

#endif
