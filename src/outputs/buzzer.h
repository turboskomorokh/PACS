#ifndef _SECSYS_BUZZER_H_
#define _SECSYS_BUZZER_H_

#include "config.h"

enum
{
    BEEP_SUCCESS = 1000,
    BEEP_FAILURE = 500,
};

class Buzzer
{
private:
    int pin = BUZZER_PIN;

    bool isBuzzing = false;

    uint32_t beginTime = 0,
             beepDuration = 0;

public:
    Buzzer();

    void beep(int frequency, uint32_t duration);

    void beep(int frequency)
    {
        beep(frequency, BUZZER_DEFAULT_DURATION_MS);
    }

    void update();
};

#endif