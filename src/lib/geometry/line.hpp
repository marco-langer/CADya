#ifndef CADYA_GEOMETRY_LINE_HPP
#define CADYA_GEOMETRY_LINE_HPP

#include "geometry/angle.hpp"
#include "geometry/coordinate.hpp"
#include "geometry/vector.hpp"

#include <optional>

namespace cdy {

class Line
{
public:
    Line(Coordinate const& point, Vector const& normal);
    Line(Coordinate const& point, Angle<Radian> angle);
    Line(Coordinate const& point1, Coordinate const& point2);

    auto point() const -> Coordinate const&
    {
        return point_;
    }

    auto normal() const -> Vector const&
    {
        return normal_;
    }

private:
    Coordinate point_;
    Vector normal_;
};

auto make_line(Coordinate const& point, Vector const& vector) -> std::optional<Line>;
auto make_line(Coordinate const& point1, Coordinate const& point2) -> std::optional<Line>;

} // namespace cdy

#endif
