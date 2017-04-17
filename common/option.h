#ifndef OPTION_H
#define OPTION_H

#include <cxxabi.h>

#include <stdio.h>
#include <stdarg.h>


#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

namespace option
{

static const std::string kHelpOptionLongName = "help";
static const char kHelpOptionShortName = '?';
static const std::string kHelpMessage = "show this help message";

class option_exception: public std::exception {
public:
    option_exception(const std::string & what) : _what(what) {}
    ~option_exception() throw() {}

    const char* what() const throw()
    {
        return _what.c_str();
    }

private:
    std::string _what;
};

template <class T>
std::string type_name()
{
    char * realname = abi::__cxa_demangle(typeid(T).name(), 0, 0, 0);
    std::string type(realname);
    free(realname);
    return type;
}

std::string str_fmt(const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int len = vsnprintf(nullptr, 0, fmt, ap) + 1;

    std::unique_ptr<char[]> buf(new char[len]);
    va_start(ap, fmt);
    vsnprintf(buf.get(), len, fmt, ap);
    va_end(ap);
    return std::string(buf.get());
}

template <class T>
T lexical_cast(const std::string & value)
{
    std::stringstream ss;
    T tmp;
    if (! (ss << value && ss >> tmp && ss.eof())) {
        throw option_exception(str_fmt("bad cast, can not cast %s to type %s", value.c_str(), type_name<T>().c_str()));
    }

    return tmp;
}

template <class T>
struct Restrict
{
    virtual void Check(const std::string & name, const T &) const {}
};

template <class T>
class RangeRestrict : public Restrict<T> {
public:
    RangeRestrict(const T & min, const T & max) : _min(min), _max(max) {}

    virtual void Check(const std::string & name, const T & value) const override
    {
        if (value < _min || value > _max) {
            throw option_exception(str_fmt("%s must be in range %d ~ %d", name.c_str(), _min, _max));
        }
    }

private:
    T _min;
    T _max;
};

template <class T>
class OneOfRestrict : public Restrict<T> {
public:
    OneOfRestrict(const std::set<T> & possible_values) : _possible_values(possible_values) {}

    virtual void Check(const std::string & name, const T & value) const override
    {
        if (_possible_values.find(value) == _possible_values.end()) {
            std::stringstream ss;
            ss << name << " must be in set [";
            auto it = _possible_values.begin();
            ss << *it++;
            for (;it != _possible_values.end(); ++it) {
                ss << ", " << *it;
            }
            ss << "]";

            throw option_exception(ss.str());
        }
    }

private:
    std::set<T> _possible_values;
};

struct OptionBase {
    OptionBase(std::string long_name, char short_name, std::string desc,
               bool is_necessary, bool is_bool_option)
        : long_name(long_name)
        , short_name(short_name)
        , desc(desc)
        , is_set(false)
        , is_necessary(is_necessary)
        , is_bool_option(is_bool_option) {}
    virtual ~OptionBase() {}

    virtual void check() = 0;
    virtual void set(const std::string & v) = 0;
    virtual void set(bool v) = 0;

    std::string long_name;
    char short_name;
    std::string desc;
    bool is_bool_option;
    bool is_necessary;
    bool is_set;
};

template <class T>
struct Option : public OptionBase {
public:
    Option(std::string long_name, char short_name, std::string desc, bool is_necessary,
           bool is_bool_option, const T & default_value)
        : OptionBase(long_name, short_name, desc, is_necessary, is_bool_option)
        , default_value(default_value) {}
    virtual ~Option() {}

    T get() const
    {
        return is_set ? value : default_value;
    }

    void set(const std::string & v)
    {
        value = lexical_cast<T>(v);
        is_set = true;
    }

    void set(bool v)
    {
        if (!is_bool_option) {
            throw(option_exception("unepected error happed! 0_0..."));
        }

        value = v;
        is_set = true;
    }

    virtual void check()
    {
        if (this->is_necessary && !is_set) {
            throw option_exception(str_fmt("option '%s' must be set", long_name.c_str()));
        }
    }

    T default_value;
    T value;
};

template <class T, class R>
struct OptionWithRestirct : public Option<T> {
    OptionWithRestirct(std::string long_name, char short_name, std::string desc, bool is_necessary,
                       bool is_bool_option, const T & default_value, const R & restriction)
        : Option<T>(long_name, short_name, desc, is_necessary, is_bool_option, default_value)
        , restriction(restriction) {}
    virtual ~OptionWithRestirct() {}

    virtual void check()
    {
        if (this->is_necessary && !this->is_set) {
            throw option_exception(str_fmt("option '%s' must be set", this->long_name.c_str()));
        }

        restriction.Check(this->long_name, this->is_set ? this->value : this->default_value);
    }

    R restriction;
};

class Options {
public:
    Options() {}

    // bool 类型选项
    void Add(const std::string & long_name, char short_name, const std::string & desc)
    {
        CheckOption(long_name, short_name);
        _name_map.insert(std::make_pair(short_name, long_name));
        _options.insert(std::make_pair(long_name, std::unique_ptr<Option<bool>>(new Option<bool>(long_name, short_name, desc, false, true, false))));
    }

    // 带值类型选项
    template<class T>
    void Add(const std::string & long_name,
             char short_name,
             const std::string & desc,
             bool is_necessary = false,
             T default_value = T())
    {
        CheckOption(long_name, short_name);
        _name_map.insert(std::make_pair(short_name, long_name));
        _options.insert(std::make_pair(long_name, std::unique_ptr<Option<T>>(new Option<T>(long_name, short_name, desc, is_necessary, false, default_value))));
    }

