#include <Arduino.h>
#include <string>

#include "common.h"
#include "rtos.h"

RTOS_Task::RTOS_Task() : id(0), exec(nullptr), ttl(0), last(0), period(0), priority(0) {}

RTOS_Task::RTOS_Task(Function exec, uint32_t ttl, uint32_t period, Byte priority)
    : id(0), exec(exec), ttl(ttl), last(0), period(period), priority(priority) {}

RTOS_Scheduler::RTOS_Scheduler() {
    SP = RTOS_STACK_MAX - 1;
}

void RTOS_Scheduler::add(RTOS_Task task) {
    TaskStack[SP++] = task;
}

void RTOS_Scheduler::kill(uint32_t id) {
    for (uint32_t taskNum = 0; taskNum < RTOS_STACK_MAX; taskNum++) {
        if (TaskStack[taskNum].id == id) {
            TaskStack[taskNum].priority = RTOS_PRIORITY_DEAD;
            break;
        }
    }
}

void RTOS_Scheduler::listSerial() {
    for (uint32_t taskNum = 0; taskNum < RTOS_STACK_MAX; taskNum++) {
        if (TaskStack[taskNum].id != 0) {
            Serial.printf("Name: %lu\nTTL: %lu\nLast: %lu\nPeriod: %lu\nPriority: %u\n",
                          TaskStack[taskNum].id,
                          TaskStack[taskNum].ttl,
                          millis() - TaskStack[taskNum].last,
                          TaskStack[taskNum].period,
                          TaskStack[taskNum].priority);
        }
    }
}

void RTOS_Scheduler::run() {
    RTOS_Task *task;
    uint32_t curMillis = millis();
    for (uint32_t taskNum = 0; taskNum < RTOS_STACK_MAX - 1; taskNum++) {
        task = &TaskStack[taskNum];
        if (task->id == 0 || task->priority == RTOS_PRIORITY_DEAD) continue;
        if (curMillis < (task->period + task->last)) continue;
        task->exec();
        task->last = curMillis;
        if (task->ttl != 0 && (curMillis - task->last) >= task->ttl) {
            Serial.printf("Task %lu Died\n", task->id);
            task->priority = RTOS_PRIORITY_DEAD;
        }
    }
}