#ifndef CADYA_GEOMETRY_CIRCLE_HPP
#define CADYA_GEOMETRY_CIRCLE_HPP

#include "geometry/coordinate.hpp"
#include "geometry/length.hpp"

#include <optional>

namespace cdy {

struct Circle
{
    Coordinate center;
    Length radius;
};

auto make_circle(
        Coordinate const& first,
        Coordinate const& second,
        Coordinate const& third)
    -> std::optional<Circle>;

} // namespace cdy

#endif
