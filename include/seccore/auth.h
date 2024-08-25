#pragma once
#ifndef _SECSYS_AUTH_H_
#define _SECSYS_AUTH_H_

#include <vector>

typedef struct SecurityKey {
    unsigned char Data[32];
} SecurityKey;

extern std::vector<SecurityKey> AuthorizedKeys;

void addSecurityKey(unsigned char *KeyHash);
void removeSecurityKey(unsigned char *KeyHash);
bool checkSecurityKey(unsigned char *KeyHash);

#endif