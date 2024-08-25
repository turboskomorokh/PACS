#ifndef _SECSYS_RTOS_H_
#define _SECSYS_RTOS_H_

#include "config.h"

#define RTOS_PRIORITY_DEAD 255

struct RTOS_Task
{
    uint32_t id;
    Byte priority;

    Function exec;
    
    uint32_t ttl;
    uint32_t last;
    uint32_t period;
    RTOS_Task();    
    RTOS_Task(uint32_t id, Function exec, uint32_t ttl, uint32_t period, Byte priority);
};

struct RTOS_Scheduler
{
private:
    uint32_t SP; // StackPointer

public:
    uint32_t tid = 0;
    RTOS_Task TaskStack[RTOS_STACK_MAX];

    void add(RTOS_Task task);
    void kill(uint32_t id);
    void run();

    void listSerial();

    RTOS_Scheduler();
};

#endif