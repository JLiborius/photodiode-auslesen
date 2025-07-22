#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define USE_MQTT
#define MAX_VOLTAGE_PHOTODIODE 4.0
#define INPUT_PIN 34
#define SAMPLE_TIME 3000 // Every X ms one sample

#ifdef USE_MQTT
const char* ssid = "gigacube-1C0F";
const char* password = "#2023agile36b!";
const char* mqtt_server = "192.168.0.6";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void connectToWifi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi");
    ESP.restart();
  }

  client.setServer(mqtt_server, mqtt_port);
}

void reconnect() {
  unsigned long startAttemptTime = millis();
  while (!client.connected() && millis() - startAttemptTime < 20000) {
    Serial.print("Connecting to MQTT...");
    String clientId = "ESP32_Photodiode_Malte";
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 0.5 seconds");
      delay(500);
    }
  }

  if (!client.connected()) {
    Serial.println("MQTT connection failed, restarting...");
    delay(100);
    ESP.restart();
  }
}
#endif

float readVoltage(int input_pin){
  int sensorValue = analogRead(input_pin);
  float voltage = sensorValue * (MAX_VOLTAGE_PHOTODIODE / 4095.0);  // Convert ADC to voltage (12-bit)
  return voltage;
}

unsigned long startTime;

void setup() {
  Serial.begin(115200);
  delay(500);
  #ifdef USE_MQTT
  connectToWifi();
  #endif
  startTime = millis();
}

void loop() {
  #ifdef USE_MQTT
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    connectToWifi();
  }
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  #endif

  unsigned long currentTime = millis() - startTime;
  float voltage = readVoltage(INPUT_PIN);

  Serial.print(currentTime);
  Serial.print(",");
  Serial.println(voltage);

  #ifdef USE_MQTT
  StaticJsonDocument<200> doc;
  doc["Voltage_Photodiode_Malte"] = voltage
  String output; 
  serializeJson(doc, output);
  client.publish("lab/petzvalstrasse/sensor/photodiode_malte", output.c_str());
  #endif

  delay(SAMPLE_TIME);
}
