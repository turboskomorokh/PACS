#include <cstring>
#include "seccore/auth.h"
#include <mbedtls/sha256.h>

void addSecurityKey(Byte *KeyHash)
{
    SecurityKey SecKey;
    memcpy(SecKey, KeyHash, 32);
    AuthorizedKeys.push_back(SecKey);
}

void removeSecurityKey(Byte *KeyHash)
{
    for (auto it = AuthorizedKeys.begin(); it != AuthorizedKeys.end(); ++it)
    {
        if (!memcmp(&(*it), KeyHash, 32))
        {
            AuthorizedKeys.erase(it);
            break;
        }
    }
}

bool checkSecurityKey(Byte *KeyHash)
{
    for (auto it = AuthorizedKeys.begin(); it != AuthorizedKeys.end(); ++it)
    {
        if (!memcmp(&(*it), KeyHash, 64))
            return true;
    }
    return false;
}