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
    const auto [angle, expected_result]
        = GENERATE(table<cdy::Angle<cdy::Degree>, double>({
        {0_deg, 1.0},
        {30_deg, 0.5 * std::sqrt(3)},
        {75_deg, 0.25 * (std::sqrt(6) - std::sqrt(2))},
    }));

    auto const result = cdy::cos(angle);
    REQUIRE(result == Catch::Approx(expected_result));
}
