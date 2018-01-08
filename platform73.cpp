/*
  Platform73.h - Library communicating with Platform73.
  Created by Harut Martirosyan 2018.
*/

#include "platform73.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

Platform73::Platform73(String projectId)
{
  _projectId = projectId;
}

void Platform73::connect()
{
  _espClient = WiFiClient();
  _client = PubSubClient(_espClient);
  _setup_wifi();
  _setup_mqtt();
}

void Platform73::event(const char * name)
{
  char msg[119];
  snprintf (msg, 100, "{\"air_temp\":%u, \"air_hum\":%u, \"light\":%u, \"soil_temp\":%u, \"soil_hum1\":%u, \"soil_hum2\":%u}", 1, 1, 1, 1, 1, 1);
  this->_client.publish("outTopic", msg);
  Serial.println(msg);
}

void Platform73::metric(const char * name, const int value)
{
  char msg[119];
  char topic[100];
  char topicPrefix[] = "/1/devices/5a4e4725d4d1e74ffccd7dd9/metrics/";
  sprintf(topic,"%s%s",topicPrefix,name);
  snprintf (msg, 100, "{\"name\":\"%s\", \"value\":%u}", name, value);
  _client.publish(topic, msg);
  Serial.println(msg);
}

void Platform73::_setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(_ssid);
  WiFi.begin(_ssid, _password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void Platform73::_setup_mqtt() {
  _client.setServer(_mqtt_server, 1883);
  // Loop until we're reconnected
  while (!_client.connected()) {
    // Create a random client ID
    String clientId = "platform73client-";
    clientId += String(random(0xffff), HEX);
    Serial.println(_mqtt_server);
    if (_client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      delay(5000);
    }
  }
  _client.loop();
}
