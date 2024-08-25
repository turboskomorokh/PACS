#ifndef _SECSYS_BUTTON_H_
#define _SECSYS_BUTTON_H_

#include "pin.h"

class Button : PinInput {
public:
    Button();
    Button(int pin);

    bool read();
};

#endif