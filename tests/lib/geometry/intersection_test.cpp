#include "matchers/coordinate_matcher.hpp"

#include "geometry/coordinate.hpp"
#include "geometry/intersection.hpp"
#include "geometry/line_segment.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <optional>

TEST_CASE("geometry.intersection.line-line")
{
    auto const [first, second, expected_result]
        = GENERATE(table<cdy::LineSegment, cdy::LineSegment, std::optional<cdy::Coordinate>>({
        {
            cdy::LineSegment{{0.0, 1.0}, {2.0, 1.0}},
            cdy::LineSegment{{1.0, 2.0}, {1.0, 0.0}},
            cdy::Coordinate{1.0, 1.0}
        },{
            cdy::LineSegment{{0.0, 1.0}, {2.0, 1.0}},
            cdy::LineSegment{{3.0, 2.0}, {3.0, 0.0}},
            std::nullopt
        }
    }));

    CAPTURE(first, second);

    auto const maybe_result = cdy::intersection(first, second);

    REQUIRE(maybe_result.has_value() == expected_result.has_value());
    if (maybe_result.has_value())
    {
        REQUIRE_THAT(*maybe_result, test::CoordinateMatcher(*expected_result));
    }
}

TEST_CASE("geometry.intersection.line-circle")
{
    REQUIRE(false);
}

TEST_CASE("geometry.intersection.circle-circle")
{
    REQUIRE(false);
}
