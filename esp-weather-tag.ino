#include <LOLIN_EPD.h>
#include <Adafruit_GFX.h>
#include <time.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <PolledTimeout.h>
#include <ESP8266HTTPClient.h>
#include <LittleFS.h>

#define MY_NTP_SERVER "ca.pool.ntp.org"
#define MY_TZ "EST5EDT,M3.2.0,M11.1.0"

#define EPD_CS D0
#define EPD_DC D8
#define EPD_RST -1  // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY -1 // can set to -1 to not use a pin (will wait a fixed delay)

LOLIN_SSD1680 EPD(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI

//testing github verification

time_t now;
tm tm;

void setup() {
   // Initialize serial port
   Serial.begin(9600);
   Serial.println("updating display");
   LittleFS.begin();
   EPD.begin();
   updateDisplay();
   if (!checkfortime()) {
      incrementTime();
      //ESP.deepSleep(3565000000);
      Serial.println("this is incrementation");
      ESP.deepSleep(10000000);
   }
   configTime(MY_TZ, MY_NTP_SERVER);
   fetchandwritedata();
   time(&now);                       // read the current time
   localtime_r(&now, &tm);   
   while(tm.tm_sec != 60) {
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
   http.GET();                                  //Send the request
   
   File file = LittleFS.open("/data.json", "r+");
   file.print(http.getStream());
   file.close();
   http.end();   //Close connection
}

bool checkfortime() {
   File file = LittleFS.open("/hourcheck.txt", "r+");
   Serial.println(file.read());
   if (file.read() == 25) {
      file.print("1");
      file.close();
      return true;
   } else {
      file.close();
      return false;
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
