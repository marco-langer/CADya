#ifndef CADYA_GEOMETRY_LINE_SEGMENT_HPP
#define CADYA_GEOMETRY_LINE_SEGMENT_HPP

#include "geometry/coordinate.hpp"

#include <optional>

namespace cdy {

/* invariants: start != end */
class LineSegment
{
public:
    LineSegment(Coordinate const& start, Coordinate const& end);

    auto start() const -> Coordinate const&
    {
        return start_;
    }

    auto end() const -> Coordinate const&
    {
        return end_;
    }

private:
    Coordinate start_;
    Coordinate end_;
};

auto make_line_segment(
        Coordinate const& start,
        Coordinate const& end)
    -> std::optional<LineSegment>;

} // namespace cdy

#endif
