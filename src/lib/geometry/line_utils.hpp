#ifndef CADYA_GEOMETRY_LINE_UTILS_HPP
#define CADYA_GEOMETRY_LINE_UTILS_HPP

#include "geometry/line.hpp"

namespace cdy {

// TODO add perpendicular to this enum?
enum class LineOrientation { Parallel, Intersecting, Coincident };

auto orientation(Line const& first, Line const& second) -> LineOrientation;

} // namespace cdy

#endif
