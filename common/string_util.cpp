#include "string_util.h"

#include <stdio.h>
#include <stdarg.h>

#include <memory>
#include <random>

namespace ralph
{

const std::string Str::kDefaultTrimCharecters = " \a\b\f\t\v\r\n";

std::string Str::ToUpper(const std::string & str)
{
    std::string res(str);
    for (size_t i=0; i<str.length(); ++i) {
        if (res[i] >= 'a' && res[i] <= 'z') {
            res[i] = res[i] - 'a' + 'A';
        }
    }
    return std::move(res);
}

std::string Str::ToLower(const std::string & str)
{
    std::string res(str);
    for (size_t i=0; i<str.length(); ++i) {
        if (res[i] >= 'A' && res[i] <= 'Z') {
            res[i] = res[i] - 'A' + 'a';
        }
    }
    return std::move(res);
}

bool Str::StartsWith(const std::string & str, const std::string & prefix)
{
    if (str.length() < prefix.length()) {
        return false;
    }

    return str.compare(0, prefix.length(), prefix) == 0;
}

bool Str::EndsWith  (const std::string & str, const std::string & suffix)
{
    if (str.length() < suffix.length()) {
        return false;
    }

    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

std::string Str::Replace(const std::string & str, const std::string & from,
                         const std::string & to)
{
    size_t find = str.find(from);
    if (find == std::string::npos) {
        return str;
    }

    std::string result = str;
    result.replace(find, from.length(), to);
    return std::move(result);
}

std::string Str::ReplaceAll(const std::string & str, const std::string & from,
                            const std::string & to)
{
    size_t pos = 0;
    size_t find = 0;

    size_t from_len = from.length();

    std::string result;
    while(true) {
        find = str.find(from, pos);
        result.append(str, pos, find - pos);

        if (find == std::string::npos) {
            break;
        }

        result.append(to);
        pos = find + from_len;
    }

    return std::move(result);
}

std::string Str::Trim (const std::string & str, const std::string & trim_str)
{
    size_t b = str.find_first_not_of(trim_str);
    if (b == std::string::npos) {
        return std::string();
    }

    size_t e = str.find_last_not_of(trim_str);
    return str.substr(b, e - b + 1);
}

std::string Str::Ltrim(const std::string & str, const std::string & trim_str)
{
    size_t b = str.find_first_not_of(trim_str);
    if (b == std::string::npos) {
        return std::string();
    }

    return str.substr(b);
}

std::string Str::Rtrim(const std::string & str, const std::string & trim_str)
{
    size_t e = str.find_last_not_of(trim_str);
    if (e == std::string::npos) {
        return std::string();
    }

    return str.substr(0, e + 1);
}

std::string Str::Format(const char * fmt, ...)
{
    static const size_t kBufLen = 1024;
    va_list ap;
    va_start(ap, fmt);
    size_t len = static_cast<size_t>(vsnprintf(nullptr, 0, fmt, ap) + 1);
    va_end(ap);

    va_start(ap, fmt);

    if (len <= kBufLen) {
        char buf[kBufLen];
        vsnprintf(buf, kBufLen, fmt, ap);
        va_end(ap);
        return std::string(buf);
    }

    std::unique_ptr<char[]> buf(new char[len]);
    vsnprintf(buf.get(), len, fmt, ap);
    va_end(ap);
    return std::string(buf.get());
}

std::vector<std::string> Str::Split(const std::string & str,
                                    const std::string & deli,
                                    bool reserve_space)
{
    std::vector<std::string> res;
    size_t pos = 0;
    size_t str_len = str.length();
    size_t deli_len = deli.length();
    while (pos < str_len) {
        size_t tmp = str.find(deli, pos);
        if (tmp == std::string::npos) {
            res.push_back(str.substr(pos));
            break;
        }

        if (tmp != pos || reserve_space) {
            res.push_back(str.substr(pos, tmp - pos));
        }

        pos = tmp + deli_len;
    }

    return std::move(res);
}

std::vector<std::string> Str::SplitAny(const std::string & str,
                                       const std::string & deli,
                                       bool reserve_space)
{
    std::vector<std::string> res;
    size_t pos = 0;
    size_t str_len = str.length();
    while (pos < str_len) {
        size_t tmp = str.find_first_of(deli, pos);
        if (tmp == std::string::npos) {
            res.push_back(str.substr(pos));
            break;
        }

        if (tmp != pos || reserve_space) {
            res.push_back(str.substr(pos, tmp - pos));
        }

        pos = tmp + 1;
    }

    return std::move(res);
}

std::string Str::Join(const std::vector<std::string> & v,
                      const std::string & deli)
{
    std::string res;
    size_t size = v.size();
    if (size > 0) {
        res = v[0];
    }

    for (size_t i=1; i<size; ++i) {
        res.append(deli);
        res.append(v[i]);
    }

    return std::move(res);
}

std::string Str::Random(const std::string & charset, int len)
{
    char buf[256];
    size_t charset_length = charset.length();
    size_t idx = 0;
    size_t buf_idx = 0;
    while(idx < charset_length) {
        if (idx + 1 < charset_length && charset[idx+1] == '-') {
            char b = charset[idx];
            if (idx + 2 < charset_length) {
                char e = charset[idx+2];
                for (char c=b; c<=e; ++c) {
                    buf[buf_idx++] = c;
                }
                idx += 3;
            } else {
                buf[buf_idx++] = charset[idx];
                buf[buf_idx++] = charset[idx+1];
                idx += 2;
            }
        } else {
            buf[buf_idx++] = charset[idx];
            idx += 1;
        }
    }

    std::string result(len, '\0');
    std::random_device rd;
    for (int i=0; i<len; ++i) {
        result[i] = buf[rd() % buf_idx];
    }

    return std::move(result);
}

} // namespace ralph
