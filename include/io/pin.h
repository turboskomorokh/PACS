#ifndef _SECSYS_PIN_IN_H_
#define _SECSYS_PIN_IN_H_

class PinInput {
protected:
    int pin;
public:
    PinInput(int pin);
};

class PinOutput {
protected:
    int pin;
public:
    PinOutput(int pin);
};

#endif