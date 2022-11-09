/*
  esp-weather-tag, refer to readme.md for more information. 
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

#include <LOLIN_EPD.h>
#include <Adafruit_GFX.h>
#include <time.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <PolledTimeout.h>
#include <ESP8266HTTPClient.h>
#include <LittleFS.h>

#define MY_NTP_SERVER "ca.pool.ntp.org"
#define MY_TZ "EST5EDT,M3.2.0,M11.1.0"  //timezone, according to

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

#define EPD_CS D0    // chip select
#define EPD_DC D8    // data/command
#define EPD_RST -1   // share with microcontroller reset
#define EPD_BUSY -1  // waits a fixed delay instead of using a pin, some sort of issue with that

LOLIN_SSD1680 EPD(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY);  //set up hardware SPI

time_t now;
tm tm;

void setup() {

  Serial.begin(9600);
  Serial.println("updating display");  //debug, probably will remove in future
  LittleFS.begin();
  EPD.begin();
  updateDisplay();  //update display before doing time operations (checking time + incrementation, then going to sleep)
  /* 

  if the 24th hour has passed, reset the hour, fetch new data, fetch new time, wait until the seconds hits 59, then restart the ESP 

  */

  if (checkfortime()) {
    incrementTime();
    Serial.println("this is incrementation");
    //ESP.deepSleep(3565000000); 59 min and 25 seconds, leaves time for the reset routine to count down. 
    ESP.deepSleep(10000000);  // 10 seconds
  }
  /*
    reset routine
  */
  configTime(MY_TZ, MY_NTP_SERVER);
  fetchandwritedata();
  time(&now);  // read the current time
  localtime_r(&now, &tm);
  while (tm.tm_sec != 60) {
  }
  ESP.restart();
}

void loop() {
}

void fetchandwritedata() {
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  wm.autoConnect();

  time(&now);
  localtime_r(&now, &tm);
  delay(2000);

  WiFiClient wc;
  HTTPClient http;

  http.useHTTP10(true);
  http.begin(wc, "http://api.openweathermap.org/data/2.5/onecall?lat=***REMOVED***&lon=***REMOVED***&exclude=minutely,daily,alerts,current&appid=***REMOVED***&units=metric&lang=en");  //Specify request destination
  http.GET();                                                                                                                                                                                   //Send the request

  File file = LittleFS.open("/data.json", "r+"); 
  file.print(http.getStream());
  file.close();
  http.end();  
}

bool checkfortime() {
  File file = LittleFS.open("/hourcheck.txt", "r+");
  Serial.println(file.read());
  if (file.read() == 24) {
    file.print("0");
    file.close();
    return false;
  } else {
    file.close();
    return true;
  }
}

void updateDisplay() {
  Serial.println("updating display");
  File file = LittleFS.open("/data.json", "r+");
  File file2 = LittleFS.open("/hourcheck.txt", "r+");

  DynamicJsonDocument doc(24576);

  DeserializationError error = deserializeJson(doc, file);
  file.close();
  int i = file2.read() - '0';
  Serial.println(i);
  Serial.print(F("temp hour "));
  Serial.print(i);
  Serial.print(F(": "));
  Serial.print(String(doc["hourly"][i]["temp"]));
  Serial.println(F("C"));
}

void incrementTime() {
  File file = LittleFS.open("/hourcheck.txt", "r+");
  int hour = file.read() - '0';
  hour++;
  file.close();
}