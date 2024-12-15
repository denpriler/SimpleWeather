#pragma once

#include <string>
#include <curl/curl.h>
#include <iostream>

class WeatherLocation
{
private:
	// CURL variables
	std::string curl_query;
	std::string curl_buffer;
	CURL* curl;
	CURLcode curl_res;

protected:
	float latitude;
	float longitude;

public:
	WeatherLocation(float latitude, float longitude);
	~WeatherLocation();

	void GetCurrentWeather();
	void PrintWeatherString();
};

