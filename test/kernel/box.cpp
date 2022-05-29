#include "matchers/point_matcher.hpp"

#include <kernel/box.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <vector>

namespace {

using point = cy::basic_point<double, 3>;
using box = cy::basic_box<point>;

}

TEST_CASE("box.constructor() two points")
{
    auto const [first, second, expected_min, expected_max] = GENERATE(
        table<point, point, point, point>({
        {
            point{0.0, 0.0, 0.0},
            point{0.0, 0.0, 0.0},
            point{0.0, 0.0, 0.0},
            point{0.0, 0.0, 0.0}
        },
        {
            point{1.0, 2.0, 3.0},
            point{2.0, 3.0, 4.0},
            point{1.0, 2.0, 3.0},
            point{2.0, 3.0, 4.0}
        },
        {
            point{1.0, -2.0, 3.0},
            point{-2.0, 3.0, -4.0},
            point{-2.0, -2.0, -4.0},
            point{1.0, 3.0, 3.0}
        }
    }));

    auto const bb = box{first, second};
    REQUIRE_THAT(bb.min, test::point_matcher(expected_min));
    REQUIRE_THAT(bb.max, test::point_matcher(expected_max));
}

TEST_CASE("box.constructor() iterators")
{
    auto const [points, expected_min, expected_max] = GENERATE(
        table<std::vector<point>, point, point>({
        {
            std::vector<point>{},
            point{0.0, 0.0, 0.0},
            point{0.0, 0.0, 0.0},
        },
        {
            std::vector{
              point{0.0, 0.0, 0.0},
              point{0.0, 0.0, 0.0},
            },
            point{0.0, 0.0, 0.0},
            point{0.0, 0.0, 0.0},
        },
        {
            std::vector{
                point{1.0, 2.0, 3.0},
                point{2.0, 3.0, 4.0},
            },
            point{1.0, 2.0, 3.0},
            point{2.0, 3.0, 4.0},
        },
        {
            std::vector{
                point{1.0, -2.0, 3.0},
                point{-2.0, 3.0, -4.0},
            },
            point{-2.0, -2.0, -4.0},
            point{1.0, 3.0, 3.0},
        },
        {
            std::vector{
                point{1.0, -2.0, 3.0},
                point{10.0, -5.0, 3.0},
                point{-2.0, 3.0, -4.0},
            },
            point{-2.0, -5.0, -4.0},
            point{10.0, 3.0, 3.0},
        }
    }));

    auto const bb = box{std::begin(points), std::end(points)};
    REQUIRE_THAT(bb.min, test::point_matcher(expected_min));
    REQUIRE_THAT(bb.max, test::point_matcher(expected_max));
}