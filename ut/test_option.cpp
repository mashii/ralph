#include <iostream>

#include "ralph/common/option.h"

using namespace std;

int main(int argc, char *argv[])
{
    option::Options opts;
    // bool类型选项
    opts.Add("all", 'a', "do not ignore entries starting with .");
    opts.Add("list", 'l', "use a long listing format");
    opts.Add("directory", 'd', "list directories themselves, not their contents");

    // 长选项`color`，没有对应的短选项，不是必须，默认为`auto`
    std::set<std::string> s = {"never", "auto", "always"};
    opts.Add<std::string>("color", '\0', "colorize the output; WHEN can be 'never', 'auto', or 'always' (the default); more info below", false, "auto", option::OneOfRestrict<std::string>(s));
    // 长选项`tabsize`，不是必须，默认为`8`，取值必须在 4 - 16 之间
    opts.Add<int>("tabsize", 't', "assume tab stops at each COLS instead of 8", false, 8, option::RangeRestrict<int>(4, 16));
    // 长选项`file`，必须，默认为`.`
    opts.Add<std::string>("file", 'f', "list file path", true, ".");

    if (!opts.Parse(argc, argv)) {
        opts.Help();
        return -1;
    }

    cout << "all: " << opts.Get<bool>("all") << endl;
    cout << "list: " << opts.Get<bool>("list") << endl;
    cout << "directory: " << opts.Get<bool>("directory") << endl;
    cout << "color: " << opts.Get<std::string>("color") << endl;
    cout << "tabsize: " << opts.Get<int>("tabsize") << endl;
    cout << "file: " << opts.Get<std::string>("file") << endl;

    const std::vector<std::string> & rest = opts.Rest();
    for (const auto & it : rest) {
        cout << " - " << it << endl;
    }

    return 0;
}
