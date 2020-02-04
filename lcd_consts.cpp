#include <arduino.h>
#include <LiquidCrystal_I2C.h>

#include "lcd_consts.h"
#include "utils.h"

#define LCD_I2C_PORT              0x3F
#define LCD_COL_NO                16
#define LCD_ROW_NO                2

#define LCD_TEMP_ICON             0
#define LCD_TEMP_ICON_TMPL        0x04060406040E0E00

#define LCD_HUMIDITY_ICON         1
#define LCD_HUMIDITY_ICON_TMPL    0x04040E0E17170E00

#define LCD_DEGREE_ICON           2
#define LCD_DEGREE_ICON_TMPL      0x0205020000000000

#define LCD_PRESSURE_ICON         3
#define LCD_PRESSURE_ICON_TMPL    0x00040404150E0400

#define LCD_TIME_ICON             4
#define LCD_TIME_ICON_TMPL        0x000E1517110E0000

#define LCD_DATE_ICON             5
#define LCD_DATE_ICON_TMPL        0x1F11151D1515111F


LiquidCrystal_I2C lcd(LCD_I2C_PORT, LCD_COL_NO, LCD_ROW_NO);

Icon prepareIcon(uint64_t iconTempl);
void printDate(MeasuredData *data);
void printTime(MeasuredData *data);
void printTemperature(MeasuredData *data);
void printHumidity(MeasuredData *data);
void printPressure(MeasuredData *data);

void initLCD()
{
  lcd.init();
  lcd.backlight();

  lcd.createChar(LCD_TEMP_ICON, prepareIcon(LCD_TEMP_ICON_TMPL).tmpl);
  lcd.createChar(LCD_HUMIDITY_ICON, prepareIcon(LCD_HUMIDITY_ICON_TMPL).tmpl);
  lcd.createChar(LCD_DEGREE_ICON, prepareIcon(LCD_DEGREE_ICON_TMPL).tmpl);
  lcd.createChar(LCD_PRESSURE_ICON, prepareIcon(LCD_PRESSURE_ICON_TMPL).tmpl);
  lcd.createChar(LCD_TIME_ICON, prepareIcon(LCD_TIME_ICON_TMPL).tmpl);
  lcd.createChar(LCD_DATE_ICON, prepareIcon(LCD_DATE_ICON_TMPL).tmpl);
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

Icon prepareIcon(uint64_t iconTempl) {
  Icon icon;

  icon.tmpl[0] = (iconTempl >> 56) & 0xFF;
  icon.tmpl[1] = (iconTempl >> 48) & 0xFF;
  icon.tmpl[2] = (iconTempl >> 40) & 0xFF; 
  icon.tmpl[3] = (iconTempl >> 32) & 0xFF; 
  icon.tmpl[4] = (iconTempl >> 24) & 0xFF; 
  icon.tmpl[5] = (iconTempl >> 16) & 0xFF; 
  icon.tmpl[6] = (iconTempl >> 8) & 0xFF;
  icon.tmpl[7] = (iconTempl >> 0) & 0xFF;

  return icon;
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