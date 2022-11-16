#ifndef CADYA_TEST_LIB_VECTOR_MATCHER_HPP
#define CADYA_TEST_LIB_VECTOR_MATCHER_HPP

#include "base_matcher.hpp"

#include "geometry/vector.hpp"

#include <catch2/catch_approx.hpp>

#include <ostream>

namespace cdy {

inline auto operator<<(std::ostream& os, Vector const& vector) -> std::ostream&
{
    return os << fmt::format("[{}, {}]", vector.x, vector.y);
}

} // namespace cdy

namespace test {

struct VectorMatcher : BaseMatcher<cdy::Vector>
{
    using BaseMatcher::BaseMatcher;

    auto match(cdy::Vector const& vector) const -> bool override
    {
        return vector.x == Catch::Approx(expected().x).margin(epsilon())
            && vector.y == Catch::Approx(expected().y).margin(epsilon());
    }
};

} // namespace test

#endif
