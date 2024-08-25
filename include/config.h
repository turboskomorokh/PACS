#ifndef _SECSYS_CONFIG_H_
#define _SECSYS_CONFIG_H_

// Wi-Fi Settings
#define WIFI_SSID "AP"
#define WIFI_PASSWORD "12345678"

// Button Settings
#define BUTTON_ENABLE 1

#define BUTTON_DEFAULT_PIN 15

// RFID Settings 
#define RFID_ENABLE 1

#define RFID_MFRC552_SS_PIN  5
#define RFID_MFRC552_RST_PIN 0

// Buzzer Settings
#define BUZZER_ENABLE 1

#define BUZZER_DEFAULT_PIN 14
#define BUZZER_DEFAULT_DURATION_MS 500

// RTOS Settings
#define RTOS_STACK_MAX 32
#define RTOS_DEFAULT_TTL 10
#define RTOS_DEFAULT_PERIOD 100

#endif