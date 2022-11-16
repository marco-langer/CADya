#ifndef CADYA_GEOMETRY_LINE_SEGMENT_UTILS_HPP
#define CADYA_GEOMETRY_LINE_SEGMENT_UTILS_HPP

#include "geometry/coordinate.hpp"
#include "geometry/length.hpp"
#include "geometry/line.hpp"
#include "geometry/line_segment.hpp"
#include "geometry/vector.hpp"

namespace cdy {

auto evaluate_at(LineSegment const& line_segment, double t) -> Coordinate;

auto midpoint(LineSegment const& line_segment)-> Coordinate;

auto tangent(LineSegment const& line_segment) -> Vector;

auto normal(LineSegment const& line_segment) -> Vector;

auto projected(
        LineSegment const& line_segment,
        Coordinate const& point)
    -> Coordinate;

auto distance(
        LineSegment const& line_segment,
        Coordinate const& point)
    -> Length;

auto is_near(
        LineSegment const& line_segment,
        Coordinate const& point,
        double epsilon)
    -> bool;

auto perpendicular_bisector(LineSegment const& line_segment) -> Line;

} // namespace cdy

#endif
