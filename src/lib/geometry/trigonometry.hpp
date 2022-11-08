#ifndef CADYA_GEOMETRY_TRIGONOMETRY_HPP
#define CADYA_GEOMETRY_TRIGONOMETRY_HPP

#include "geometry/angle.hpp"
#include "geometry/vector.hpp"

namespace cdy {

auto sin(Angle<Radian> radians) -> double;
auto cos(Angle<Radian> radians) -> double;
auto angle(Vector const& first, Vector const& second) -> Angle<Radian>;

} // namespace cdy

#endif
