#ifndef CADYA_TEST_LINE_SEGMENT_MATCHER_HPP
#define CADYA_TEST_LINE_SEGMENT_MATCHER_HPP

#include "base_matcher.hpp"
#include "coordinate_matcher.hpp"

#include "geometry/line_segment.hpp"

#include <fmt/core.h>

#include <ostream>

namespace cdy {

inline auto operator<<(std::ostream& os, LineSegment const& line_segment) -> std::ostream&
{
    return os << fmt::format("[[{}, {}], [{}, {}]]",
        line_segment.first.x, line_segment.first.y,
        line_segment.second.x, line_segment.second.y);
}

} // namespace cdy

namespace test {

struct LineSegmentMatcher : BaseMatcher<cdy::LineSegment>
{
    using BaseMatcher::BaseMatcher;

    auto match(cdy::LineSegment const& line_segment) const -> bool override
    {
        return line_segment.first == CoordinateMatcher(expected().first, epsilon())
            && line_segment.second == CoordinateMatcher(expected().second, epsilon());
    }
};

} // namespace test

#endif
