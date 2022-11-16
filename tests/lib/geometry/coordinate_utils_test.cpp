#include "matchers/coordinate_matcher.hpp"

#include "geometry/coordinate_utils.hpp"
#include "utility.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <ostream>

namespace cdy {

auto operator<<(std::ostream& os, cdy::ChoordinateOrientation orientation)
    -> std::ostream&
{
    switch (orientation) {
        case cdy::ChoordinateOrientation::Collinear: return os << "collinear";
        case cdy::ChoordinateOrientation::Counterclockwise: return os << "ccw";
        case cdy::ChoordinateOrientation::Clockwise: return os << "cw";
        default: cdy::unreachable();
    }
}

} // namespace cdy

TEST_CASE("geometry.coordinate_utils.orientation()") {

    auto [point1, point2, point3, expected_orientation] = GENERATE(
        table<cdy::Coordinate, cdy::Coordinate, cdy::Coordinate, cdy::ChoordinateOrientation>
    ({
        {{}, {}, {}, cdy::ChoordinateOrientation::Collinear},
        {{1.0, 1.0}, {1.0, 1.0}, {1.0, 1.0}, cdy::ChoordinateOrientation::Collinear},
        {{0.1, 0.2}, {0.1, 0.2}, {0.1, 0.2}, cdy::ChoordinateOrientation::Collinear},
        {{0.1, 0.2}, {0.1, 0.2}, {0.1, 0.3}, cdy::ChoordinateOrientation::Collinear},
        {{0.1, 0.3}, {0.2, 0.6}, {0.3, 0.9}, cdy::ChoordinateOrientation::Collinear},
        {{1.0, 3.0}, {2.0, 6.0}, {3.0, 9.0}, cdy::ChoordinateOrientation::Collinear},
        {{0.1, 0.3}, {0.2, 0.6}, {0.3, 0.8}, cdy::ChoordinateOrientation::Clockwise},
        {{0.1, 0.3}, {0.2, 0.6}, {0.3, 1.0}, cdy::ChoordinateOrientation::Counterclockwise},
        {{0.1, 0.0}, {0.0, 0.1}, {-0.1, 0.0}, cdy::ChoordinateOrientation::Counterclockwise},
        {{0.1, 0.0}, {0.0, -0.1}, {-0.1, 0.0}, cdy::ChoordinateOrientation::Clockwise},
    }));

    CAPTURE(point1, point2, point3, expected_orientation);

    REQUIRE(cdy::orientation(point1, point2, point3) == expected_orientation);
}
