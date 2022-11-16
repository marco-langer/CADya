#ifndef CADYA_TEST_LINE_MATCHER_HPP
#define CADYA_TEST_LINE_MATCHER_HPP

#include "base_matcher.hpp"
#include "coordinate_matcher.hpp"
#include "vector_matcher.hpp"

#include "geometry/line.hpp"
#include "geometry/line_utils.hpp"
#include "utility.hpp"

#include <fmt/core.h>

#include <ostream>

namespace cdy {

inline auto operator<<(std::ostream& os, Line const& line) -> std::ostream&
{
    return os << fmt::format("[point: [{}, {}], normal: [{}, {}]]",
        line.point().x, line.point().y,
        line.normal().x, line.normal().y);
}

inline auto operator<<(std::ostream& os, LineOrientation orientation) -> std::ostream&
{
    switch (orientation) {
        case LineOrientation::Parallel: return os << "parallel";
        case LineOrientation::Intersecting: return os << "intersecting";
        case LineOrientation::Coincident: return os << "coincident";
        default: cdy::unreachable();
    }
}

} // namespace cdy

#endif
