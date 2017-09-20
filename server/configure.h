#ifndef RALPH_SERVER_CONFIGURE_H
#define RALPH_SERVER_CONFIGURE_H

#include "json/json.h"

namespace ralph
{

extern const Json::Value & g_configure;

bool LoadConfigure(const char * file);

} /* namespace ralph */

#endif // RALPH_SERVER_CONFIGURE_H

