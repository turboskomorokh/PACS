#include <Arduino.h>

#include "config.h"
#include "buzzer.h"

Buzzer::Buzzer()
{
    pinMode(pin, HIGH);
}

void Buzzer::beep(int frequency, uint32_t duration)
{
    tone(pin, frequency);
    beginTime = millis();
    beepDuration = duration;
    isBuzzing = true;
}

void Buzzer::update() {
    if (isBuzzing && millis() - beginTime >= beepDuration) {
        noTone(pin);
        isBuzzing = false;
    }
}