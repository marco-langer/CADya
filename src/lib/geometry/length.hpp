#ifndef CADYA_GEOMETRY_LENGTH_HPP
#define CADYA_GEOMETRY_LENGTH_HPP

#include <cassert>

namespace cdy {

class Length
{
public:
    Length() = default;
    explicit Length(double value) : value_{value} { assert(value_ >= 0.0); }

    operator double() const { return value_; }

private:
    double value_{};
};

} // namespace cdy

#endif
