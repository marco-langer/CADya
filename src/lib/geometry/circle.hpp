#ifndef CADYA_GEOMETRY_CIRCLE_HPP
#define CADYA_GEOMETRY_CIRCLE_HPP

#include "coordinate.hpp"
#include "length.hpp"

namespace cdy {

struct Circle
{
    Coordinate center;
    Length radius;
};

} // namespace cdy

#endif
