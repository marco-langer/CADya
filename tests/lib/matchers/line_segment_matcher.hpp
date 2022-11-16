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
    return os << fmt::format("[start: [{}, {}], end: [{}, {}]]",
        line_segment.start().x, line_segment.start().y,
        line_segment.end().x, line_segment.end().y);
}

} // namespace cdy

namespace test {

struct LineSegmentMatcher : BaseMatcher<cdy::LineSegment>
{
    using BaseMatcher::BaseMatcher;

    auto match(cdy::LineSegment const& line_segment) const -> bool override
    {
        return line_segment.start() == CoordinateMatcher(expected().start(), epsilon())
            && line_segment.end() == CoordinateMatcher(expected().end(), epsilon());
    }
};

} // namespace test

#endif
