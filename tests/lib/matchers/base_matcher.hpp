#ifndef CADYA_TEST_BASE_MATCHER_HPP
#define CADYA_TEST_BASE_MATCHER_HPP

#include <catch2/matchers/catch_matchers_templated.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <fmt/core.h>

#include <concepts>
#include <sstream>
#include <string>

namespace test {

namespace detail {

inline constexpr auto default_epsilon = 1e-15;

}

template <typename T>
concept Printable = requires (T const t, std::ostream& os)
{
    { os << t } -> std::same_as<std::ostream&>;
};

template <Printable T>
class BaseMatcher : public Catch::Matchers::MatcherBase<T>
{
public:
    BaseMatcher(
            T const& expected,
            double epsilon = detail::default_epsilon)
        : expected_{expected}
        , epsilon_{epsilon}
    {}

    auto expected() const -> T const&
    {
        return expected_;
    }

    auto epsilon() const -> double
    {
        return epsilon_;
    }

    auto describe() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << " == ";
        ss << expected_;
        return ss.str();
    }

private:
    T expected_;
    double epsilon_;
};

template <typename T>
auto operator==(T const& t, BaseMatcher<T> const& matcher) -> bool
{
    return matcher.match(t);
}

template <typename T>
auto operator==(BaseMatcher<T> const& matcher, T const& t) -> bool
{
    return matcher.match(t);
}

// TODO is it possible to unify BaseMatcher and BaseMatcherGeneric without
// loosing the ability to overload operator== ?
// Catch::Matchers::MatcherGenericBase does not provide a member function match()
template <Printable T>
class BaseMatcherGeneric : public Catch::Matchers::MatcherGenericBase
{
public:
    BaseMatcherGeneric(
            T const& expected,
            double epsilon = detail::default_epsilon)
        : expected_{expected}
        , epsilon_{epsilon}
    {}

    auto expected() const -> T const&
    {
        return expected_;
    }

    auto epsilon() const -> double
    {
        return epsilon_;
    }

    auto describe() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << " == ";
        ss << expected_;
        return ss.str();
    }

private:
    T expected_;
    double epsilon_;
};

} // namespace test

#endif
