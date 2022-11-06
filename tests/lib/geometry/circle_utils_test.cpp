#include "matchers/circle_matcher.hpp"
#include "matchers/coordinate_matcher.hpp"

#include "geometry/circle_utils.hpp"
#include "geometry/coordinate.hpp"
#include "geometry/length.hpp"
#include "geometry/trigonometry.hpp"
#include "geometry/vector_utils.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <optional>

TEST_CASE("geometry.circle_utils.is_inside()")
{
    auto const [circle, point, expected_result]
        = GENERATE(table<cdy::Circle, cdy::Coordinate, bool>({
        {
            cdy::Circle{.center = {}, .radius = {}},
            cdy::Coordinate{},
            false
        },{
            cdy::Circle{.center = {}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{},
            true
        },{
            cdy::Circle{.center = {}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{0.5, 0.2},
            true
        },{
            cdy::Circle{.center = {}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{1.5, 0.2},
            false
        },{
            cdy::Circle{.center = {1.0, 2.0}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{1.5, 2.2},
            true
        },{
            cdy::Circle{.center = {1.0, 2.0}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{2.5, 2.2},
            false
        }
    }));

    CAPTURE(circle, point, expected_result);

    REQUIRE(cdy::is_inside(circle, point) == expected_result);
}

TEST_CASE("geometry.circle_utils.projected()")
{
    auto const [circle, point, expected_result]
        = GENERATE(table<cdy::Circle, cdy::Coordinate, std::optional<cdy::Coordinate>>({
        {
            cdy::Circle{.center = {}, .radius = {}},
            cdy::Coordinate{},
            std::nullopt
        },{
            cdy::Circle{.center = {}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{},
            std::nullopt
        },{
            cdy::Circle{.center = {}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{0.5, 0.0},
            cdy::Coordinate{1.0, 0.0}
        },{
            cdy::Circle{.center = {1.0, 2.0}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{1.5, 2.0},
            cdy::Coordinate{2.0, 2.0}
        },{
            cdy::Circle{.center = {1.0, 1.0}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{1.5, 1.5},
            cdy::Coordinate{
                .x = 1.0 + cdy::cos(cdy::Angle{45}),
                .y = 1.0 + cdy::sin(cdy::Angle{45})}
        },{
            cdy::Circle{.center = {1.0, 1.0}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{2.5, 2.5},
            cdy::Coordinate{
                .x = 1.0 + cdy::cos(cdy::Angle{45}),
                .y = 1.0 + cdy::sin(cdy::Angle{45})}
        }
    }));

    CAPTURE(circle, point);

    auto const maybe_result = cdy::projected(circle, point);

    REQUIRE(maybe_result.has_value() == expected_result.has_value());
    if (maybe_result.has_value())
    {
        REQUIRE_THAT(*maybe_result, test::CoordinateMatcher(*expected_result));
    }
}

TEST_CASE("geometry.circle_utils.distance()")
{
    auto const [circle, point, expected_result]
        = GENERATE(table<cdy::Circle, cdy::Coordinate, cdy::Length>({
        {
            cdy::Circle{.center = {}, .radius = {}},
            cdy::Coordinate{},
            cdy::Length{}
        },{
            cdy::Circle{.center = {}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{},
            cdy::Length{1.0}
        },{
            cdy::Circle{.center = {}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{0.5, 0.0},
            cdy::Length{0.5}
        },{
            cdy::Circle{.center = {1.0, 2.0}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{1.5, 2.0},
            cdy::Length{0.5}
        },{
            cdy::Circle{.center = {1.0, 1.0}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{1.5, 1.5},
            cdy::distance(
                cdy::Coordinate{1.5, 1.5},
                cdy::Coordinate{
                    .x = 1.0 + cdy::cos(cdy::Angle{45}),
                    .y = 1.0 + cdy::sin(cdy::Angle{45})})
        },{
            cdy::Circle{.center = {1.0, 1.0}, .radius = cdy::Length{1.0}},
            cdy::Coordinate{2.5, 2.5},
            cdy::distance(
                cdy::Coordinate{2.5, 2.5},
                cdy::Coordinate{
                    .x = 1.0 + cdy::cos(cdy::Angle{45}),
                    .y = 1.0 + cdy::sin(cdy::Angle{45})})
        }
    }));

    CAPTURE(circle, point);

    auto const result = cdy::distance(circle, point);

    REQUIRE(result == Catch::Approx(expected_result));
}
