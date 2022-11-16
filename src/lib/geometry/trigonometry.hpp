#ifndef CADYA_GEOMETRY_TRIGONOMETRY_HPP
#define CADYA_GEOMETRY_TRIGONOMETRY_HPP

#include "geometry/angle.hpp"
#include "geometry/vector.hpp"

namespace cdy {

auto sin(Angle<Radian> angle) -> double;
auto cos(Angle<Radian> angle) -> double;
auto angle(Vector const& first, Vector const& second) -> Angle<Radian>;
auto direction(Angle<Radian> angle) -> Vector;

} // namespace cdy

#endif
