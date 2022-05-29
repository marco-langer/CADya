#ifndef CADYA_POINT_MATCHER_HPP
#define CADYA_POINT_MATCHER_HPP

#include "kernel/point.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <fmt/core.h>

#include <concepts>
#include <fstream>

namespace test { namespace detail {

template <std::floating_point F, std::size_t Dim>
auto to_string(cy::basic_point<F, Dim> const & pt) -> std::string
{
    if constexpr (Dim == 2) {
        return fmt::format("[x = {}, y = {}]", pt[0], pt[1]);
    } else {
        return fmt::format("[x = {}, y = {}, z = {}]", pt[0], pt[1], pt[2]);
    }
}

template <std::floating_point F, std::size_t Dim>
auto are_equal(
    cy::basic_point<F, Dim> const & lhs,
    cy::basic_point<F, Dim> const & rhs,
    F epsilon) -> bool
{
    if constexpr (Dim == 2) {
        return Catch::Approx(lhs.xs[0]).epsilon(epsilon) == rhs.xs[0]
            && Catch::Approx(lhs.xs[1]).epsilon(epsilon) == rhs.xs[1];
    } else {
        return Catch::Approx(lhs.xs[0]).epsilon(epsilon) == rhs.xs[0]
            && Catch::Approx(lhs.xs[1]).epsilon(epsilon) == rhs.xs[1]
            && Catch::Approx(lhs.xs[2]).epsilon(epsilon) == rhs.xs[2];
    }
}

} // namespace detail

template <std::floating_point F, std::size_t Dim>
struct point_matcher : Catch::Matchers::MatcherGenericBase
{
    point_matcher(cy::basic_point<F, Dim> const & point, F epsilon = F{1e-15})
        : point_(point), epsilon_(epsilon) {}

    auto match(cy::basic_point<F, Dim> const & other_point) const -> bool
    {
        return detail::are_equal(point_, other_point, epsilon_);
    }

    auto describe() const -> std::string
    {
        return detail::to_string(point_);
    }

    cy::basic_point<F, Dim> point_;
    F epsilon_;
};

} // namespace test

namespace cy {

auto operator<<(std::ostream & os, cy::Point auto const & pt) -> std::ostream &
{
    return os << test::detail::to_string(pt);
}

} // namespace cy

#endif