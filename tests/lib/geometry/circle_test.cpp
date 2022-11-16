#include "matchers/circle_matcher.hpp"
#include "matchers/coordinate_matcher.hpp"

#include "geometry/circle.hpp"
#include "geometry/coordinate.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <optional>

TEST_CASE("geometry.circle.make_circle()") {

    auto const [first, second, third, expected_circle] = GENERATE(table
        <
            cdy::Coordinate,
            cdy::Coordinate,
            cdy::Coordinate,
            std::optional<cdy::Circle>
        >({
        {
            {1.0, 1.0}, {1.0, 1.0}, {1.0, 1.0}, {}
        },{
            {1.0, 1.0}, {1.0, 1.0}, {1.0, 2.0}, {}
        },{
            {1.0, 1.0}, {1.0, 2.0}, {1.0, 3.0}, {}
        },{
            {0.0, 1.0}, {1.0, 2.0}, {2.0, 1.0},
            cdy::Circle{.center = {1.0, 1.0}, .radius = cdy::Length{2.0}}
        },
    }));

    CAPTURE(first, second, third);

    auto const maybe_circle = cdy::make_circle(first, second, third);

    REQUIRE(maybe_circle.has_value() == expected_circle.has_value());
    if (maybe_circle.has_value())
    {
        REQUIRE_THAT(*maybe_circle, test::CircleMatcher(*expected_circle));
    }
}
