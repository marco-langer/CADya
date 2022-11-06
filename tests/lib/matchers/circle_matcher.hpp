#ifndef CADYA_TEST_LIB_CIRCLE_MATCHER_HPP
#define CADYA_TEST_LIB_CIRCLE_MATCHER_HPP

#include "base_matcher.hpp"
#include "coordinate_matcher.hpp"

#include "geometry/circle.hpp"

#include <catch2/catch_approx.hpp>

#include <ostream>

namespace cdy {

inline auto operator<<(std::ostream& os, Circle const& circle) -> std::ostream&
{
    return os << fmt::format("[center: [{}, {}], radius = {}]",
        circle.center.x, circle.center.y, circle.radius);
}

} // namespace cdy

namespace test {

struct CircleMatcher : BaseMatcher<cdy::Circle>
{
    using BaseMatcher::BaseMatcher;

    auto match(cdy::Circle const& circle) const -> bool override
    {
        return circle.center == CoordinateMatcher{expected().center, epsilon()}
            && circle.radius == Catch::Approx(expected().radius).margin(epsilon());
    }
};

} // namespace test

#endif
