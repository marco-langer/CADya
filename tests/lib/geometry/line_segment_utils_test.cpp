#include "matchers/coordinate_matcher.hpp"
#include "matchers/line_matcher.hpp"
#include "matchers/line_segment_matcher.hpp"
#include "matchers/vector_matcher.hpp"

#include "geometry/coordinate.hpp"
#include "geometry/length.hpp"
#include "geometry/line_segment_utils.hpp"
#include "geometry/trigonometry.hpp"
#include "geometry/vector_utils.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEST_CASE("geometry.line_segment_utils.evaluate_at()")
{
    auto const [line_segment, t, expected_point]
        = GENERATE(table<cdy::LineSegment, double, cdy::Coordinate>({
        {
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            0.0,
            cdy::Coordinate{1.0, 1.0}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            0.5,
            cdy::Coordinate{2.0, 1.5}
        },{
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            1.0,
            cdy::Coordinate{3.0, 2.0}
        }
    }));

    CAPTURE(line_segment, t, expected_point);

    REQUIRE_THAT(cdy::evaluate_at(line_segment, t), test::CoordinateMatcher(expected_point));
}

TEST_CASE("geometry.line_segment_utils.midpoint()")
{
    auto const [line_segment, expected_point]
        = GENERATE(table<cdy::LineSegment, cdy::Coordinate>({
        {
            cdy::LineSegment{{1.0, 1.0}, {3.0, 2.0}},
            cdy::Coordinate{2.0, 1.5}
        }
    }));

    CAPTURE(line_segment, expected_point);

    REQUIRE_THAT(cdy::midpoint(line_segment), test::CoordinateMatcher(expected_point));
}

TEST_CASE("geometry.line_segment_utils.tangent()")
{
    auto const [line_segment, expected_tangent]
        = GENERATE(table<cdy::LineSegment, cdy::Vector>({
        {
            cdy::LineSegment{{1.0, 1.0}, {2.0, 1.0}},
            cdy::Vector{1.0, 0.0}
        },{
            cdy::LineSegment{{1.0, 1.0}, {1.0, 2.0}},
            cdy::Vector{0.0, 1.0}
        },{
            cdy::LineSegment{{1.0, 1.0}, {2.0, 2.0}},
            cdy::Vector{1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0)}
        }
    }));

    CAPTURE(line_segment, expected_tangent);

    REQUIRE_THAT(cdy::tangent(line_segment), test::VectorMatcher(expected_tangent));
}

TEST_CASE("geometry.line_segment_utils.normal()")
{
    auto const [line_segment, expected_normal]
        = GENERATE(table<cdy::LineSegment, cdy::Vector>({
        {
            cdy::LineSegment{{1.0, 1.0}, {2.0, 1.0}},
            cdy::Vector{0.0, 1.0}
        },{
            cdy::LineSegment{{1.0, 1.0}, {1.0, 2.0}},
            cdy::Vector{-1.0, 0.0}
        },{
            cdy::LineSegment{{1.0, 1.0}, {2.0, 2.0}},
            cdy::Vector{-1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0)}
        }
    }));

    CAPTURE(line_segment, expected_normal);

    REQUIRE_THAT(cdy::normal(line_segment), test::VectorMatcher(expected_normal));
}

TEST_CASE("geometry.line_segment_utils.projected()")
{
    auto const [line_segment, point, expected_projected]
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

    CAPTURE(line_segment, point, expected_projected);

    auto const projected_point = cdy::projected(line_segment, point);

    REQUIRE_THAT(projected_point, test::CoordinateMatcher(expected_projected));
}

TEST_CASE("geometry.line_segment_utils.distance()")
{
    auto const [line_segment, point, expected_distance]
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

    CAPTURE(line_segment, point, expected_distance);

    auto const distance = cdy::distance(line_segment, point);

    REQUIRE(distance == Catch::Approx(expected_distance));
}

TEST_CASE("geometry.line_segment_utils.perpendicular_bisector()")
{
    auto [line_segment, expected_bisector] = GENERATE(
        table<cdy::LineSegment, cdy::Line>({
        {
            cdy::LineSegment{{1.0, 1.0}, {3.0, 1.0}},
            cdy::Line{cdy::Coordinate{2.0, 0.0}, cdy::Coordinate{2.0, 2.0}}
        }
    }));

    CAPTURE(line_segment, expected_bisector);

    REQUIRE_THAT(cdy::perpendicular_bisector(line_segment),
        test::LineMatcher(expected_bisector));
}
