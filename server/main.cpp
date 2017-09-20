#include <set>
#include <string>

#include "ralph/common/option.h"
#include "ralph/common/logger.h"

int main(int argc, char *argv[])
{
    option::Options opts;
    std::set<std::string> action_set = {"start", "stop", "reload", "status"};
    opts.Add<std::string>("action", 'a', "start, stop, status or reload", true, "",
                          option::OneOfRestrict<std::string>(action_set));
    opts.Add<std::string>("config", 'c', "configure file, default: ../etc/configure.json",
                          false, "../etc/configure.json");

    if (!opts.Parse(argc, argv)) {
        opts.Help();
        return -1;
    }

    LogInfo("action: %s", opts.Get<std::string>("action").c_str());
    LogInfo("config: %s", opts.Get<std::string>("config").c_str());

    return 0;
}
