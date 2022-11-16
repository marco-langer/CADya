#include "matchers/angle_matcher.hpp"
#include "matchers/coordinate_matcher.hpp"
#include "matchers/line_matcher.hpp"
#include "matchers/vector_matcher.hpp"

#include "geometry/line.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <cmath>

using namespace cdy::literals::angle_literals;

TEST_CASE("geometry.line.line() point-angle")
{
    auto [point, angle, expected_normal] = GENERATE(
        table<cdy::Coordinate, cdy::Angle<cdy::Radian>, cdy::Vector>({
        {{1.0, 1.0}, 0_deg, {-1.0, 0.0}},
        {{1.0, 1.0}, 45_deg, {-1.0 / std::sqrt(2.0), -1.0 / std::sqrt(2.0)}},
    }));

    CAPTURE(point, angle, expected_normal);

    auto const line = cdy::Line{point, angle};

    REQUIRE_THAT(line.point(), test::CoordinateMatcher(point));
    REQUIRE_THAT(line.normal(), test::VectorMatcher(expected_normal));
}

TEST_CASE("geometry.line.line() point-point")
{
    auto [point1, point2, expected_normal] = GENERATE(
        table<cdy::Coordinate, cdy::Coordinate, cdy::Vector>({
        {{1.0, 1.0}, {2.0, 1.0}, {0.0, 1.0}},
        {{1.0, 1.0}, {2.0, 2.0}, {-1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0)}},
    }));

    CAPTURE(point1, point2, expected_normal);

    auto const line = cdy::Line{point1, point2};

    REQUIRE_THAT(line.point(), test::CoordinateMatcher(point1));
    REQUIRE_THAT(line.normal(), test::VectorMatcher(expected_normal));
}
