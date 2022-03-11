
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "networkname";
const char* password = "networkpwd";

void setup() {
  // Initialize serial port
	Serial.begin(9600);
	while (!Serial) continue;

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {

		delay(1000);
		Serial.print("Connecting..");

	}
}

void loop() {
	http.useHTTP10(true);
	WiFiClient wc;
	HTTPClient http;

   http.begin(wc, "https://api.openweathermap.org/data/2.5/onecall?lat=***REMOVED***&lon=***REMOVED***&exclude=minutely,daily,alerts,current&appid=***REMOVED***&units=metric&lang=en");  //Specify request destination
	http.GET();                                  //Send the request
   http.end();   //Close connection

   DynamicJsonDocument doc(24576);

   DeserializationError error = deserializeJson(doc, http.getStream());

   if (error) {
    	Serial.print(F("deserializeJson() failed: "));
    	Serial.println(error.f_str());
    	return;
   }

	JsonArray hourly = doc["hourly"];

	JsonObject hourly_0 = hourly[0];
	float hourly_0_temp = hourly_0["temp"]; // 2.2
	float hourly_0_feels_like = hourly_0["feels_like"]; // -0.67
	int hourly_0_humidity = hourly_0["humidity"]; // 53
	int hourly_0_clouds = hourly_0["clouds"]; // 20
	float hourly_0_wind_speed = hourly_0["wind_speed"]; // 2.78
	const char* hourly_0_weather_0_description = hourly_0_weather_0["description"]; // "few clouds"
	const char* hourly_0_weather_0_icon = hourly_0_weather_0["icon"]; // "02d"

	int hourly_0_pop = hourly_0["pop"]; // 0

	JsonObject hourly_1 = hourly[1];
	long hourly_1_dt = hourly_1["dt"]; // 1646935200
	float hourly_1_temp = hourly_1["temp"]; // 2.45
	float hourly_1_feels_like = hourly_1["feels_like"]; // -0.73
	int hourly_1_pressure = hourly_1["pressure"]; // 1021
	int hourly_1_humidity = hourly_1["humidity"]; // 55
	int hourly_1_clouds = hourly_1["clouds"]; // 0
	int hourly_1_visibility = hourly_1["visibility"]; // 10000
	float hourly_1_wind_speed = hourly_1["wind_speed"]; // 3.22
	int hourly_1_wind_deg = hourly_1["wind_deg"]; // 268
	float hourly_1_wind_gust = hourly_1["wind_gust"]; // 5.24

	JsonObject hourly_1_weather_0 = hourly_1["weather"][0];
	int hourly_1_weather_0_id = hourly_1_weather_0["id"]; // 800
	const char* hourly_1_weather_0_main = hourly_1_weather_0["main"]; // "Clear"
	const char* hourly_1_weather_0_description = hourly_1_weather_0["description"]; // "clear sky"
	const char* hourly_1_weather_0_icon = hourly_1_weather_0["icon"]; // "01d"

	int hourly_1_pop = hourly_1["pop"]; // 0

	JsonObject hourly_2 = hourly[2];
	long hourly_2_dt = hourly_2["dt"]; // 1646938800
	float hourly_2_temp = hourly_2["temp"]; // 2.39
	float hourly_2_feels_like = hourly_2["feels_like"]; // -0.67
	int hourly_2_pressure = hourly_2["pressure"]; // 1021
	int hourly_2_humidity = hourly_2["humidity"]; // 52
	int hourly_2_clouds = hourly_2["clouds"]; // 20
	int hourly_2_visibility = hourly_2["visibility"]; // 10000
	float hourly_2_wind_speed = hourly_2["wind_speed"]; // 3.05
	int hourly_2_wind_deg = hourly_2["wind_deg"]; // 268
	float hourly_2_wind_gust = hourly_2["wind_gust"]; // 4.98

	JsonObject hourly_2_weather_0 = hourly_2["weather"][0];
	int hourly_2_weather_0_id = hourly_2_weather_0["id"]; // 801
	const char* hourly_2_weather_0_main = hourly_2_weather_0["main"]; // "Clouds"
	const char* hourly_2_weather_0_description = hourly_2_weather_0["description"]; // "few clouds"
	const char* hourly_2_weather_0_icon = hourly_2_weather_0["icon"]; // "02d"

	int hourly_2_pop = hourly_2["pop"]; // 0

	JsonObject hourly_3 = hourly[3];
	long hourly_3_dt = hourly_3["dt"]; // 1646942400
	float hourly_3_temp = hourly_3["temp"]; // 2.35
	float hourly_3_feels_like = hourly_3["feels_like"]; // -0.66
	int hourly_3_pressure = hourly_3["pressure"]; // 1021
	int hourly_3_humidity = hourly_3["humidity"]; // 51
	int hourly_3_clouds = hourly_3["clouds"]; // 40
	int hourly_3_visibility = hourly_3["visibility"]; // 10000
	float hourly_3_wind_speed = hourly_3["wind_speed"]; // 2.98
	int hourly_3_wind_deg = hourly_3["wind_deg"]; // 275
	float hourly_3_wind_gust = hourly_3["wind_gust"]; // 4.75

	JsonObject hourly_3_weather_0 = hourly_3["weather"][0];
	int hourly_3_weather_0_id = hourly_3_weather_0["id"]; // 802
	const char* hourly_3_weather_0_main = hourly_3_weather_0["main"]; // "Clouds"
	const char* hourly_3_weather_0_description = hourly_3_weather_0["description"]; // "scattered clouds"
	const char* hourly_3_weather_0_icon = hourly_3_weather_0["icon"]; // "03d"

	int hourly_3_pop = hourly_3["pop"]; // 0

	JsonObject hourly_4 = hourly[4];
	long hourly_4_dt = hourly_4["dt"]; // 1646946000
	float hourly_4_temp = hourly_4["temp"]; // 2.29
	float hourly_4_feels_like = hourly_4["feels_like"]; // -0.32
	int hourly_4_pressure = hourly_4["pressure"]; // 1021
	int hourly_4_humidity = hourly_4["humidity"]; // 49
	int hourly_4_clouds = hourly_4["clouds"]; // 60
	int hourly_4_visibility = hourly_4["visibility"]; // 10000
	float hourly_4_wind_speed = hourly_4["wind_speed"]; // 2.51
	int hourly_4_wind_deg = hourly_4["wind_deg"]; // 276
	float hourly_4_wind_gust = hourly_4["wind_gust"]; // 3.95

	JsonObject hourly_4_weather_0 = hourly_4["weather"][0];
	int hourly_4_weather_0_id = hourly_4_weather_0["id"]; // 803
	const char* hourly_4_weather_0_main = hourly_4_weather_0["main"]; // "Clouds"
	const char* hourly_4_weather_0_description = hourly_4_weather_0["description"]; // "broken clouds"
	const char* hourly_4_weather_0_icon = hourly_4_weather_0["icon"]; // "04d"

	int hourly_4_pop = hourly_4["pop"]; // 0

	JsonObject hourly_5 = hourly[5];
	long hourly_5_dt = hourly_5["dt"]; // 1646949600
	float hourly_5_temp = hourly_5["temp"]; // 1.99
	float hourly_5_feels_like = hourly_5["feels_like"]; // -0.65
	int hourly_5_pressure = hourly_5["pressure"]; // 1021
	int hourly_5_humidity = hourly_5["humidity"]; // 49
	int hourly_5_clouds = hourly_5["clouds"]; // 79
	int hourly_5_visibility = hourly_5["visibility"]; // 10000
	float hourly_5_wind_speed = hourly_5["wind_speed"]; // 2.48
	int hourly_5_wind_deg = hourly_5["wind_deg"]; // 289
	float hourly_5_wind_gust = hourly_5["wind_gust"]; // 3.85

	JsonObject hourly_5_weather_0 = hourly_5["weather"][0];
	int hourly_5_weather_0_id = hourly_5_weather_0["id"]; // 803
	const char* hourly_5_weather_0_main = hourly_5_weather_0["main"]; // "Clouds"
	const char* hourly_5_weather_0_description = hourly_5_weather_0["description"]; // "broken clouds"
	const char* hourly_5_weather_0_icon = hourly_5_weather_0["icon"]; // "04d"

	int hourly_5_pop = hourly_5["pop"]; // 0

	JsonObject hourly_6 = hourly[6];
	long hourly_6_dt = hourly_6["dt"]; // 1646953200
	float hourly_6_temp = hourly_6["temp"]; // 1.14
	float hourly_6_feels_like = hourly_6["feels_like"]; // -1.54
	int hourly_6_pressure = hourly_6["pressure"]; // 1021
	int hourly_6_humidity = hourly_6["humidity"]; // 53
	int hourly_6_clouds = hourly_6["clouds"]; // 90
	int hourly_6_visibility = hourly_6["visibility"]; // 10000
	float hourly_6_wind_speed = hourly_6["wind_speed"]; // 2.37
	int hourly_6_wind_deg = hourly_6["wind_deg"]; // 311
	float hourly_6_wind_gust = hourly_6["wind_gust"]; // 4.37

	JsonObject hourly_6_weather_0 = hourly_6["weather"][0];
	int hourly_6_weather_0_id = hourly_6_weather_0["id"]; // 804
	const char* hourly_6_weather_0_main = hourly_6_weather_0["main"]; // "Clouds"
	const char* hourly_6_weather_0_description = hourly_6_weather_0["description"]; // "overcast clouds"
	const char* hourly_6_weather_0_icon = hourly_6_weather_0["icon"]; // "04d"

	int hourly_6_pop = hourly_6["pop"]; // 0

	JsonObject hourly_7 = hourly[7];
	long hourly_7_dt = hourly_7["dt"]; // 1646956800
	float hourly_7_temp = hourly_7["temp"]; // 0.31
	float hourly_7_feels_like = hourly_7["feels_like"]; // -3.06
	int hourly_7_pressure = hourly_7["pressure"]; // 1021
	int hourly_7_humidity = hourly_7["humidity"]; // 61
	int hourly_7_clouds = hourly_7["clouds"]; // 90
	int hourly_7_visibility = hourly_7["visibility"]; // 10000
	float hourly_7_wind_speed = hourly_7["wind_speed"]; // 2.92
	int hourly_7_wind_deg = hourly_7["wind_deg"]; // 342
	float hourly_7_wind_gust = hourly_7["wind_gust"]; // 5.02

	JsonObject hourly_7_weather_0 = hourly_7["weather"][0];
	int hourly_7_weather_0_id = hourly_7_weather_0["id"]; // 804
	const char* hourly_7_weather_0_main = hourly_7_weather_0["main"]; // "Clouds"
	const char* hourly_7_weather_0_description = hourly_7_weather_0["description"]; // "overcast clouds"
	const char* hourly_7_weather_0_icon = hourly_7_weather_0["icon"]; // "04n"

	int hourly_7_pop = hourly_7["pop"]; // 0

	JsonObject hourly_8 = hourly[8];
	long hourly_8_dt = hourly_8["dt"]; // 1646960400
	float hourly_8_temp = hourly_8["temp"]; // -0.95
	float hourly_8_feels_like = hourly_8["feels_like"]; // -5.11
	int hourly_8_pressure = hourly_8["pressure"]; // 1022
	int hourly_8_humidity = hourly_8["humidity"]; // 68
	int hourly_8_clouds = hourly_8["clouds"]; // 84
	int hourly_8_visibility = hourly_8["visibility"]; // 10000
	float hourly_8_wind_speed = hourly_8["wind_speed"]; // 3.55
	int hourly_8_wind_deg = hourly_8["wind_deg"]; // 356
	float hourly_8_wind_gust = hourly_8["wind_gust"]; // 4.89

	JsonObject hourly_8_weather_0 = hourly_8["weather"][0];
	int hourly_8_weather_0_id = hourly_8_weather_0["id"]; // 803
	const char* hourly_8_weather_0_main = hourly_8_weather_0["main"]; // "Clouds"
	const char* hourly_8_weather_0_description = hourly_8_weather_0["description"]; // "broken clouds"
	const char* hourly_8_weather_0_icon = hourly_8_weather_0["icon"]; // "04n"

	int hourly_8_pop = hourly_8["pop"]; // 0

	JsonObject hourly_9 = hourly[9];
	long hourly_9_dt = hourly_9["dt"]; // 1646964000
	float hourly_9_temp = hourly_9["temp"]; // -1.83
	float hourly_9_feels_like = hourly_9["feels_like"]; // -6.24
	int hourly_9_pressure = hourly_9["pressure"]; // 1022
	int hourly_9_humidity = hourly_9["humidity"]; // 69
	int hourly_9_clouds = hourly_9["clouds"]; // 92
	int hourly_9_visibility = hourly_9["visibility"]; // 10000
	float hourly_9_wind_speed = hourly_9["wind_speed"]; // 3.62
	int hourly_9_wind_deg = hourly_9["wind_deg"]; // 357
	float hourly_9_wind_gust = hourly_9["wind_gust"]; // 4.83

	JsonObject hourly_9_weather_0 = hourly_9["weather"][0];
	int hourly_9_weather_0_id = hourly_9_weather_0["id"]; // 804
	const char* hourly_9_weather_0_main = hourly_9_weather_0["main"]; // "Clouds"
	const char* hourly_9_weather_0_description = hourly_9_weather_0["description"]; // "overcast clouds"
	const char* hourly_9_weather_0_icon = hourly_9_weather_0["icon"]; // "04n"

	int hourly_9_pop = hourly_9["pop"]; // 0

	JsonObject hourly_10 = hourly[10];
	long hourly_10_dt = hourly_10["dt"]; // 1646967600
	float hourly_10_temp = hourly_10["temp"]; // -1.89
	float hourly_10_feels_like = hourly_10["feels_like"]; // -5.95
	int hourly_10_pressure = hourly_10["pressure"]; // 1023
	int hourly_10_humidity = hourly_10["humidity"]; // 65
	int hourly_10_clouds = hourly_10["clouds"]; // 95
	int hourly_10_visibility = hourly_10["visibility"]; // 10000
	float hourly_10_wind_speed = hourly_10["wind_speed"]; // 3.2
	int hourly_10_wind_deg = hourly_10["wind_deg"]; // 356
	float hourly_10_wind_gust = hourly_10["wind_gust"]; // 4.14

	JsonObject hourly_10_weather_0 = hourly_10["weather"][0];
	int hourly_10_weather_0_id = hourly_10_weather_0["id"]; // 804
	const char* hourly_10_weather_0_main = hourly_10_weather_0["main"]; // "Clouds"
	const char* hourly_10_weather_0_description = hourly_10_weather_0["description"]; // "overcast clouds"
	const char* hourly_10_weather_0_icon = hourly_10_weather_0["icon"]; // "04n"

	int hourly_10_pop = hourly_10["pop"]; // 0

	JsonObject hourly_11 = hourly[11];
	long hourly_11_dt = hourly_11["dt"]; // 1646971200
	float hourly_11_temp = hourly_11["temp"]; // -1.93
	float hourly_11_feels_like = hourly_11["feels_like"]; // -5.6
	int hourly_11_pressure = hourly_11["pressure"]; // 1022
	int hourly_11_humidity = hourly_11["humidity"]; // 65
	int hourly_11_clouds = hourly_11["clouds"]; // 96
	int hourly_11_visibility = hourly_11["visibility"]; // 10000
	float hourly_11_wind_speed = hourly_11["wind_speed"]; // 2.78
	int hourly_11_wind_deg = hourly_11["wind_deg"]; // 352
	float hourly_11_wind_gust = hourly_11["wind_gust"]; // 3.59

	JsonObject hourly_11_weather_0 = hourly_11["weather"][0];
	int hourly_11_weather_0_id = hourly_11_weather_0["id"]; // 804
	const char* hourly_11_weather_0_main = hourly_11_weather_0["main"]; // "Clouds"
	const char* hourly_11_weather_0_description = hourly_11_weather_0["description"]; // "overcast clouds"
	const char* hourly_11_weather_0_icon = hourly_11_weather_0["icon"]; // "04n"

	int hourly_11_pop = hourly_11["pop"]; // 0

	JsonObject hourly_12 = hourly[12];
	long hourly_12_dt = hourly_12["dt"]; // 1646974800
	float hourly_12_temp = hourly_12["temp"]; // -2.24
	float hourly_12_feels_like = hourly_12["feels_like"]; // -5.89
	int hourly_12_pressure = hourly_12["pressure"]; // 1022
	int hourly_12_humidity = hourly_12["humidity"]; // 72
	int hourly_12_clouds = hourly_12["clouds"]; // 97
	int hourly_12_visibility = hourly_12["visibility"]; // 10000
	float hourly_12_wind_speed = hourly_12["wind_speed"]; // 2.7
	int hourly_12_wind_deg = hourly_12["wind_deg"]; // 353
	float hourly_12_wind_gust = hourly_12["wind_gust"]; // 3.41

	JsonObject hourly_12_weather_0 = hourly_12["weather"][0];
	int hourly_12_weather_0_id = hourly_12_weather_0["id"]; // 804
	const char* hourly_12_weather_0_main = hourly_12_weather_0["main"]; // "Clouds"
	const char* hourly_12_weather_0_description = hourly_12_weather_0["description"]; // "overcast clouds"
	const char* hourly_12_weather_0_icon = hourly_12_weather_0["icon"]; // "04n"

	float hourly_12_pop = hourly_12["pop"]; // 0.03

	JsonObject hourly_13 = hourly[13];
	long hourly_13_dt = hourly_13["dt"]; // 1646978400
	float hourly_13_temp = hourly_13["temp"]; // -2.48
	float hourly_13_feels_like = hourly_13["feels_like"]; // -6.25
	int hourly_13_pressure = hourly_13["pressure"]; // 1021
	int hourly_13_humidity = hourly_13["humidity"]; // 78
	int hourly_13_clouds = hourly_13["clouds"]; // 97
	int hourly_13_visibility = hourly_13["visibility"]; // 8986
	float hourly_13_wind_speed = hourly_13["wind_speed"]; // 2.77
	int hourly_13_wind_deg = hourly_13["wind_deg"]; // 4
	float hourly_13_wind_gust = hourly_13["wind_gust"]; // 3.55

	JsonObject hourly_13_weather_0 = hourly_13["weather"][0];
	int hourly_13_weather_0_id = hourly_13_weather_0["id"]; // 804
	const char* hourly_13_weather_0_main = hourly_13_weather_0["main"]; // "Clouds"
	const char* hourly_13_weather_0_description = hourly_13_weather_0["description"]; // "overcast clouds"
	const char* hourly_13_weather_0_icon = hourly_13_weather_0["icon"]; // "04n"

	float hourly_13_pop = hourly_13["pop"]; // 0.11

	JsonObject hourly_14 = hourly[14];
	long hourly_14_dt = hourly_14["dt"]; // 1646982000
	float hourly_14_temp = hourly_14["temp"]; // -2.52
	float hourly_14_feels_like = hourly_14["feels_like"]; // -5.52
	int hourly_14_pressure = hourly_14["pressure"]; // 1021
	int hourly_14_humidity = hourly_14["humidity"]; // 77
	int hourly_14_clouds = hourly_14["clouds"]; // 100
	int hourly_14_visibility = hourly_14["visibility"]; // 10000
	float hourly_14_wind_speed = hourly_14["wind_speed"]; // 2.1
	int hourly_14_wind_deg = hourly_14["wind_deg"]; // 11
	float hourly_14_wind_gust = hourly_14["wind_gust"]; // 2.41

	JsonObject hourly_14_weather_0 = hourly_14["weather"][0];
	int hourly_14_weather_0_id = hourly_14_weather_0["id"]; // 804
	const char* hourly_14_weather_0_main = hourly_14_weather_0["main"]; // "Clouds"
	const char* hourly_14_weather_0_description = hourly_14_weather_0["description"]; // "overcast clouds"
	const char* hourly_14_weather_0_icon = hourly_14_weather_0["icon"]; // "04n"

	float hourly_14_pop = hourly_14["pop"]; // 0.33

	JsonObject hourly_15 = hourly[15];
	long hourly_15_dt = hourly_15["dt"]; // 1646985600
	float hourly_15_temp = hourly_15["temp"]; // -2.48
	float hourly_15_feels_like = hourly_15["feels_like"]; // -4.88
	int hourly_15_pressure = hourly_15["pressure"]; // 1020
	int hourly_15_humidity = hourly_15["humidity"]; // 76
	int hourly_15_clouds = hourly_15["clouds"]; // 100
	int hourly_15_visibility = hourly_15["visibility"]; // 10000
	float hourly_15_wind_speed = hourly_15["wind_speed"]; // 1.68
	int hourly_15_wind_deg = hourly_15["wind_deg"]; // 32
	float hourly_15_wind_gust = hourly_15["wind_gust"]; // 1.48

	JsonObject hourly_15_weather_0 = hourly_15["weather"][0];
	int hourly_15_weather_0_id = hourly_15_weather_0["id"]; // 804
	const char* hourly_15_weather_0_main = hourly_15_weather_0["main"]; // "Clouds"
	const char* hourly_15_weather_0_description = hourly_15_weather_0["description"]; // "overcast clouds"
	const char* hourly_15_weather_0_icon = hourly_15_weather_0["icon"]; // "04n"

	float hourly_15_pop = hourly_15["pop"]; // 0.33

	JsonObject hourly_16 = hourly[16];
	long hourly_16_dt = hourly_16["dt"]; // 1646989200
	float hourly_16_temp = hourly_16["temp"]; // -2.42
	float hourly_16_feels_like = hourly_16["feels_like"]; // -4.39
	int hourly_16_pressure = hourly_16["pressure"]; // 1020
	int hourly_16_humidity = hourly_16["humidity"]; // 76
	int hourly_16_clouds = hourly_16["clouds"]; // 100
	int hourly_16_visibility = hourly_16["visibility"]; // 10000
	float hourly_16_wind_speed = hourly_16["wind_speed"]; // 1.43
	int hourly_16_wind_deg = hourly_16["wind_deg"]; // 42
	float hourly_16_wind_gust = hourly_16["wind_gust"]; // 1.04

	JsonObject hourly_16_weather_0 = hourly_16["weather"][0];
	int hourly_16_weather_0_id = hourly_16_weather_0["id"]; // 804
	const char* hourly_16_weather_0_main = hourly_16_weather_0["main"]; // "Clouds"
	const char* hourly_16_weather_0_description = hourly_16_weather_0["description"]; // "overcast clouds"
	const char* hourly_16_weather_0_icon = hourly_16_weather_0["icon"]; // "04n"

	float hourly_16_pop = hourly_16["pop"]; // 0.33

	JsonObject hourly_17 = hourly[17];
	long hourly_17_dt = hourly_17["dt"]; // 1646992800
	float hourly_17_temp = hourly_17["temp"]; // -2.56
	float hourly_17_feels_like = hourly_17["feels_like"]; // -4.76
	int hourly_17_pressure = hourly_17["pressure"]; // 1020
	int hourly_17_humidity = hourly_17["humidity"]; // 82
	int hourly_17_clouds = hourly_17["clouds"]; // 100
	int hourly_17_visibility = hourly_17["visibility"]; // 6133
	float hourly_17_wind_speed = hourly_17["wind_speed"]; // 1.55
	int hourly_17_wind_deg = hourly_17["wind_deg"]; // 64
	float hourly_17_wind_gust = hourly_17["wind_gust"]; // 1.5

	JsonObject hourly_17_weather_0 = hourly_17["weather"][0];
	int hourly_17_weather_0_id = hourly_17_weather_0["id"]; // 600
	const char* hourly_17_weather_0_main = hourly_17_weather_0["main"]; // "Snow"
	const char* hourly_17_weather_0_description = hourly_17_weather_0["description"]; // "light snow"
	const char* hourly_17_weather_0_icon = hourly_17_weather_0["icon"]; // "13n"

	float hourly_17_pop = hourly_17["pop"]; // 0.4

	float hourly_17_snow_1h = hourly_17["snow"]["1h"]; // 0.1

	JsonObject hourly_18 = hourly[18];
	long hourly_18_dt = hourly_18["dt"]; // 1646996400
	float hourly_18_temp = hourly_18["temp"]; // -2.7
	float hourly_18_feels_like = hourly_18["feels_like"]; // -5.53
	int hourly_18_pressure = hourly_18["pressure"]; // 1020
	int hourly_18_humidity = hourly_18["humidity"]; // 86
	int hourly_18_clouds = hourly_18["clouds"]; // 100
	int hourly_18_visibility = hourly_18["visibility"]; // 1743
	float hourly_18_wind_speed = hourly_18["wind_speed"]; // 1.95
	int hourly_18_wind_deg = hourly_18["wind_deg"]; // 84
	float hourly_18_wind_gust = hourly_18["wind_gust"]; // 2.25

	JsonObject hourly_18_weather_0 = hourly_18["weather"][0];
	int hourly_18_weather_0_id = hourly_18_weather_0["id"]; // 600
	const char* hourly_18_weather_0_main = hourly_18_weather_0["main"]; // "Snow"
	const char* hourly_18_weather_0_description = hourly_18_weather_0["description"]; // "light snow"
	const char* hourly_18_weather_0_icon = hourly_18_weather_0["icon"]; // "13n"

	float hourly_18_pop = hourly_18["pop"]; // 0.44

	float hourly_18_snow_1h = hourly_18["snow"]["1h"]; // 0.12

	JsonObject hourly_19 = hourly[19];
	long hourly_19_dt = hourly_19["dt"]; // 1647000000
	float hourly_19_temp = hourly_19["temp"]; // -2.65
	float hourly_19_feels_like = hourly_19["feels_like"]; // -6.18
	int hourly_19_pressure = hourly_19["pressure"]; // 1020
	int hourly_19_humidity = hourly_19["humidity"]; // 89
	int hourly_19_clouds = hourly_19["clouds"]; // 100
	int hourly_19_visibility = hourly_19["visibility"]; // 377
	float hourly_19_wind_speed = hourly_19["wind_speed"]; // 2.52
	int hourly_19_wind_deg = hourly_19["wind_deg"]; // 104
	float hourly_19_wind_gust = hourly_19["wind_gust"]; // 3.46

	JsonObject hourly_19_weather_0 = hourly_19["weather"][0];
	int hourly_19_weather_0_id = hourly_19_weather_0["id"]; // 600
	const char* hourly_19_weather_0_main = hourly_19_weather_0["main"]; // "Snow"
	const char* hourly_19_weather_0_description = hourly_19_weather_0["description"]; // "light snow"
	const char* hourly_19_weather_0_icon = hourly_19_weather_0["icon"]; // "13d"

	float hourly_19_pop = hourly_19["pop"]; // 0.52

	float hourly_19_snow_1h = hourly_19["snow"]["1h"]; // 0.19

	JsonObject hourly_20 = hourly[20];
	long hourly_20_dt = hourly_20["dt"]; // 1647003600
	float hourly_20_temp = hourly_20["temp"]; // -2.26
	float hourly_20_feels_like = hourly_20["feels_like"]; // -6.32
	int hourly_20_pressure = hourly_20["pressure"]; // 1020
	int hourly_20_humidity = hourly_20["humidity"]; // 84
	int hourly_20_clouds = hourly_20["clouds"]; // 100
	int hourly_20_visibility = hourly_20["visibility"]; // 3027
	float hourly_20_wind_speed = hourly_20["wind_speed"]; // 3.11
	int hourly_20_wind_deg = hourly_20["wind_deg"]; // 112
	float hourly_20_wind_gust = hourly_20["wind_gust"]; // 4.27

	JsonObject hourly_20_weather_0 = hourly_20["weather"][0];
	int hourly_20_weather_0_id = hourly_20_weather_0["id"]; // 600
	const char* hourly_20_weather_0_main = hourly_20_weather_0["main"]; // "Snow"
	const char* hourly_20_weather_0_description = hourly_20_weather_0["description"]; // "light snow"
	const char* hourly_20_weather_0_icon = hourly_20_weather_0["icon"]; // "13d"

	float hourly_20_pop = hourly_20["pop"]; // 0.37

	float hourly_20_snow_1h = hourly_20["snow"]["1h"]; // 0.13

	JsonObject hourly_21 = hourly[21];
	long hourly_21_dt = hourly_21["dt"]; // 1647007200
	float hourly_21_temp = hourly_21["temp"]; // -1.71
	float hourly_21_feels_like = hourly_21["feels_like"]; // -5.92
	int hourly_21_pressure = hourly_21["pressure"]; // 1019
	int hourly_21_humidity = hourly_21["humidity"]; // 81
	int hourly_21_clouds = hourly_21["clouds"]; // 100
	int hourly_21_visibility = hourly_21["visibility"]; // 10000
	float hourly_21_wind_speed = hourly_21["wind_speed"]; // 3.41
	int hourly_21_wind_deg = hourly_21["wind_deg"]; // 115
	float hourly_21_wind_gust = hourly_21["wind_gust"]; // 4.61

	JsonObject hourly_21_weather_0 = hourly_21["weather"][0];
	int hourly_21_weather_0_id = hourly_21_weather_0["id"]; // 804
	const char* hourly_21_weather_0_main = hourly_21_weather_0["main"]; // "Clouds"
	const char* hourly_21_weather_0_description = hourly_21_weather_0["description"]; // "overcast clouds"
	const char* hourly_21_weather_0_icon = hourly_21_weather_0["icon"]; // "04d"

	float hourly_21_pop = hourly_21["pop"]; // 0.21

	JsonObject hourly_22 = hourly[22];
	long hourly_22_dt = hourly_22["dt"]; // 1647010800
	float hourly_22_temp = hourly_22["temp"]; // -1.13
	float hourly_22_feels_like = hourly_22["feels_like"]; // -5.18
	int hourly_22_pressure = hourly_22["pressure"]; // 1018
	int hourly_22_humidity = hourly_22["humidity"]; // 79
	int hourly_22_clouds = hourly_22["clouds"]; // 100
	int hourly_22_visibility = hourly_22["visibility"]; // 10000
	float hourly_22_wind_speed = hourly_22["wind_speed"]; // 3.37
	int hourly_22_wind_deg = hourly_22["wind_deg"]; // 120
	float hourly_22_wind_gust = hourly_22["wind_gust"]; // 4.52

	JsonObject hourly_22_weather_0 = hourly_22["weather"][0];
	int hourly_22_weather_0_id = hourly_22_weather_0["id"]; // 804
	const char* hourly_22_weather_0_main = hourly_22_weather_0["main"]; // "Clouds"
	const char* hourly_22_weather_0_description = hourly_22_weather_0["description"]; // "overcast clouds"
	const char* hourly_22_weather_0_icon = hourly_22_weather_0["icon"]; // "04d"

	float hourly_22_pop = hourly_22["pop"]; // 0.11

	JsonObject hourly_23 = hourly[23];
	long hourly_23_dt = hourly_23["dt"]; // 1647014400
	float hourly_23_temp = hourly_23["temp"]; // -0.81
	float hourly_23_feels_like = hourly_23["feels_like"]; // -4.56
	int hourly_23_pressure = hourly_23["pressure"]; // 1018
	int hourly_23_humidity = hourly_23["humidity"]; // 81
	int hourly_23_clouds = hourly_23["clouds"]; // 100
	int hourly_23_visibility = hourly_23["visibility"]; // 7870
	float hourly_23_wind_speed = hourly_23["wind_speed"]; // 3.1
	int hourly_23_wind_deg = hourly_23["wind_deg"]; // 129
	float hourly_23_wind_gust = hourly_23["wind_gust"]; // 4.44

	JsonObject hourly_23_weather_0 = hourly_23["weather"][0];
	int hourly_23_weather_0_id = hourly_23_weather_0["id"]; // 804
	const char* hourly_23_weather_0_main = hourly_23_weather_0["main"]; // "Clouds"
	const char* hourly_23_weather_0_description = hourly_23_weather_0["description"]; // "overcast clouds"
	const char* hourly_23_weather_0_icon = hourly_23_weather_0["icon"]; // "04d"

	float hourly_23_pop = hourly_23["pop"]; // 0.07
}

