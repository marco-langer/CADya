#ifndef CADYA_BEZIER_MATCHER_HPP
#define CADYA_BEZIER_MATCHER_HPP

#include "matchers/point_matcher.hpp"

#include <kernel/bezier.hpp>

#include <catch2/matchers/catch_matchers_templated.hpp>
#include <fmt/core.h>

#include <concepts>
#include <fstream>

namespace test { namespace detail {

auto to_string(cy::CubicBezier auto const & bezier) -> std::string
{
    return fmt::format("{}, {}, {}, {}",
        to_string(bezier.pts[0]), to_string(bezier.pts[1]),
        to_string(bezier.pts[2]), to_string(bezier.pts[3])
    );
}

} // namespace detail

template <cy::CubicBezier CubicBezier, std::floating_point F>
struct bezier_matcher : Catch::Matchers::MatcherGenericBase
{
    bezier_matcher(CubicBezier const & bezier, F epsilon = F{1e-15})
        : bezier_(bezier), epsilon_(epsilon) {}

    auto match(CubicBezier const & other_bezier) const -> bool
    {
        return detail::are_equal(bezier_.pts[0], other_bezier.pts[0], epsilon_)
            && detail::are_equal(bezier_.pts[1], other_bezier.pts[1], epsilon_)
            && detail::are_equal(bezier_.pts[2], other_bezier.pts[2], epsilon_)
            && detail::are_equal(bezier_.pts[3], other_bezier.pts[3], epsilon_);
    }

    auto describe() const -> std::string
    {
        return detail::to_string(bezier_);
    }

    CubicBezier bezier_;
    F epsilon_;
};

} // namespace

namespace cy {

template <cy::CubicBezier CubicBezier>
auto operator<<(std::ostream & os, CubicBezier auto const & bezier) -> std::ostream &
{
    return os << test::detail::to_string(bezier);
}

} // namespace cy


#endif