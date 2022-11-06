#include "intersection.hpp"

namespace cdy {

auto intersection(
        LineSegment const& /* first */,
        LineSegment const& /* second */)
    -> std::optional<Coordinate>
{
    // TODO
    return {};
}

auto intersection(
        LineSegment const& /* line_segment */,
        Circle const& /* circle */)
    -> boost::container::static_vector<Coordinate, 2>
{
    // TODO
    return {};
}

auto intersection(
        Circle const& /* circle */,
        LineSegment const& /* line_segment */)
    -> boost::container::static_vector<Coordinate, 2>
{
    // TODO
    return {};
}

auto intersection(
        Circle const& /* first */,
        Circle const& /* second */)
    -> boost::container::static_vector<Coordinate, 2>
{
    // TODO
    return {};
}

} // namespace cdy
