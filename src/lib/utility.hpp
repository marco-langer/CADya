#ifndef CADYA_UTILITY_HPP

namespace cdy {

// TODO C++23 replace with std::unreachable()
[[noreturn]] inline void unreachable()
{
#ifdef __GNUC__ // GCC, Clang, ICC
    __builtin_unreachable();
#else // MSVC
    __assume(false);
#endif
}

} // namespace cdy

#endif

