#include <Arduino.h>
#include "output.h"

PinOutput::PinOutput(int pin) : pin(pin) {
    pinMode(this->pin, OUTPUT);
}