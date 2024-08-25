#ifndef _SECSYS_AUTH_H_
#define _SECSYS_AUTH_H_

#include <vector>
#include "common.h"

typedef Byte SecurityKey[32];

std::vector<SecurityKey> AuthorizedKeys;

void addSecurityKey(Byte *KeyHash);
void removeSecurityKey(Byte *KeyHash);
bool checkSecurityKey(Byte *KeyHash);

#endif