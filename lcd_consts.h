#ifndef __lcd_consts_h
#define __lcd_consts_h

#include "utils.h"

union Icon {
    uint64_t tmplNumber;
    uint8_t tmplArray[8];
};

void initLCD();
void printLCDWelcome();
void printLCDInfo(MeasuredData *data);

#endif
