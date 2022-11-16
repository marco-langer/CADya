#include "matchers/line_matcher.hpp"

#include "geometry/line_utils.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using namespace cdy::literals::angle_literals;

TEST_CASE("geometry.line_utils.orientation()")
{
    auto const [first, second, expected_orientation] = GENERATE(
        table<cdy::Line, cdy::Line, cdy::LineOrientation>({
        {
            cdy::Line{{1.0, 1.0}, 45_deg},
            cdy::Line{{1.0, 2.0}, 45_deg},
            cdy::LineOrientation::Parallel
        },{
            cdy::Line{{1.0, 1.0}, 45_deg},
            cdy::Line{{1.0, 2.0}, 225_deg},
            cdy::LineOrientation::Parallel
        },{
            cdy::Line{{1.0, 1.0}, 45_deg},
            cdy::Line{{1.0, 2.0}, 90_deg},
            cdy::LineOrientation::Intersecting
        },{
            cdy::Line{{1.0, 1.0}, 45_deg},
            cdy::Line{{1.0, 1.0}, 45_deg},
            cdy::LineOrientation::Coincident
        },{
            cdy::Line{{1.0, 1.0}, 45_deg},
            cdy::Line{{2.0, 2.0}, 225_deg},
            cdy::LineOrientation::Coincident
        }
    }));

    CAPTURE(first, second, expected_orientation);

    REQUIRE(cdy::orientation(first, second) == expected_orientation);
}
