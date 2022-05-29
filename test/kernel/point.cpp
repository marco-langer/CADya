#include "matchers/point_matcher.hpp"

#include <kernel/point.hpp>

#include <catch2/catch_test_macros.hpp>

namespace {

using point = cy::basic_point<double, 3>;

}

TEST_CASE("point.operator+()")
{
    auto const lhs = point{0.1, 0.2, 0.3};
    auto const rhs = point{0.01, 0.02, 0.03};
    auto const expected_result = point{0.11, 0.22, 0.33};

    auto const result = lhs + rhs;
    REQUIRE_THAT(result, test::point_matcher(expected_result));
}

TEST_CASE("point.operator-()")
{
    auto const lhs = point{0.1, 0.2, 0.3};
    auto const rhs = point{0.01, 0.02, 0.03};
    auto const expected_result = point{0.09, 0.18, 0.27};

    auto const result = lhs - rhs;
    REQUIRE_THAT(result, test::point_matcher(expected_result));
}

TEST_CASE("point.operator*()")
{
    auto const pt = point{0.1, 0.2, 0.3};
    auto const scalar = 2.0;
    auto const expected_result = point{0.2, 0.4, 0.6};

    auto const result_lhs = pt * scalar;
    auto const result_rhs = scalar * pt;
    REQUIRE_THAT(result_lhs, test::point_matcher(expected_result));
    REQUIRE_THAT(result_rhs, test::point_matcher(expected_result));
}