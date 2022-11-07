#include "intersection.hpp"

#include "line_segment_utils.hpp"

#include <Eigen/Dense>

namespace cdy {

auto intersection(
        LineSegment const& first,
        LineSegment const& second)
    -> std::optional<Coordinate>
{
    // TODO compare (and benchmark both) this implemented solution with the one
    // suggested on SO using 2D-hyperplanes:
    // https://stackoverflow.com/a/50763846

    /*
     * first: (x1, y1), (x2, y2)
     * second: (x3, y3), (x4, y4)
     *
     * f(t)_x = x1 + t * (x2 - x1)
     * f(t)_y = y1 + t * (y2 - y1)
     *
     * g(u)_x = x3 + u * (x4 - x3)
     * g(u)_y = y3 + u * (y4 - y3)
     *
     * f(t)_x = g(u)_x
     * f(t)_y = g(u)_y
     *
     * =>
     *
     * x1 + t * (x2 - x1) = x3 + u * (x4 - x3)
     * y1 + t * (y2 - y1) = y3 + u * (y4 - y3)
     *
     * =>
     *
     * (x2 - x1) * t + (x3 - x4) * u = x3 - x1
     * (y2 - y1) * t + (y3 - y4) * u = y3 - y1
     *
     * =>
     *
     * ( a b ) * (z1) = ( f )
     * ( c d )   (z2) = ( g )
     *
     * a = x2 - x1
     * b = x3 - x4
     * c = y2 - y1
     * d = y3 - y4
     * f = x3 - x1
     * g = y3 - y1
     */
    // TODO why does the static assert triggers within the matrix constructor
    // and not within the vector constructor? Both are compile-time sized
    auto A = Eigen::Matrix2d{};
    A << first.second.x - first.first.x,
        second.first.x - second.second.x,
        first.second.y - first.first.y,
        second.first.y - second.second.y;

    auto const b = Eigen::Vector2d{
        second.first.x - first.first.x,
        second.first.y - first.first.y};

    auto const qr_decomp = A.colPivHouseholderQr();
    if (!qr_decomp.isInvertible())
    {
        return std::nullopt;
    }
    auto const result = static_cast<Eigen::Vector2d>(qr_decomp.solve(b));
    auto const t = result[0];
    auto const u = result[1];

    if (t < 0.0 || t > 1.0 || u < 0.0 || u > 1.0)
    {
        return std::nullopt;
    }
    else
    {
        return evaluate_at(first, t);
    }
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
        Circle const& circle,
        LineSegment const& line_segment)
    -> boost::container::static_vector<Coordinate, 2>
{
    return intersection(line_segment, circle);
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
