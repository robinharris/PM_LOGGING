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

void SDS_Setup(){
    // Serial1.begin(9600);
}

void GPS_Setup(){
    // setup GPS receiver
}

boolean writeToSD(){
    // set up SD Card
}

void loopGPS(){
    // receive sentences from GPS receiver
}

void loopSDS(){
    // receive readings from SDS sensor
}

void setup(){
    SDS_Setup();
    GPS_Setup();
    Serial.begin(115200);

}

void loop(){
    loopGPS();
    loopSDS();
    writeToSD();
}