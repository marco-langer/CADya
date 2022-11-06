#ifndef CADYA_GEOMETRY_LINE_SEGMENT_UTILS_HPP
#define CADYA_GEOMETRY_LINE_SEGMENT_UTILS_HPP

#include "coordinate.hpp"
#include "length.hpp"
#include "line_segment.hpp"

namespace cdy {

auto projected(
        LineSegment const& line_segment,
        Coordinate const& point)
    -> Coordinate;

auto distance(
        LineSegment const& line_segment,
        Coordinate const& point)
    -> Length;

auto is_close(
        LineSegment const& line_segment,
        Coordinate const& point,
        double epsilon)
    -> bool;

} // namespace cdy

#endif
