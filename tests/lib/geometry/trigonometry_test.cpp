#include "matchers/angle_matcher.hpp"
#include "matchers/vector_matcher.hpp"

#include "geometry/trigonometry.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <cmath>

using namespace cdy::literals::angle_literals;

TEST_CASE("geometry.trigonometry.sin()")
{
    auto const [angle, expected_result]
        = GENERATE(table<cdy::Angle<cdy::Degree>, double>({
        {0_deg, 0.0},
        {30_deg, 0.5},
        {75_deg, 0.25 * (std::sqrt(6) + std::sqrt(2))},
    }));

    auto const result = cdy::sin(angle);
    REQUIRE(result == Catch::Approx(expected_result));
}

TEST_CASE("geometry.trigonometry.cos()")
{
    auto const [angle, expected_result]
        = GENERATE(table<cdy::Angle<cdy::Degree>, double>({
        {0_deg, 1.0},
        {30_deg, 0.5 * std::sqrt(3)},
        {75_deg, 0.25 * (std::sqrt(6) - std::sqrt(2))},
    }));

    auto const result = cdy::cos(angle);
    REQUIRE(result == Catch::Approx(expected_result));
}

TEST_CASE("geometry.trigonometry.angle()")
{
    auto const [first, second, expected_angle]
        = GENERATE(table<cdy::Vector, cdy::Vector, cdy::Angle<cdy::Degree>>({
        {{0.0, 1.0}, {0.0, 1.0}, 0_deg},
        {{0.0, 1.0}, {1.0, 1.0}, 45_deg},
        {{0.0, 1.0}, {1.0, 0.0}, 90_deg},
        {{0.0, 1.0}, {1.0, -1.0}, 135_deg},
        {{0.0, 1.0}, {0.0, -1.0}, 180_deg},
        {{0.0, 1.0}, {-1.0, -1.0}, 135_deg},
        {{0.0, 1.0}, {0.0, 1.000000000002}, 0_deg},
        {
            {0.38268343236508978, -0.92387953251128663},
            {0.38268343236508978, -0.92387953251128663},
            0_deg
        },{
            {0.38268343236508978, -0.92387953251128663},
            {0.38268343236508984, -0.92387953251128685},
            0_deg
        },{
            {-0.38268343236508978, 0.92387953251128663},
            {0.38268343236508978, -0.92387953251128663},
            180_deg
        },{
            {-0.38268343236508978, 0.92387953251128663},
            {0.38268343236508984, -0.92387953251128685},
            180_deg
        }
    }));

    auto const result = cdy::angle(first, second);
    REQUIRE_THAT(result, test::AngleMatcher<cdy::Degree>(expected_angle));
}

TEST_CASE("geometry.trigonometry.direction()") {

    auto const [angle, expected_direction] = GENERATE(
        table<cdy::Angle<cdy::Degree>, cdy::Vector>({
        {0_deg, {1.0, 0.0}},
        {45_deg, {1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0)}},
        {90_deg, {0.0, 1.0}},
        {135_deg, {-1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0)}},
        {180_deg, {-1.0, 0.0}},
        {225_deg, {-1.0 / std::sqrt(2.0), -1.0 / std::sqrt(2.0)}},
        {270_deg, {0.0, -1.0}},
        {315_deg, {1.0 / std::sqrt(2.0), -1.0 / std::sqrt(2.0)}},
    }));

    CAPTURE(angle, expected_direction);

    REQUIRE_THAT(cdy::direction(angle), test::VectorMatcher(expected_direction));
}
