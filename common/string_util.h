#ifndef RALPH_COMMON_STRING_UTIL_H
#define RALPH_COMMON_STRING_UTIL_H

#include <string>
#include <vector>

namespace ralph {

class Str {
public:
    static const std::string kDefaultTrimCharecters;

public:
    static std::string ToUpper(const std::string & str);
    static std::string ToLower(const std::string & str);

    static bool StartsWith(const std::string & str, const std::string & prefix);
    static bool EndsWith  (const std::string & str, const std::string & suffix);

    static std::string Replace(const std::string & str, const std::string & from,
                               const std::string & to);

    static std::string ReplaceAll(const std::string & str, const std::string & from,
                               const std::string & to);

    static std::string Trim (const std::string & str,
                             const std::string & trim_str = kDefaultTrimCharecters);

    static std::string Ltrim(const std::string & str,
                             const std::string & trim_str = kDefaultTrimCharecters);

    static std::string Rtrim(const std::string & str,
                   const std::string & trim_str = kDefaultTrimCharecters);

    static std::string Format(const char * fmt, ...)
                   __attribute__ ((format (printf, 1, 2)));

    static std::vector<std::string> Split(const std::string & str,
                                          const std::string & deli,
                                          bool reserve_space = false);

    static std::vector<std::string> SplitAny(const std::string & str,
                                             const std::string & deli,
                                             bool reserve_space = false);

    static std::string Join(const std::vector<std::string> & v,
                            const std::string & deli);

    static std::string Random(const std::string &charset, int len);
};

} // namespace ralph

#endif // RALPH_COMMON_STRING_UTIL_H
