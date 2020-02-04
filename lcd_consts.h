#ifndef __lcd_consts_h
#define __lcd_consts_h

#include "utils.h"

struct Icon {
    uint8_t tmpl[8];
};

void initLCD();
void printLCDWelcome();
void printLCDInfo(MeasuredData *data);

#endif
