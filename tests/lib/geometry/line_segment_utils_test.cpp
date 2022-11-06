#include "matchers/coordinate_matcher.hpp"
#include "matchers/line_segment_matcher.hpp"

#include "geometry/coordinate.hpp"
#include "geometry/length.hpp"
#include "geometry/line_segment_utils.hpp"
#include "geometry/trigonometry.hpp"
#include "geometry/vector_utils.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEST_CASE("geometry.LineSegment.projected()")
{
    auto const [line_segment, point, expected_result]
        = GENERATE(table<cdy::LineSegment, cdy::Coordinate, cdy::Coordinate>({
        {
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{-1.0, 0.0},
            cdy::Coordinate{1.0, 1.0}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{1.0, 1.0},
            cdy::Coordinate{1.0, 1.0}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{0.0, 3.0},
            cdy::Coordinate{1.0, 1.0}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{1.0, 3.5},
            cdy::Coordinate{2.0, 1.5}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{2.0, 1.5},
            cdy::Coordinate{2.0, 1.5}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{2.0, 4.0},
            cdy::Coordinate{3.0, 2.0}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{3.0, 2.0},
            cdy::Coordinate{3.0, 2.0}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{5.0, 2.0},
            cdy::Coordinate{3.0, 2.0}
        }
    }));

    CAPTURE(line_segment, point, expected_result);

    auto const projected_point = cdy::projected(line_segment, point);

    REQUIRE_THAT(projected_point, test::CoordinateMatcher(expected_result));
}

TEST_CASE("geometry.LineSegment.distance()")
{
    auto const [line_segment, point, expected_result]
        = GENERATE(table<cdy::LineSegment, cdy::Coordinate, cdy::Length>({
        {
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{-1.0, 0.0},
            cdy::distance(
                cdy::Coordinate{-1.0, 0.0},
                cdy::Coordinate{1.0, 1.0})
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{1.0, 1.0},
            cdy::Length{}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{0.0, 3.0},
            cdy::distance(
                cdy::Coordinate{0.0, 3.0},
                cdy::Coordinate{1.0, 1.0})
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{1.0, 3.5},
            cdy::distance(
                cdy::Coordinate{1.0, 3.5},
                cdy::Coordinate{2.0, 1.5})
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{2.0, 1.5},
            cdy::Length{}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{2.0, 4.0},
            cdy::distance(
                cdy::Coordinate{2.0, 4.0},
                cdy::Coordinate{3.0, 2.0})
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{3.0, 2.0},
            cdy::Length{}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{5.0, 2.0},
            cdy::distance(
                cdy::Coordinate{5.0, 2.0},
                cdy::Coordinate{3.0, 2.0})
        }
    }));

    CAPTURE(line_segment, point, expected_result);

    auto const distance = cdy::distance(line_segment, point);

    REQUIRE(distance == Catch::Approx(expected_result));
}
