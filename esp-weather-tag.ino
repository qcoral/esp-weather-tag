#include <LOLIN_EPD.h>
#include <Adafruit_GFX.h>
#include <time.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <PolledTimeout.h>
#include <ESP8266HTTPClient.h>

#define MY_NTP_SERVER "ca.pool.ntp.org"
#define MY_TZ "EST5EDT,M3.2.0,M11.1.0"

#define EPD_CS D0
#define EPD_DC D8
#define EPD_RST -1  // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY -1 // can set to -1 to not use a pin (will wait a fixed delay)

LOLIN_SSD1680 EPD(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI

time_t now;
tm tm;

void printMillis() {
  Serial.print(F("millis() = "));
  Serial.println(millis());
} 

void wakeupCallback() {  // unlike ISRs, you can do a print() from a callback function
  printMillis();  // show time difference across sleep; millis is wrong as the CPU eventually stops
  Serial.println(F("Woke from Light Sleep - this is the callback"));
  Serial.flush();
}

void printTime() {
   time(&now);                       // read the current time
   localtime_r(&now, &tm);           // update the structure tm with the current time
   Serial.print("year:");
   Serial.print(tm.tm_year + 1900);  // years since 1900
   Serial.print("\tmonth:");
   Serial.print(tm.tm_mon + 1);      // January = 0 (!)
   Serial.print("\tday:");
   Serial.print(tm.tm_mday);         // day of month
   Serial.print("\thour:");
   Serial.print(tm.tm_hour);         // hours since midnight  0-23
   Serial.print("\tsec:");
   Serial.print(tm.tm_sec);          // seconds after the minute  0-61*
   Serial.print("\twday");
   Serial.print(tm.tm_wday);         // days since Sunday 0-6
   Serial.println();
   EPD.clearBuffer();
   EPD.setCursor(0, 0);
   EPD.fillScreen(EPD_WHITE);
   EPD.setTextColor(EPD_RED);
   EPD.setTextWrap(true);
   EPD.print(String(tm.tm_mday));
   Serial.println("displaying date");
   EPD.display();
   delay(30000);
}

void setup() {
   // Initialize serial port
   Serial.begin(9600);
   EPD.begin();
   configTime(MY_TZ, MY_NTP_SERVER);
}

void loop() {
   WiFi.mode(WIFI_STA);
   WiFiManager wm;
   
   bool connectresult;
   connectresult = wm.autoConnect();
   if (!connectresult) {
      Serial.println("Failed to connect");
      ESP.restart();
   }
   else {
      Serial.println("Connected");
   }

   time(&now);
   localtime_r(&now, &tm);
   delay(2000);
   
   printTime();
   WiFiClient wc;
   HTTPClient http;

   http.useHTTP10(true);
   http.begin(wc, "http://api.openweathermap.org/data/2.5/onecall?lat=***REMOVED***&lon=***REMOVED***&exclude=minutely,daily,alerts,current&appid=***REMOVED***&units=metric&lang=en");  //Specify request destination
   http.GET();                                  //Send the request

   DynamicJsonDocument doc(24576);

   DeserializationError error = deserializeJson(doc, http.getStream());

   http.end();   //Close connection

   if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
   }
   for (int i = 1; i <= 23; i++) {
      Serial.print(F("temp hour "));
      Serial.print(i);
      Serial.print(F(": "));
      Serial.print(String(doc["hourly"][i]["temp"]));
      Serial.println(F("C"));
      EPD.clearBuffer();
      EPD.setCursor(0, 0);
      EPD.fillScreen(EPD_WHITE);
      EPD.setTextColor(EPD_BLACK);
      EPD.setTextWrap(true);
      EPD.setTextSize(5);
      EPD.print(String(doc["hourly"][i]["temp"]));
      EPD.display();
      lightsleep();
   }
}

void lightsleep() {
  WiFi.mode(WIFI_OFF);  // you must turn the modem off; using disconnect won't work
  extern os_timer_t *timer_list;
  timer_list = nullptr;  // stop (but don't disable) the 4 OS timers
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_set_wakeup_cb(wakeupCallback);
  wifi_fpm_open();
  //wifi_fpm_do_sleep(3595000000);
  //delay(3595000000 + 1);
  wifi_fpm_do_sleep(30000000);
  delay(30000000 + 1);
}
