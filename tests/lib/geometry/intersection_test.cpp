#include "matchers/coordinate_matcher.hpp"
#include "matchers/line_matcher.hpp"
#include "matchers/line_segment_matcher.hpp"

#include "geometry/circle.hpp"
#include "geometry/coordinate.hpp"
#include "geometry/intersection.hpp"
#include "geometry/line.hpp"
#include "geometry/line_segment.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <optional>

TEST_CASE("geometry.intersection.Line-Line")
{
    auto const [first, second, expected_intersection] = GENERATE(table
        <
            cdy::Line,
            cdy::Line,
            std::optional<cdy::Coordinate>
        >({
        { // intersecting
            cdy::Line{cdy::Coordinate{0.0, 1.0}, cdy::Coordinate{2.0, 1.0}},
            cdy::Line{cdy::Coordinate{1.0, 2.0}, cdy::Coordinate{1.0, 0.0}},
            cdy::Coordinate{1.0, 1.0}
        },{ // intersecting
            cdy::Line{cdy::Coordinate{0.0, 1.0}, cdy::Coordinate{2.0, 1.0}},
            cdy::Line{cdy::Coordinate{3.0, 2.0}, cdy::Coordinate{3.0, 0.0}},
            cdy::Coordinate{3.0, 1.0}
        },{ // coincident
            cdy::Line{cdy::Coordinate{0.0, 1.0}, cdy::Coordinate{1.0, 2.0}},
            cdy::Line{cdy::Coordinate{0.0, 1.0}, cdy::Coordinate{1.0, 2.0}},
            std::nullopt
        },{ // coincident
            cdy::Line{cdy::Coordinate{0.0, 1.0}, cdy::Coordinate{1.0, 2.0}},
            cdy::Line{cdy::Coordinate{1.0, 2.0}, cdy::Coordinate{0.0, 1.0}},
            std::nullopt
        },{ // parallel
            cdy::Line{cdy::Coordinate{0.0, 1.0}, cdy::Coordinate{1.0, 2.0}},
            cdy::Line{cdy::Coordinate{1.0, 2.0}, cdy::Coordinate{2.0, 3.0}},
            std::nullopt
        },{ // parallel
            cdy::Line{cdy::Coordinate{0.0, 1.0}, cdy::Coordinate{1.0, 2.0}},
            cdy::Line{cdy::Coordinate{2.0, 3.0}, cdy::Coordinate{1.0, 2.0}},
            std::nullopt
        }
    }));

    CAPTURE(first, second);

    auto const maybe_intersection = cdy::intersection(first, second);

    REQUIRE(maybe_intersection.has_value() == expected_intersection.has_value());
    if (maybe_intersection.has_value())
    {
        REQUIRE_THAT(*maybe_intersection, test::CoordinateMatcher(*expected_intersection));
    }
}

TEST_CASE("geometry.intersection.LineSegment-LineSegment")
{
    auto const [first, second, expected_intersection] = GENERATE(table
        <
            cdy::LineSegment,
            cdy::LineSegment,
            std::optional<cdy::Coordinate>
        >({
        {
            cdy::LineSegment{{0.0, 1.0}, {2.0, 1.0}},
            cdy::LineSegment{{1.0, 2.0}, {1.0, 0.0}},
            cdy::Coordinate{1.0, 1.0}
        },{
            cdy::LineSegment{{0.0, 1.0}, {2.0, 1.0}},
            cdy::LineSegment{{3.0, 2.0}, {3.0, 0.0}},
            std::nullopt
        },{
            cdy::LineSegment{{0.0, 1.0}, {2.0, 1.0}},
            cdy::LineSegment{{-1.0, 2.0}, {3.0, 2.0}},
            std::nullopt
        },{
            cdy::LineSegment{{0.0, 1.0}, {2.0, 1.0}},
            cdy::LineSegment{{2.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{2.0, 1.0}
        }
    }));

    CAPTURE(first, second);

    auto const maybe_intersection = cdy::intersection(first, second);

    REQUIRE(maybe_intersection.has_value() == expected_intersection.has_value());
    if (maybe_intersection.has_value())
    {
        REQUIRE_THAT(*maybe_intersection, test::CoordinateMatcher(*expected_intersection));
    }
}

TEST_CASE("geometry.intersection.LineSegment-Circle")
{
    REQUIRE(false);
}

TEST_CASE("geometry.intersection.Circle-Circle")
{
    REQUIRE(false);
}
