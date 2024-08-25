#include <Arduino.h>
#include "io/pin.h"

PinOutput::PinOutput(int pin) : pin(pin) {
    pinMode(this->pin, OUTPUT);
}