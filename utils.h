#ifndef __utils_h
#define __utils_h

#include <DS3231.h>

struct MeasuredData
{
    RTCDateTime dt;
    float humidity;
    float tempC;
    float tempF;
    float heatIndexF;
    float heatIndexC;
    bool readFailed;
    float pressure;
};

char *withLeadingZero(int value, const char *pattern = "%02d");

#endif