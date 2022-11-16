#include "geometry/line.hpp"

#include "geometry/line_segment.hpp"
#include "geometry/line_segment_utils.hpp"
#include "geometry/trigonometry.hpp"
#include "geometry/vector_utils.hpp"
#include "math.hpp"

#include <cassert>

namespace cdy {

Line::Line(Coordinate const& point, Vector const& normal)
    : point_{point}
    , normal_{normal}
{
    assert(is_approx_same(norm(normal), 1.0));
}

Line::Line(Coordinate const& point, Angle<Radian> angle)
    : point_{point}
    , normal_{direction(angle + numbers::pi)}
{}

Line::Line(Coordinate const& point1, Coordinate const& point2)
    : point_{point1}
    , normal_{cdy::normal(LineSegment{point1, point2})}
{}

auto make_line(Coordinate const& point, Vector const& vector) -> std::optional<Line>
{
    auto const vector_length = norm(vector);
    return is_zero(vector_length)
        ? std::nullopt
        : std::optional<Line>{Line{point, vector / vector_length}};
}

auto make_line(Coordinate const& point1, Coordinate const& point2) -> std::optional<Line>
{
    return make_line(point1, point2 - point1);
}

} // namespace cdy
