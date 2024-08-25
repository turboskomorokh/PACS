#include <cstring>
#include "seccore/auth.h"

std::vector<SecurityKey> AuthorizedKeys;

bool checkSecurityKey(unsigned char *KeyHash) {
    for (const auto& key : AuthorizedKeys) {
        if (std::memcmp(key.Data, KeyHash, sizeof(keyHash)) == 0) {
            return true;
        }
    }
    return false;
}

void addSecurityKey(unsigned char *KeyHash) {
    SecurityKey newKey;
    std::memcpy(newKey.Data, KeyHash, 32);
    AuthorizedKeys.push_back(newKey);
}

void removeSecurityKey(unsigned char *KeyHash) {
    for (auto it = AuthorizedKeys.begin(); it != AuthorizedKeys.end(); ++it) {
        if (std::memcmp(it->Data, KeyHash, 32) == 0) {
            AuthorizedKeys.erase(it);
            return;
        }
    }
}
