#include <Arduino.h>
#include "io/pin.h"

PinInput::PinInput(int pin) : pin(pin) {
    pinMode(this->pin, INPUT);
}