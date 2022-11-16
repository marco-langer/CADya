#include "geometry/line_segment_utils.hpp"

#include "geometry/vector_utils.hpp"

namespace cdy {

auto evaluate_at(LineSegment const& line_segment, double t) -> Coordinate
{
    return line_segment.start() + t * (line_segment.end() - line_segment.start());
}

auto midpoint(LineSegment const& line_segment) -> Coordinate
{
    return evaluate_at(line_segment, 0.5);
}

auto tangent(LineSegment const& line_segment) -> Vector
{
    auto const direction = line_segment.end() - line_segment.start();
    auto const direction_length = norm(direction);
    assert(direction_length > 0.0);
    return direction / direction_length;
}

auto normal(LineSegment const& line_segment) -> Vector
{
    auto const tangent_vector = tangent(line_segment);
    return {-tangent_vector.y, tangent_vector.x};
}

auto projected(
        LineSegment const& line_segment,
        Coordinate const& point)
    -> Coordinate
{
    auto const v = line_segment.end() - line_segment.start();
    auto const w = point - line_segment.start();

    auto const c1 = dot_product(v, w);
    if (c1 <= 0.0)
    {
        return line_segment.start();
    }

    auto const c2 = dot_product(v, v);
    if (c2 <= c1)
    {
        return line_segment.end();
    }

    return line_segment.start() + c1/c2 * v;
}

auto distance(
        LineSegment const& line_segment,
        Coordinate const& point)
    -> Length
{
    auto const projected_point = projected(line_segment, point);
    return distance(projected_point, point);
}

auto is_near(
        LineSegment const& line_segment,
        Coordinate const& point,
        double epsilon)
    -> bool
{
    return distance(line_segment, point) <= epsilon;
}

auto perpendicular_bisector(LineSegment const& line_segment) -> Line
{
    return Line{midpoint(line_segment), tangent(line_segment)};
}

} // namespace cdy
