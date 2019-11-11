#include <arduino.h>
#include <LiquidCrystal_I2C.h>

#include "lcd_consts.h"
#include "utils.h"

#define LCD_I2C_PORT 0x3F
#define LCD_COL_NO 16
#define LCD_ROW_NO 2
#define LCD_TEMP_ICON 0
#define LCD_HUMIDITY_ICON 1
#define LCD_DEGREE_ICON 2
#define LCD_PRESSURE_ICON 3
#define LCD_TIME_ICON 4
#define LCD_DATE_ICON 5

byte tempIconBytes[8] = {
    0b00100,
    0b00110,
    0b00100,
    0b00110,
    0b00100,
    0b01110,
    0b01110,
    0b00000};

byte humidityIconBytes[8] = {
    0b00100,
    0b00100,
    0b01110,
    0b01110,
    0b10111,
    0b10111,
    0b01110,
    0b00000};

byte degreeIconBytes[8] = {
    0b00010,
    0b00101,
    0b00010,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000};

byte pressureIconBytes[8] = {
    0b00000,
    0b00100,
    0b00100,
    0b00100,
    0b10101,
    0b01110,
    0b00100,
    0b00000};

byte timeIconBytes[8] = {
    0b00000,
    0b01110,
    0b10101,
    0b10111,
    0b10001,
    0b01110,
    0b00000,
    0b00000};

byte dateIconBytes[8] = {
    0b11111,
    0b10001,
    0b10101,
    0b11101,
    0b10101,
    0b10101,
    0b10001,
    0b11111};

LiquidCrystal_I2C lcd(LCD_I2C_PORT, LCD_COL_NO, LCD_ROW_NO);

void printDate(MeasuredData *data);
void printTime(MeasuredData *data);
void printTemperature(MeasuredData *data);
void printHumidity(MeasuredData *data);
void printPressure(MeasuredData *data);

void initLCD()
{
  lcd.init();
  lcd.backlight();

  lcd.createChar(LCD_TEMP_ICON, tempIconBytes);
  lcd.createChar(LCD_HUMIDITY_ICON, humidityIconBytes);
  lcd.createChar(LCD_DEGREE_ICON, degreeIconBytes);
  lcd.createChar(LCD_PRESSURE_ICON, pressureIconBytes);
  lcd.createChar(LCD_TIME_ICON, timeIconBytes);
  lcd.createChar(LCD_DATE_ICON, dateIconBytes);
}

void printLCDWelcome()
{
  lcd.setCursor(3, 0);
  lcd.print("Termometr");
  lcd.setCursor(1, 1);
  lcd.print("J. Lubiatowska");
}

void printLCDInfo(MeasuredData *data)
{
  lcd.clear();

  lcd.setCursor(0, 0);
  printDate(data);
  lcd.setCursor(0, 1);
  printTime(data);

  delay(1000);
  lcd.clear();

  lcd.setCursor(0, 0);
  printTemperature(data);
  lcd.setCursor(0, 1);
  printHumidity(data);

  delay(1000);
  lcd.clear();

  lcd.setCursor(0, 0);
  printPressure(data);

  delay(1000);
}

void printDate(MeasuredData *data)
{
  lcd.write((byte)LCD_DATE_ICON);
  lcd.print(" ");
  lcd.print(withLeadingZero(data->dt.year, "%04d"));
  lcd.print("-");
  lcd.print(withLeadingZero(data->dt.month));
  lcd.print("-");
  lcd.print(withLeadingZero(data->dt.day));
}

void printTime(MeasuredData *data)
{
  lcd.write((byte)LCD_TIME_ICON);
  lcd.print(" ");
  lcd.print(withLeadingZero(data->dt.hour));
  lcd.print(":");
  lcd.print(withLeadingZero(data->dt.minute));
  lcd.print(":");
  lcd.print(withLeadingZero(data->dt.second));
}
void printTemperature(MeasuredData *data)
{
  lcd.write((byte)LCD_TEMP_ICON);
  lcd.print(" ");
  lcd.print(data->tempC);
  lcd.print(" ");
  lcd.write((byte)LCD_DEGREE_ICON);
  lcd.print("C");
}
void printHumidity(MeasuredData *data)
{
  lcd.write((byte)LCD_HUMIDITY_ICON);
  lcd.print(" ");
  lcd.print(data->humidity);
  lcd.print(" %");
}
void printPressure(MeasuredData *data)
{
  lcd.write((byte)LCD_PRESSURE_ICON);
  lcd.print(" ");
  lcd.print(data->pressure);
  lcd.print(" hPa");
}