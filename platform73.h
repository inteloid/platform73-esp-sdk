/*
  Platform73.h - Library communicating with Platform73.
  Created by Harut Martirosyan 2018.
*/
#ifndef Platform73_h
#define Platform73_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class Platform73
{
  public:
    Platform73(String projectId);
    void connect();
    void event(const char * name);
    void metric(const char * name, const int value);
  private:
    void _setup_wifi();
    void _setup_mqtt();
    String _projectId;
    PubSubClient _client;
    WiFiClient _espClient;
    const char* _ssid = "WIFI_SSID";
    const char* _password = "WIFI_PASSWORD";
    const char* _mqtt_server = "35.227.96.112";
};

#endif
