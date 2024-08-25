#ifndef _SECSYS_MFRC522_H_
#define _SECSYS_MFRC522_H_

#include <MFRC522.h>

#include "config.h"

class RFIDScanner {
public:
 MFRC522 mfrc522;
 
 RFIDScanner(SPIClass &SPI);

 bool isCardPresent();
 unsigned char *ReadCard();
};

#endif