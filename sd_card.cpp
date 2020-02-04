#include <SPI.h>
#include <SD.h>

#include "sd_card.h"

#define CHIP_SELECT_PIN             10

void saveIntoFile(File file, MeasuredData *data);
void saveDateTime(RTCDateTime dt, File file);

void initSDCard() {
    if (!SD.begin(CHIP_SELECT_PIN)) {
        Serial.println("Error during SD card initialization!!!");
        return;
    }
    Serial.println("SD card initialized.");
}

void saveOnSDCard(String filename, MeasuredData *data) {
    String dataRow = "";
    File dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile)
    {
        saveIntoFile(dataFile, data);
        dataFile.close();
        Serial.println("Dane zapisane.");
    }
}

void saveIntoFile(File file, MeasuredData *data)
{
    saveDateTime(data->dt, file);
    file.print(";");

    file.print(data->humidity);
    file.print(";");

    file.print(data->tempC);
    file.print(";");
    
    file.print(data->tempF);
    file.print(";");
	
    file.print(data->heatIndexC);
    file.print(";");
	
    file.print(data->heatIndexF);
    file.print(";");
	
    file.print(data->pressure);
    file.println("");
}

void saveDateTime(RTCDateTime dt, File file) {
    
    file.print(withLeadingZero(dt.year, "%04d"));
    file.print("-");
    file.print(withLeadingZero(dt.month));
    file.print("-");
    file.print(withLeadingZero(dt.day));
    file.print(" ");
    file.print(withLeadingZero(dt.hour));
    file.print(":");
    file.print(withLeadingZero(dt.minute));
    file.print(":");
    file.print(withLeadingZero(dt.second));
}