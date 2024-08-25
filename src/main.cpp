#include <SPI.h>
#include <Wire.h>

#include "seccore/auth.h"

#include "io/mfrc522.h"
#include "io/buzzer.h"
#include "io/ssd1306.h"

#include "config.h"
#include "common.h"

#include "rtos/rtos.h"

unsigned char KnownKey[][32] = {
	{0xD3, 0x57, 0x1B, 0xC},
};

RTOS_Scheduler rtos;

SSD1306 display;

#if RFID_ENABLE == 1
RFIDScanner rfid(SPI);
#endif

#if BUZZER_ENABLE == 1
Buzzer buzzer;
#endif

void checkRfid()
{
	Serial.println("Checking for card");
#if RFID_ENABLE == 1
	if (!rfid.isCardPresent())
		return;

	unsigned char *uidBytes = rfid.ReadCard();

	if (checkSecurityKey(uidBytes))
	{
#if BUZZER_ENABLE == 1
		buzzer.beep(BEEP_SUCCESS);
#endif
		display.drawMark();
	}
	else
	{
#if BUZZER_ENABLE == 1
		buzzer.beep(BEEP_FAILURE);
#endif
		display.drawCross();
	}

	Serial.print("UID: ");
	for (int i = 0; i < rfid.mfrc522.uid.size; i++)
	{
		Serial.print("0x");
		if (uidBytes[i] < 0x10)
		{
			Serial.print("0");
		}
		Serial.print(uidBytes[i], HEX);
		Serial.print(" ");
	}
	Serial.println("");
#endif
}

void setup()
{
	Serial.begin(115200);
	display.init(Wire);
	Serial.println("Initializing...");
	display.drawLogo();

	addSecurityKey(KnownKey[0]);

	RTOS_Task rfidTask(rtos.tid++, checkRfid, RTOS_DEFAULT_TTL, RTOS_DEFAULT_PERIOD, 0);
	RTOS_Task buzzerTask(rtos.tid++, []() {
		buzzer.update();
	}, RTOS_DEFAULT_TTL, RTOS_DEFAULT_PERIOD, 0);
	RTOS_Task displayClean(rtos.tid++, []() {
		display.screen.clearDisplay();
		display.screen.display();
	}, 10, 5000, 125);

	rtos.add(rfidTask);
	rtos.add(buzzerTask);
	rtos.add(displayClean);

	Serial.println("Initialization success");
}

void loop()
{
	rtos.run();
}