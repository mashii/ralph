#ifndef RALPH_COMMON_LIKELY_H
#define RALPH_COMMON_LIKELY_H

#undef likely
#undef unlikely

#if defined(__GNUC__) && __GNUC__ >= 4
#define likely(x)   (__builtin_expect((x), 1))
#define unlikely(x) (__builtin_expect((x), 0))
#else
#define likely(x)   (x)
#define unlikely(x) (x)
#endif

#endif // RALPH_COMMON_LIKELY_H
