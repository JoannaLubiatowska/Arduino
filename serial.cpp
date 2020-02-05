#include "serial.h"
#include "utils.h"

#define SERIAL_FREQUENCY 9600

void initSerial() {
	Serial.begin(SERIAL_FREQUENCY);
}
void printSerialWelcome()
{
    Serial.println("===============================");
	Serial.println("Termometr by Joanna Lubiatowska");
	Serial.println("===============================");
}
void printSerialInfo(MeasuredData *data) 
{
    Serial.print("Date: ");
	Serial.print(withLeadingZero(data->dt.year, "%04d"));
	Serial.print("-");
	Serial.print(withLeadingZero(data->dt.month));
	Serial.print("-");
	Serial.print(withLeadingZero(data->dt.day));
	Serial.print("\tTime: ");
	Serial.print(withLeadingZero(data->dt.hour));
	Serial.print(":");
	Serial.print(withLeadingZero(data->dt.minute));
	Serial.print(":");
	Serial.print(withLeadingZero(data->dt.second));
	Serial.print("\nHumidity: ");
	Serial.print(data->humidity);
	Serial.print(" %\nTemperature: ");
	Serial.print(data->tempC);
	Serial.print(" °C ");
	Serial.print(data->tempF);
	Serial.print(" °F\nPressure: ");
	Serial.print(data->pressure);
	Serial.print(" hPa\n\n");
}