#ifndef CADYA_TYPE_TRAITS_HPP
#define CADYA_TYPE_TRAITS_HPP

#include <type_traits>

namespace cdy::traits {

template <typename T, typename... Args>
inline constexpr bool is_any_of = (... || std::is_same_v<T, Args>);

template <typename T>
inline constexpr bool dependent_false = false;

}

#endif // namespace cdy::traits
