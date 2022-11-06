#ifndef CADYA_GEOMETRY_INTERSECTION_HPP
#define CADYA_GEOMETRY_INTERSECTION_HPP

#include "circle.hpp"
#include "line_segment.hpp"

#include <boost/container/static_vector.hpp>

#include <optional>

namespace cdy {

auto intersection(
        LineSegment const& first,
        LineSegment const& second)
    -> std::optional<Coordinate>;

auto intersection(
        LineSegment const& line_segment,
        Circle const& circle)
    -> boost::container::static_vector<Coordinate, 2>;

auto intersection(
        Circle const& circle,
        LineSegment const& line_segment)
    -> boost::container::static_vector<Coordinate, 2>;

auto intersection(
        Circle const& first,
        Circle const& second)
    -> boost::container::static_vector<Coordinate, 2>;

} // namespace cdy

#endif
