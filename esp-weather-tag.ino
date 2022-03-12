#include <time.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>

#define MY_NTP_SERVER "ca.pool.ntp.org"
#define MY_TZ "EST5EDT,M3.2.0,M11.1.0"

time_t now;
tm tm;    

void showTime() {
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
}

void setup() {
	WiFi.mode(WIFI_STA);
  	// Initialize serial port
	Serial.begin(9600);

  configTime(MY_TZ, MY_NTP_SERVER);

	WiFiManager wm;

	bool connectresult;
	connectresult = wm.autoConnect();
	if(!connectresult) {
		Serial.println("Failed to connect");
		ESP.restart();
	} 
	else {
		Serial.println("Connected");
	}
  time(&now);
  localtime_r(&now, &tm);
  delay(2000);     
}

void loop() {
  do {
    showTime();
    delay(2000);
  } while (tm.tm_hour > 0 || tm.tm_sec > 5);
  
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
  for (int i = 0; i < 23; i++) {
    Serial.print(F("temp hour "));
    Serial.print(i);
    Serial.print(F(": "));
    Serial.print(String(doc["hourly"][i]["temp"]));
    Serial.println(F("C"));
    ESP.deepSleep(3595e6);
  }
}
