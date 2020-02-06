#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "lcd_consts.h"
#include "utils.h"

#define LCD_I2C_PORT              0x3F
#define LCD_COL_NO                16
#define LCD_ROW_NO                2

#define LCD_TEMP_ICON             0
#define LCD_TEMP_ICON_TMPL        0x000E0E0406040604


#define LCD_HUMIDITY_ICON         1
#define LCD_HUMIDITY_ICON_TMPL    0x000E17170E0E0404

#define LCD_DEGREE_ICON           2
#define LCD_DEGREE_ICON_TMPL      0x0000000000020502

#define LCD_PRESSURE_ICON         3
#define LCD_PRESSURE_ICON_TMPL    0x00040E1504040400

#define LCD_TIME_ICON             4
#define LCD_TIME_ICON_TMPL        0x00000E1117150E00

#define LCD_DATE_ICON             5
#define LCD_DATE_ICON_TMPL        0x1F1115151D15111F


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

  lcd.createChar(LCD_TEMP_ICON, prepareIcon(LCD_TEMP_ICON_TMPL).tmplArray);
  lcd.createChar(LCD_HUMIDITY_ICON, prepareIcon(LCD_HUMIDITY_ICON_TMPL).tmplArray);
  lcd.createChar(LCD_DEGREE_ICON, prepareIcon(LCD_DEGREE_ICON_TMPL).tmplArray);
  lcd.createChar(LCD_PRESSURE_ICON, prepareIcon(LCD_PRESSURE_ICON_TMPL).tmplArray);
  lcd.createChar(LCD_TIME_ICON, prepareIcon(LCD_TIME_ICON_TMPL).tmplArray);
  lcd.createChar(LCD_DATE_ICON, prepareIcon(LCD_DATE_ICON_TMPL).tmplArray);
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

Icon prepareIcon(uint64_t iconTmpl) {
  Icon icon;

  icon.tmplNumber = iconTmpl;

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
