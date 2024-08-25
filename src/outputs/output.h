#ifndef _SECSYS_RELAY_H_
#define _SECSYS_RELAY_H_

#include "output.h"

class PinOutput {
protected:
    int pin;
public:
    PinOutput(int pin);
};

#endif