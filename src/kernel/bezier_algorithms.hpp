#ifndef CADYA_BEZIER_ALGORITHMS
#define CADYA_BEZIER_ALGORITHMS

#include <kernel/bezier.hpp>
#include <kernel/box.hpp>

#include <boost/container/static_vector.hpp>
#include <boost/math/tools/roots.hpp>

#include <array>

namespace cy {

template <CubicBezier CubicBezier, std::floating_point F>
requires std::same_as
<
    F,
    typename get_value_type
    <
        typename get_point_type<CubicBezier>::type
    >::type
>
[[nodiscard]] auto evaluate_at(CubicBezier const & bezier, F t) noexcept
    -> Point auto
{
    auto const tt = t * t;
    auto const omt = F{1.0} - t;
    auto const omt_square = omt * omt;

    return omt * omt_square       * bezier[0]
         + 3 * t * omt_square     * bezier[1]
         + 3 * tt  * omt          * bezier[2]
         + tt * t                 * bezier[3];
}

template <CubicBezier CubicBezier, std::floating_point F>
requires std::same_as
<
    F,
    typename get_value_type
    <
        typename get_point_type<CubicBezier>::type
    >::type
>
[[nodiscard]] auto casteljau_at(CubicBezier const & /* bezier */, F /* t */) noexcept
    -> Point auto
{
    // TODO
    using point_t = typename get_point_type<CubicBezier>::type;
    return point_t{};
}

template <CubicBezier CubicBezier>
[[nodiscard]] auto bounding_box(CubicBezier const & bezier) noexcept
    -> Box auto
{
    using point_t = typename get_point_type<CubicBezier>::type;
    using F = typename get_value_type<point_t>::type;
    constexpr auto dim = get_dimension<point_t>::value;

    auto extrema = boost::container::static_vector<point_t, 2 * dim + 2>{};
    extrema.push_back(bezier[0]);
    extrema.push_back(bezier[3]);

    auto const a = bezier[1] - bezier[0];
    auto const b = 2 * bezier[2] - 4 * bezier[1] + 2 * bezier[0];
    auto const c = bezier[3] - 3 * bezier[2] + 3 * bezier[1] - bezier[0];

    auto roots = std::array<F, 2 * dim>{};
    std::tie(roots[0], roots[1]) = boost::math::tools::quadratic_roots(a[0], b[0], c[0]);
    std::tie(roots[2], roots[3]) = boost::math::tools::quadratic_roots(a[1], b[1], c[1]);
    if constexpr (dim == 3)
    {
        std::tie(roots[4], roots[5]) = boost::math::tools::quadratic_roots(a[2], b[2], c[2]);
    }

    for (auto root : roots)
    {
        if (root > F{0.0} && root < F{1.0})
        {
            extrema.push_back(evaluate_at(bezier, root));
        }
    }
    return basic_box<point_t>{std::cbegin(extrema), std::cend(extrema)};
}

template <CubicBezier CubicBezier>
[[nodiscard]] auto bounding_box_ctrl_net(CubicBezier const & bezier) noexcept
    -> Box auto
{
    using point_t = typename get_point_type<CubicBezier>::type;
    return basic_box<point_t>{std::cbegin(bezier.pts), std::cend(bezier.pts)};
}

}

#endif