    // 带值类型选项，并且有限制
    template<class T, class R>
    void Add(const std::string & long_name,
             char short_name,
             const std::string & desc,
             bool is_necessary = false,
             T default_value = T(),
             const R & restriction = Restrict<T>())
    {
        CheckOption(long_name, short_name);
        _name_map.insert(std::make_pair(short_name, long_name));
        _options.insert(std::make_pair(long_name, std::unique_ptr<OptionWithRestirct<T, R>>(new OptionWithRestirct<T, R>(long_name, short_name, desc, is_necessary, false, default_value, restriction))));
    }

    bool Parse(int argc, const char * const argv[])
    {
        if (argc > 0) {
            _name = argv[0];
        }

        try {
            int i = 1;
            while (i<argc) {
                std::string arg(argv[i]);

                // 非选项参数
                if (arg[0] != '-') {
                    _rest.push_back(arg);

                } else {
                    if (arg.length() < 2) {
                        fprintf(stderr, "invalidate parameter '%s'\n", arg.c_str());
                        return false;
                    }

                    std::string lname;
                    std::string value;

                    // 处理长选项
                    if (arg[1] == '-') {
                        size_t pos = arg.find('=');
                        if (pos == std::string::npos) {
                            lname = arg.substr(2);
                        } else {
                            lname = arg.substr(2, pos-2);
                            value= arg.substr(pos+1);
                        }

                        if (lname == kHelpOptionLongName) {
                            Help();
                            exit(0);
                        }

                        auto it = _options.find(lname);
                        if (it == _options.end()) {
                            fprintf(stderr, "unkown option '--%s'\n", lname.c_str());
                            return false;
                        }

                        if (it->second.get()->is_bool_option) {
                            if (value != "") {
                                fprintf(stderr, "bool option '--%s' can not be with value\n", lname.c_str());
                                return false;
                            }
                            it->second.get()->set(true);
                        } else {
                            if (value == "") {
                                fprintf(stderr, "option '--%s' must be with value\n", lname.c_str());
                                return false;
                            }

                            it->second.get()->set(value);
                        }

                    // 处理短选项
                    } else {
                        int len = arg.length();
                        for (int k=1; k<len; ++k) {
                            char short_name = arg[k];

                            if (kHelpOptionShortName == arg[k]) {
                                Help();
                                exit(0);
                            }

                            if (_name_map.find(short_name) == _name_map.end()) {
                                fprintf(stderr, "unknow option '-%c'\n", short_name);
                                return false;
                            }

                            lname = _name_map[short_name];
                            auto it = _options.find(lname);
                            if (it == _options.end()) {
                                fprintf(stderr, "unepected error happed! 0_0...\n");
                                return false;
                            }

                            if (it->second.get()->is_bool_option) {
                                it->second.get()->set(true);

                            } else {
                                if (i+1 >= argc || k+1 != len) {
                                    fprintf(stderr, "option '-%c' must be with value\n", short_name);
                                    return false;
                                }

                                ++i;
                                value = argv[i];

                                it->second.get()->set(value);
                            }
                        }
                    }
                }

                ++i;
            }

            for (const auto & it : _options) {
                it.second.get()->check();
            }

        } catch (const std::exception & e) {
            fprintf(stderr, "%s\n", e.what());
            return false;
        }

        return true;
    }

    template <class T>
    T Get(const std::string & lname)
    {
        auto it = _options.find(lname);
        if (it == _options.end()) {
            throw option_exception(str_fmt("unkown option '--'", lname.c_str()));
        }

        auto opt = dynamic_cast<const Option<T> *>(it->second.get());
        if (opt == nullptr) {
            throw option_exception(str_fmt("bad cast, can not cast value of option '--%s' to type '%s'",
                                           lname.c_str(), type_name<T>().c_str()));
        }

        return opt->get();
    }

    const std::vector<std::string> & Rest() const
    {
        return _rest;
    }

    void Help()
    {
        fprintf(stderr, "usage: %s", _name.c_str());
        for (const auto & it : _options) {
            const auto & t = *it.second.get();
            if (t.is_necessary) {
                fprintf(stderr, " --%s=%s", t.long_name.c_str(), t.long_name.c_str());
            }
        }
        fprintf(stderr, " ...\n");

        fprintf(stderr, "options:\n");
        for (const auto & it : _options) {
            const auto & t = *it.second.get();
            if (t.short_name == '\0') {
                fprintf(stderr, "          --%-20s   %s\n", t.long_name.c_str(), t.desc.c_str());
            } else {
                fprintf(stderr, "    -%-2c   --%-20s   %s\n", t.short_name, t.long_name.c_str(), t.desc.c_str());
            }
        }
        fprintf(stderr, "    -%-2c   --%-20s   %s\n", kHelpOptionShortName, kHelpOptionLongName.c_str(), kHelpMessage.c_str());
    }

private:
    void CheckOption(const std::string & long_name, char short_name)
    {
        if (long_name == "") {
            throw option_exception("option must has a name");
        }

        if(_options.find(long_name) != _options.end()) {
            throw option_exception(str_fmt("multipule defined option '%s'", long_name.c_str()));
        }

        if (short_name != '\0' && _name_map.find(short_name) != _name_map.end()) {
            throw option_exception(str_fmt("multipule defined option '%c'", short_name));
        }
    }

private:
    std::string _name;
    std::vector<std::string> _rest;
    std::map<char, std::string> _name_map;
    std::map<std::string, std::unique_ptr<OptionBase>> _options;
};

} /* namespace option */

#endif /* OPTION_H */
