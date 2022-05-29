#include "matchers/box_matcher.hpp"

#include <kernel/bezier_algorithms.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <string_view>
#include <vector>
#include <iostream>
using namespace std::literals::string_view_literals;

namespace {

constexpr auto k = 0.551785;

// TODO write tests for more template parameters
using point = cy::basic_point<double, 3>;
using cubic_bezier = cy::basic_cubic_bezier<point>;
using box = cy::basic_box<point>;

}

TEST_CASE("bezier.evaluate_at() / casteljau_at()")
{
    auto const [title, bezier, data] = GENERATE(
        table
        <
            std::string_view,
            cubic_bezier,
            std::vector<std::pair<double, point>>
        >
        ({
            {
                "linear bezier"sv,
                cubic_bezier{
                    point{0.0, 0.0},
                    point{0.2, 0.2},
                    point{0.8, 0.8},
                    point{1.0, 1.0}
                },
                std::vector{
                    std::pair{0.0, point{0.0, 0.0}},
                    std::pair{0.5, point{0.5, 0.5}},
                    std::pair{1.0, point{1.0, 1.0}},
                }
            },
            {
                "circular bezier"sv,
                cubic_bezier{
                    point{0.0, 0.0},
                    point{0.0, k},
                    point{1.0 - k, 1.0},
                    point{1.0, 1.0}
                },
                std::vector{
                    std::pair{0.0, point{0.0, 0.0}},
                    std::pair{0.5, point{0.29308, 0.70691}},
                    std::pair{1.0, point{1.0, 1.0}},
                }
            },
        })
    );

    constexpr auto epsilon = 1.0e-3;
    for (int i{}; auto const [t, expected_point] : data)
    {
        CAPTURE(title, i);
        auto const pt = cy::evaluate_at(bezier, t);
        auto const pt_casteljau = cy::casteljau_at(bezier, t);
        REQUIRE_THAT(pt, test::point_matcher(expected_point, epsilon));
        REQUIRE_THAT(pt_casteljau, test::point_matcher(expected_point, epsilon));
        ++i;
    }
}

TEST_CASE("bezier.bounding_box()")
{
    auto const [title, bezier, expected_bb] = GENERATE(
        table<std::string_view, cubic_bezier, box>
        ({
            {
                "linear bezier"sv,
                cubic_bezier{
                    point{0.0, 0.0},
                    point{0.2, 0.2},
                    point{0.8, 0.8},
                    point{1.0, 1.0}
                },
                box(point{}, point{1.0, 1.0, 0.0})
            },
            {
                "circular bezier"sv,
                cubic_bezier{
                    point{0.0, 0.0},
                    point{0.0, k},
                    point{1.0 - k, 1.0},
                    point{1.0, 1.0}
                },
                box(point{}, point{1.0, 1.0, 0.0})
            },
            {
                "streched circular bezier"sv,
                cubic_bezier{
                    point{0.0, 0.0},
                    point{-1.0, 5.0},
                    point{1.0 - k, 1.0},
                    point{1.0, 1.0}
                },
                box(point{}, point{1.0, 1.0, 0.0})
            }
        })
    );

    CAPTURE(title);

    constexpr auto epsilon = 1.0e-5;
    auto const bb_matcher = test::box_matcher(expected_bb, epsilon);
    auto const bb = cy::bounding_box(bezier);
    std::cout << test::detail::to_string(bb.min) << '\n';
    std::cout << test::detail::to_string(bb.max) << '\n';
    REQUIRE_THAT(bb, bb_matcher);
}