#include <stdio.h>

#include "ralph/common/logger.h"

int main()
{
    printf("-- DEBUG filter --\n");
    LogVerbose("this is a %s message!", "verbose");
    LogDebug  ("this is a %s message!", "debug  ");
    LogInfo   ("this is a %s message!", "info   ");
    LogKey    ("this is a %s message!", "key    ");
    LogWarn   ("this is a %s message!", "warn   ");
    LogError  ("this is a %s message!", "error  "  );

    printf("\n-- KEY filter --\n");
    ralph::Logger::SetFilter(ralph::Logger::kLevelKey);
    LogVerbose("this is a %s message!", "verbose");
    LogDebug  ("this is a %s message!", "debug  ");
    LogInfo   ("this is a %s message!", "info   ");
    LogKey    ("this is a %s message!", "key    ");
    LogWarn   ("this is a %s message!", "warn   ");
    LogError  ("this is a %s message!", "error  ");

    printf("\n-- too long log --\n");
    ralph::Logger::SetFilter(ralph::Logger::kLevelInfo);
    LogInfo("OAuth addresses these issues by introducing an authorization layer"
            " and separating the role of the client from that of the resource"
            " owner. In OAuth, the client requests access to resources controlled"
            " by the resource owner and hosted by the resource server, and is"
            " issued a different set of credentials than those of the resource"
            " owner."
            "\n"
            "Instead of using the resource owner’s credentials to access protected"
            " resources, the client obtains an access token -- a string denoting a"
            " specific scope, lifetime, and other access attributes. Access tokens"
            " are issued to third-party clients by an authorization server with the"
            " approval of the resource owner. The client uses the access token to"
            " access the protected resources hosted by the resource server."
            "\n"
            "For example, an end-user (resource owner) can grant a printing"
            " service (client) access to her protected photos stored at a photosharing"
            " service (resource server), without sharing her username and"
            " password with the printing service. Instead, she authenticates"
            " directly with a server trusted by the photo-sharing service"
            " (authorization server), which issues the printing service delegationspecific"
            " credentials (access token)."
            "\n"
            "This specification is designed for use with HTTP ([RFC2616]). The"
            " use of OAuth over any protocol other than HTTP is out of scope."
            "\n"
            "The OAuth 1.0 protocol ([RFC5849]), published as an informational"
            " document, was the result of a small ad hoc community effort. This"
            " Standards Track specification builds on the OAuth 1.0 deployment"
            " experience, as well as additional use cases and extensibility"
            " requirements gathered from the wider IETF community. The OAuth 2.0"
            " protocol is not backward compatible with OAuth 1.0. The two versions"
            " may co-exist on the network, and implementations may choose to"
            " support both. However, it is the intention of this specification"
            " that new implementations support OAuth 2.0 as specified in this"
            " document and that OAuth 1.0 is used only to support existing"
            " deployments. The OAuth 2.0 protocol shares very few implementation"
            " details with the OAuth 1.0 protocol. Implementers familiar with"
            " OAuth 1.0 should approach this document without any assumptions as to"
            " its structure and details.");
    return 0;
}
