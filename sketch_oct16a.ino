#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

#include "lcd_consts.h"
#include "serial.h"
#include "sd_card.h"
#include "utils.h"
#include "web_client.h"

#define DHT_PIN 			2
#define DHT_TYPE 			DHT11

#define DEBUG				0
#define LOCAL				1

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
	setupWiFiConnection();

	delay(2000);
}

void loop()
{
	#if DEBUG == 1
		Serial.println("Read measured data");
	#endif
	readMeasuredData();

	#if DEBUG == 1
		Serial.println("Check measured data correct");
	#endif
	if (data.readFailed)
	{
		Serial.println("Failed to read from DHT sensor!");
		delay(2000);
		return;
	}

	printSerialInfo(&data);
	saveOnSDCard("dane.csv", &data);
	sendData(&data);
	printLCDInfo(&data);
}

void readMeasuredData()
{
	data.readFailed = false;
	data.dt = clock.getDateTime();
	data.humidity = dht.readHumidity();
	#if DEBUG == 1
		Serial.print("Readed humidity: ");
		Serial.println(data.humidity);
	#endif
	if (isnan(data.humidity))
	{
		data.readFailed = true;
		return;
	}
	data.tempC = dht.readTemperature();
	#if DEBUG == 1
		Serial.print("Readed temperature C: ");
		Serial.println(data.tempC);
	#endif
	if (isnan(data.tempC))
	{
		data.readFailed = true;
		return;
	}
	data.tempF = dht.readTemperature(true);
	#if DEBUG == 1
		Serial.print("Readed temperature F: ");
		Serial.println(data.tempF);
	#endif
	if (isnan(data.tempF))
	{
		data.readFailed = true;
		return;
	}

	data.heatIndexF = dht.computeHeatIndex(data.tempF, data.humidity);
	data.heatIndexC = dht.computeHeatIndex(data.tempF, data.humidity, false);
	data.pressure = bmp.readPressure() / 100;
}
