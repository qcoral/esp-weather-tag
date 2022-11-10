/*
  ESP Weather Tag. Please refer to README.md for more information. 
  Copyright (C) 2022  dari-studios

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* 
  Pin Mapping for Lolin ePaper SSD1680 to Wemos D1 Mini V4.0.0
  3V3 - 3.3V
  BUSY - No Pin
  CS - GPIO16/D0
  SCK - GPIO14/D5
  MOSI - GPIO13/D7
  DC - GPIO15/D8
  RST - RST 
  GND - GND
*/

#include <LOLIN_EPD.h>
#include <Adafruit_GFX.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <LittleFS.h>

#define MY_NTP_SERVER "ca.pool.ntp.org"  //NTP server
#define MY_TZ "EST5EDT,M3.2.0,M11.1.0"   //timezone, according to IANA standard

#define EPD_CS D0    // chip select
#define EPD_DC D8    // data/command
#define EPD_RST -1   // share with microcontroller reset
#define EPD_BUSY -1  // waits a fixed delay instead of using a pin, some sort of issue with that

LOLIN_SSD1680 EPD(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY);  //set up hardware SPI

time_t now;  //create object that can store time
tm tm;       //create struct to access time from

void setup() {

  Serial.begin(9600);
  LittleFS.begin();
  EPD.begin();

/* 
  If there have been 24 updates, or hour.txt does not exist then do reset routine. Otherwise increment hour counter and go to sleep 
*/

  if (checkfortime()) {
    updateDisplay();  //Update display with corresponding data using hour.txt and data.json.
    incrementTime();
    Serial.println("this is incrementation");
    //ESP.deepSleep(3598500000); 59 min and 58.5 seconds, leaves time for the reset routine to count down.
    ESP.deepSleep(10000000);  // 10 seconds
  }

/*
  reset routine
*/
  LittleFS.format();  //reset filesystem when resetting data and time

  File hour = LittleFS.open("/hour.txt", "w"); //Create and write to hour counter
  hour.print("0");
  hour.close();

  fetchandwritedata(); //self explanatory

  configTime(MY_TZ, MY_NTP_SERVER);
  time(&now);              //fetch time and store it into object "now"
  localtime_r(&now, &tm);  //take time value and convert it into local calendar, then store in tm struct

  while (tm.tm_hour != 23 && tm.tm_min != 59 && tm.tm_sec != 59) {  //keep refreshing time till 23:59:59
    time(&now);
    localtime_r(&now, &tm);
  }

  ESP.restart();
}

void updateDisplay() { //parses data from json, then uses the hour to display the correct data. If no json file then return. No write operations
  if (!LittleFS.exists("/data.json")) {
    return;
  }

  File data = LittleFS.open("/data.json", "r");
  File hour = LittleFS.open("/hour.txt", "r");

  DynamicJsonDocument doc(24576);

  DeserializationError error = deserializeJson(doc, data);
  data.close();  //data file is no longer needed after it is parsed
  int time = hour.read() - '0';
  hour.close();  // same with time
  Serial.print("Update: ");
  Serial.println(time);
  Serial.print(F("temp hour "));
  Serial.print(time);
  Serial.print(F(": "));
  Serial.print(String(doc["hourly"][time]["temp"]));
  Serial.println(F("C"));
}

void fetchandwritedata() { //fetches fresh data and writes it to data.json. Creates a new file and writes to it
  /*
  Connect to internet
  TODO: Add failsafe in case no internet connection by 23:59
  */
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  wm.autoConnect();

  WiFiClient wc;
  HTTPClient http;

  http.useHTTP10(true);
  http.begin(wc, "http://api.openweathermap.org/data/2.5/onecall?lat=***REMOVED***&lon=***REMOVED***&exclude=minutely,daily,alerts,current&appid=***REMOVED***&units=metric&lang=en");
  http.GET();

  //write data
  File data = LittleFS.open("/data.json", "w+");
  data.print(http.getStream());
  data.close();
  http.end();
}

bool checkfortime() {  //Waits for 24 updates, returns true before 25th starts. If not hour.txt is present then return false. No file created
  File hour = LittleFS.open("/hour.txt", "r");
  Serial.println(hour.read());
  if (hour.read() == 24) {  //even though the time value is zero indexed, we don't add a delay before the reset routine so it goes one over before resetting.
    hour.close();
    return false;
  } else {
    hour.close();
    return true;
  }
  return false;
}

void incrementTime() {  //read time, increment, wipe current time, write new time. Write operations.
  File hour = LittleFS.open("/hour.txt", "r+"); //get val
  int time = hour.read() - '0'; 
  time++;
  Serial.println(time);
  hour.close();

  LittleFS.remove("/hour.txt"); //wipe

  File hour = LittleFS.open("/hour.txt", "w"); //write val
  hour.print(time);
  hour.close();
}

void loop() {
}