#ifndef __sd_card_h
#define __sd_card_h

#include <arduino.h>
#include "utils.h"

void initSDCard();
void saveOnSDCard(String filename, MeasuredData *data);

#endif