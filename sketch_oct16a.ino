#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

#include "lcd_consts.h"
#include "serial.h"
#include "sd_card.h"
#include "utils.h"

#define DHT_PIN 2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_BMP085 bmp;
DS3231 clock;

MeasuredData data;

void setup()
{
	initSerial();
	printSerialWelcome();
	initLCD();
	printLCDWelcome();

	dht.begin();
	bmp.begin();
	clock.begin();
	clock.setDateTime(__DATE__, __TIME__);
	Serial.print("Set time to: ");
	Serial.print(__DATE__);
	Serial.print(" ");
	Serial.println(__TIME__);

	initSDCard();

	delay(2000);
}

void loop()
{
	readMeasuredData();

	if (data.readFailed)
	{
		Serial.println("Failed to read from DHT sensor!");
		delay(2000);
		return;
	}

	printSerialInfo(&data);
	saveOnSDCard("dane.csv", &data);
	printLCDInfo(&data);
}

void readMeasuredData()
{
	data.dt = clock.getDateTime();
	data.humidity = dht.readHumidity();
	data.tempC = dht.readTemperature();
	data.tempF = dht.readTemperature(true);

	if (isnan(data.humidity) || isnan(data.tempC) || isnan(data.tempF))
	{
		data.readFailed = true;
		return;
	}
	else
	{
		data.readFailed = false;
	}

	data.heatIndexF = dht.computeHeatIndex(data.tempF, data.humidity);
	data.heatIndexC = dht.computeHeatIndex(data.tempF, data.humidity, false);
	data.pressure = bmp.readPressure() / 100;
}