#include "io/mfrc522.h"

RFIDScanner::RFIDScanner(SPIClass &SPI) : mfrc522(RFID_MFRC552_SS_PIN, RFID_MFRC552_RST_PIN)
{
    SPI.begin();
    mfrc522.PCD_Init();
    mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
    mfrc522.PCD_AntennaOff();
    mfrc522.PCD_AntennaOn();
}

bool RFIDScanner::isCardPresent()
{
    return mfrc522.PICC_IsNewCardPresent();
}

unsigned char *RFIDScanner::ReadCard()
{
    mfrc522.PICC_ReadCardSerial();
    mfrc522.PICC_HaltA();
    return mfrc522.uid.uidByte;
}