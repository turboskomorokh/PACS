#ifndef _SECSYS_RELAY_H_
#define _SECSYS_RELAY_H_

#include "output.h"

class Relay : public Output {
public:
    Relay(int pin);
}

#endif