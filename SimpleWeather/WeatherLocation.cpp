#include "WeatherLocation.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

WeatherLocation::WeatherLocation(float latitude, float longitude)
	: latitude(latitude), longitude(longitude), curl_res(CURLE_OK)
{
    this->curl = curl_easy_init();
    _ASSERT(this->curl);

    this->curl_query = "https://api.open-meteo.com/v1/forecast?latitude=";
    this->curl_query.append(std::to_string(this->latitude));
    this->curl_query.append("&longitude=");
    this->curl_query.append(std::to_string(this->longitude));
    this->curl_query.append("&current=temperature_2m,weather_code,wind_speed_10m");

    curl_easy_setopt(this->curl, CURLOPT_URL, this->curl_query.c_str());
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &this->curl_buffer);
}

WeatherLocation::~WeatherLocation()
{
    curl_easy_cleanup(this->curl);
}

void WeatherLocation::GetCurrentWeather()
{    
    this->curl_res = curl_easy_perform(this->curl);
}

void WeatherLocation::PrintWeatherString()
{
    if (this->curl_res == CURLE_OK) {
        std::cout << this->curl_buffer << std::endl;
    }
    else {
        std::cout << "cURL result: " << this->curl_res << std::endl;
    }
}
