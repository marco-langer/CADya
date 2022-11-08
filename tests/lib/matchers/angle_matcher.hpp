#ifndef CADYA_TEST_LIB_ANGLE_MATCHER_HPP
#define CADYA_TEST_LIB_ANGLE_MATCHER_HPP

#include "matchers/base_matcher.hpp"

#include "geometry/angle.hpp"

#include <catch2/catch_approx.hpp>
#include <fmt/core.h>

#include <ostream>

namespace cdy {

template <typename Unit>
inline auto operator<<(std::ostream& os, Angle<Unit> angle) -> std::ostream&
{
    return os << fmt::format("{}°", static_cast<double>(Angle<Degree>{angle}));
}

} // namespace cdy

namespace test {

template <typename Unit>
struct AngleMatcher : BaseMatcherGeneric<cdy::Angle<Unit>>
{
    using BaseMatcherGeneric<cdy::Angle<Unit>>::BaseMatcherGeneric;

    template <typename UnitOther>
    auto match(cdy::Angle<UnitOther> angle) const -> bool
    {
        auto const angle_converted = cdy::Angle<Unit>{angle};
        return angle_converted == Catch::Approx(this->expected()).margin(this->epsilon());
    }
};

} // namespace test

#endif
