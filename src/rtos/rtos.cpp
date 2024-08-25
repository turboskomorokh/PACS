#include <Arduino.h>
#include "config.h"
#include "common.h"
#include "rtos/rtos.h"

RTOS_Task::RTOS_Task() : id(0), exec([]() {}), ttl(0), last(0), period(0), priority(RTOS_PRIORITY_DEAD) {}

RTOS_Task::RTOS_Task(uint32_t id, Function exec, uint32_t ttl, uint32_t period, Byte priority)
    : id(id), exec(exec), ttl(ttl), last(0), period(period), priority(priority) {}

RTOS_Scheduler::RTOS_Scheduler() : SP(0) {}

void RTOS_Scheduler::add(RTOS_Task task)
{
    if (SP < RTOS_STACK_MAX)
    {
        TaskStack[SP++] = task;
    }
}

void RTOS_Scheduler::kill(uint32_t id)
{
    for (uint32_t taskNum = 0; taskNum < RTOS_STACK_MAX; taskNum++)
    {
        if (TaskStack[taskNum].id == id)
        {
            TaskStack[taskNum].priority = RTOS_PRIORITY_DEAD;
            break;
        }
    }
}

void RTOS_Scheduler::listSerial()
{
    for (uint32_t taskNum = 0; taskNum < RTOS_STACK_MAX; taskNum++)
    {
        Serial.printf("ID: %lu\nTTL: %lu\nLast: %lu\nPeriod: %lu\nPriority: %u\n",
                      TaskStack[taskNum].id,
                      TaskStack[taskNum].ttl,
                      millis() - TaskStack[taskNum].last,
                      TaskStack[taskNum].period,
                      TaskStack[taskNum].priority);
    }
}

void RTOS_Scheduler::run()
{
    RTOS_Task *task;
    uint32_t curMillis = millis();

    for (Byte i = 0; i < RTOS_PRIORITY_DEAD - 1; i++)
    {
        for (uint32_t taskNum = 0; taskNum < RTOS_STACK_MAX - 1; taskNum++)
        {
            task = &TaskStack[taskNum];

            if (task->priority != i)
                continue;

            if (curMillis - task->last < task->period)
                continue;

            if (!task->exec)
                continue;

            task->exec();
            task->last = curMillis;

            if (task->ttl != 0 && (curMillis - task->last) >= task->ttl)
            {
                Serial.println("Task Died");
                task->priority = RTOS_PRIORITY_DEAD;
            }
        }
    }
}