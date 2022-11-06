#ifndef CADYA_TEST_LIB_COORDINATE_MATCHER_HPP
#define CADYA_TEST_LIB_COORDINATE_MATCHER_HPP

#include "base_matcher.hpp"

#include "geometry/coordinate.hpp"

#include <catch2/catch_approx.hpp>

#include <ostream>

namespace cdy {

inline auto operator<<(std::ostream& os, Coordinate const& point) -> std::ostream&
{
    return os << fmt::format("[{}, {}]", point.x, point.y);
}

} // namespace cdy

namespace test {

struct CoordinateMatcher : BaseMatcher<cdy::Coordinate>
{
    using BaseMatcher::BaseMatcher;

    auto match(cdy::Coordinate const& point) const -> bool override
    {
        return point.x == Catch::Approx(expected().x).margin(epsilon())
            && point.y == Catch::Approx(expected().y).margin(epsilon());
    }
};

} // namespace test

#endif
