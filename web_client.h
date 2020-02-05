#ifndef __web_client_h
#define __web_client_h

#include <WiFiEsp.h>

#include "utils.h"

void setupWiFiConnection();
void sendData(MeasuredData* data);

#endif