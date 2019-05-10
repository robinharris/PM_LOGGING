#include <Arduino.h>

/* 
This is the main sketch that drives a portable air quality monitor.
The components are:
    SDS011          Particulate sensor
    GPS module
    SD Card writer / reader
    STM32 microprocessor

The device takes readings every 10 seconds and logs
the time, location and sensor readings to an SD Card

Author:  Robin Harris
May 2019
*/

#include <Arduino.h>
#include <NMEAGPS.h>
#include <M5Stack.h>

// globals
float lat;
float lon;
float alt;
char timestampString [100];

NMEAGPS     gps;
gps_fix     fix;

void SDS_Setup(){
    Serial1.begin(9600, SERIAL_8N1, 23, 19);
    Serial.println("Started Serial1");
}

void loopGPS(){
    int hr;
    int min;
    int sec;
    int day;
    int mnth;
    int year;
    while (gps.available( Serial2 )) {
        fix = gps.read();
        if (fix.valid.location) {
            Serial.print( F("Location: ") );
            Serial.print( fix.latitude(), 6 );
            Serial.print( ',' );
            Serial.print( fix.longitude(), 6 );
            M5.Lcd.setTextColor(RED);
            M5.Lcd.setTextSize(2);
            M5.Lcd.setCursor(5,50);
            M5.Lcd.print( fix.latitude(), 6 );
            M5.Lcd.printf( "   " );
            M5.Lcd.println( fix.longitude(), 6 );
            M5.update();
            // set global variables
            lat = fix.latitude();
            lon = fix.longitude();
        }
        if (fix.valid.altitude)
            Serial.print( F(", Altitude: ") );
            Serial.print( fix.altitude() );
            Serial.println();
            M5.Lcd.setCursor(5,100);
            M5.Lcd.printf("Altitude: ");
            M5.Lcd.print( fix.altitude() );
            // set global variables
            alt = fix.altitude();
            M5.update();

        if (fix.valid.date)


        // set local variables for date and time
        year = fix.dateTime.year;
        mnth = fix.dateTime.month;
        day = fix.dateTime.day;
        hr = fix.dateTime.hours;
        min = fix.dateTime.minutes;
        sec = fix.dateTime.seconds;

        // create a global timestamp as a string
        sprintf(timestampString, "%02d:%02d:%d %02d:%02d:%02d", day, mnth, year, hr, min, sec);
        Serial.println(timestampString);
        M5.Lcd.setCursor(5,150);
        M5.Lcd.print(timestampString);
    }
}

boolean writeToSD(){
    // set up SD Card
}

void loopSDS(){
    char incomingChar[5];
    int availableChars;
    if(Serial1.available()){
        availableChars = Serial1.available();
        for (int i=0; i < availableChars; i++ ){
            incomingChar[i] = Serial1.read();
        }
        int numberOfChars = strlen(incomingChar);
        incomingChar[numberOfChars + 1]= '\0';
        Serial.println(incomingChar);
    }
}

void setup(){
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, 16, 17);
    M5.begin();
    M5.Lcd.setCursor(100, 5);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.printf("Location");
    M5.update();
    Serial.println(F("Starting main sketch"));
    SDS_Setup();
}

void loop(){
    loopGPS();
    loopSDS();
    writeToSD();
}
//