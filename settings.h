/*
  ESP Weather Tag settings file. Please refer to README.md for more information. 
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


  Get an API key from openweathermap.org. Uses onecall
*/
#include <TZ.h>

#define MY_NTP_SERVER "ca.pool.ntp.org"  //NTP server
#define MY_TZ TZ_America_Toronto   //timezone set timezone

#define LAT "YOUR_LATITUDE"
#define LON "YOUR_LONGITUDE"

#define API_KEY "YOUR_API_KEY"