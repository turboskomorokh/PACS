#include <Arduino.h>

#include "common.h"
#include "config.h"

#include "io/button.h"

Button::Button(int pin) : PinInput(pin) {}

Button::Button() : PinInput(BUZZER_DEFAULT_PIN) {}

bool Button::read() {
    return digitalRead(this->pin);
}