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
  CS - GPIO12/D6
  SCK - GPIO14/D5
  MOSI - GPIO13/D7
  DC - GPIO15/D8
  RST - RST 
  GND - GND

  WAKE - GPIO16/D0 | MAKE SURE THIS IS CONNECTED OR IT WILL NOT WORK
*/

#include "settings.h" 

#include <LOLIN_EPD.h>
#include <Adafruit_GFX.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <LittleFS.h>
#include <PolledTimeout.h>

/*
<icons>
*/


#define EPD_CS D6    // chip select
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


  Serial.println("Starting main process"); //DBGPRNT
/* 
  Update display, increment, then wait until next hour. Reset after 24th update.
*/

if (!checkfortime()) {
    updateDisplay();  //Update display with corresponding data using hour.txt and data.json.
    incrementTime();
    //ESP.deepSleep(3598500000); 59 min and 58.5 seconds, leaves time for the reset routine to count down.
    Serial.println("time incremented, going to sleep"); //DBGPRNT
    ESP.deepSleep(10000000);  // 10 seconds
  } else {
    refreshdata();
  }
}

void updateDisplay() {  //parses data from json, then uses the hour to display the correct data. If no json file then return. No write operations
  Serial.println("updating display");

  if (!LittleFS.exists("/data.json")) {
    return;
  }

  File data = LittleFS.open("/data.json", "r");
  File hour = LittleFS.open("/hour.txt", "r");

  DynamicJsonDocument json(24576);

  DeserializationError error = deserializeJson(json, data);

  data.close();  //data file is no longer needed after it is parsed
  int time = hour.read();
  hour.close();  // same with time
  Serial.print("Update: ");
  Serial.println(time + 1);
  Serial.print(F("update hour "));
  Serial.print(time + 1);
  Serial.print(F(": "));
  Serial.print(String(json["hourly"][time]["temp"]));
  Serial.println(F("C"));
}

void refreshdata() {  //resets filesystem and hour count, stalls till 3:59:56, then refreshes data and restarts
  Serial.println("refreshing data"); //DBGPRNT

  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  configTime(MY_TZ, MY_NTP_SERVER);

  wm.autoConnect("esp-weather-tag"); //creates new network called esp-weather-tag, stalls until network is found

  WiFiClient wc;
  HTTPClient http;
  DynamicJsonDocument json(24576); //create json object


  time(&now);              //Fetch time and store it into object "now"
  localtime_r(&now, &tm);  //take time value and convert it into local calendar, then store in tm struct

  LittleFS.format();  //reset filesystem

  Serial.println("FS Formatted"); //DBGPRNT

  File hour = LittleFS.open("/hour.txt", "w");  //create hour file
  hour.write(0);
  hour.close();

  Serial.println("hour file written and stalling time"); //DBGPRNT

  /*
  while (tm.tm_hour != 13 || tm.tm_min != 32 || tm.tm_sec != 30) {  //keep stalling time till 03:59:56
    time(&now);
    localtime_r(&now, &tm);
    yield();
  }
  */

  Serial.println("time reached"); //DBGPRNT

  //fetch data
  http.useHTTP10(true);
  http.begin(wc, "http://api.openweathermap.org/data/2.5/onecall?lat=***REMOVED***&lon=***REMOVED***&exclude=minutely,daily,alerts,current&appid=***REMOVED***&units=metric&lang=en");
  http.GET();

  deserializeJson(json, http.getStream()); //deserialize https stream into json object

  Serial.println("data fetched"); //DBGPRNT

  //write data
  File data = LittleFS.open("/data.json", "w+");

  serializeJson(json, data); //serialize json object into a file
  Serial.println();

  data.close();
  http.end();

  Serial.println("data written, restarting"); //DBGPRNT

  ESP.restart(); //reboot into updates
}

bool checkfortime() {  //Waits for 24 updates, returns true before 25th starts. If not hour.txt is present then return false. No file created
  Serial.println("checkfortime is checking time"); //DBGPRNT

  if (!LittleFS.exists("/hour.txt")) {
    Serial.println("hour file does not exist"); //DBGPRNT
    return true;
  }

  File hour = LittleFS.open("/hour.txt", "r");

  Serial.print("checkfortime's hour is "); //DBGPRNT
  Serial.println(hour.read()); //DBGPRNT

  if (hour.read() == 24) {  //even though the time value is zero indexed, it's incremented after the update so it doesn't do a 25th
    hour.close();
    Serial.println("There has been 24 updates"); //DBGPRNT
    return true;
  } else {
    hour.close();
    Serial.println("There have not been 24 updates"); //DBGPRNT
    return false;
  }
}

void incrementTime() {  //read time, increment, wipe current time, write new time. Write operations.

  Serial.println("incrementing time"); //DBGPRNT

  File hour = LittleFS.open("/hour.txt", "r+");  //get val
  int time = hour.read();
  hour.close();
  LittleFS.remove("/hour.txt");

  File hourinc = LittleFS.open("/hour.txt", "w+");
  time++;
  hourinc.write(time);
  hourinc.close();

  Serial.println("time incremented"); //DBGPRNT
}

void loop() {
}