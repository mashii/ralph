#include "configure.h"

#include "ralph/common/logger.h"

namespace ralph
{

static Json::Value g_conf;
const Json::Value & g_configure = g_conf;

bool LoadConfigure(const char * file)
{
    Json::Reader reader;
    if (!reader.parse(file, g_conf, false)) {
        LogError("load configure file failed, %s",
                 reader.getFormatedErrorMessages().c_str());
        return false;
    }

    return true;
}

} /* namespace ralph */
