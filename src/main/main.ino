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

#include <NMEAGPS.h>
#include <GPSport.h>

// globals
float lat;
float lon;
float alt;
char timestampString [100];


NMEAGPS     gps;
gps_fix     fix;

void SDS_Setup(){
    gpsPort.begin(9600); // this will default to Serial1 if it exists
    // this uses AltSoftwareSerial and pins 8 & 9 on an Uno
}

void loopGPS(){
    int hr;
    int min;
    int sec;
    int day;
    int mnth;
    int year;
    while (gps.available( gpsPort )) {
        fix = gps.read();

        Serial.print( F("Location: ") );
        if (fix.valid.location) {
            Serial.print( fix.latitude(), 6 );
            Serial.print( ',' );
            Serial.print( fix.longitude(), 6 );
    }

    Serial.print( F(", Altitude: ") );
    if (fix.valid.altitude)
        Serial.print( fix.altitude() );

    Serial.println();

    // set global variables
    lat = fix.latitude();
    lon = fix.longitude();
    alt = fix.altitude();

    // set local variables for date and time
    year = fix.dateTime.year;
    mnth = fix.dateTime.month;
    day = fix.dateTime.day;
    hr = fix.dateTime.hours;
    min = fix.dateTime.minutes;
    sec = fix.dateTime.seconds;

    // create a global timestamp as a string
    sprintf(timestampString, "%d:%02d:%02d %02d:%02d:%02d", year, mnth, day, hr, min, sec);
    Serial.println(timestampString);
    return;
    }
}

boolean writeToSD(){
    // set up SD Card
}

void loopSDS(){
    // receive readings from SDS sensor
}

void setup(){
    SDS_Setup();
    Serial.begin(115200);
    Serial.println(F("Starting main sketch"));
}

void loop(){
    loopGPS();
    loopSDS();
    writeToSD();
}