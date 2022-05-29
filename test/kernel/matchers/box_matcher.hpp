#ifndef CADYA_BOX_MATCHER_HPP
#define CADYA_BOX_MATCHER_HPP

#include "matchers/point_matcher.hpp"

#include <kernel/box.hpp>

#include <catch2/matchers/catch_matchers_templated.hpp>
#include <fmt/core.h>

#include <concepts>
#include <fstream>

namespace test { namespace detail {

auto to_string(cy::Box auto const & box) -> std::string
{
    return fmt::format("min = {}, max = {}", to_string(box.min), to_string(box.max));
}

} // namespace detail

template <cy::Box Box, std::floating_point F>
struct box_matcher : Catch::Matchers::MatcherGenericBase
{
    box_matcher(Box const & box, F epsilon = F{1e-15})
        : box_(box), epsilon_(epsilon) {}

    auto match(Box const & other_box) const -> bool
    {
        return detail::are_equal(box_.min, other_box.min, epsilon_)
            && detail::are_equal(box_.max, other_box.max, epsilon_);
    }

    auto describe() const -> std::string
    {
        return detail::to_string(box_);
    }

    Box box_;
    F epsilon_;
};

} // namespace

namespace cy {

auto operator<<(std::ostream & os, cy::Box auto const & box) -> std::ostream &
{
    return os << test::detail::to_string(box);
}

} // namespace cy


#endif