#include "geometry/angle.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <numbers>

using namespace cdy::literals::angle_literals;

TEST_CASE("geometry.Angle.degree_to_radian()")
{
    auto const [value, expected_value] = GENERATE(table<double, double>({
        {0, 0},
        {90, std::numbers::pi / 2},
        {180, std::numbers::pi},
        {270, 3.0 / 2.0 * std::numbers::pi}
    }));

    CAPTURE(value, expected_value);

    auto const result = cdy::detail::degree_to_radian(value);

    REQUIRE(result == Catch::Approx(expected_value));
}

TEST_CASE("geometry.Angle.radian_to_degree()")
{
    auto const [value, expected_value] = GENERATE(table<double, double>({
        {0, 0},
        {std::numbers::pi / 2, 90},
        {std::numbers::pi, 180},
        {3.0 / 2.0 * std::numbers::pi, 270}
    }));

    CAPTURE(value, expected_value);

    auto const result = cdy::detail::radian_to_degree(value);

    REQUIRE(result == Catch::Approx(expected_value));
}

TEST_CASE("geometry.Angle.operator+()") {

    auto const first = 30_deg;
    auto const second = 12_deg;
    auto const expected_result = 42_deg;

    REQUIRE(first + second == Catch::Approx(expected_result));
}
