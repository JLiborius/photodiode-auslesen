# ESP32 Photodiode Data Logger with MQTT and Serial Output

This project measures the voltage from a photodiode using an ESP32, sends the readings to an MQTT broker, and outputs the data over serial. Use the included Python script to save the data as a CSV.

---

## Features

- Connects ESP32 to WiFi and MQTT for remote data sharing
- Reads photodiode voltage via ADC
- Publishes voltage readings in JSON format over MQTT
- Prints timestamped voltage over USB serial
- Python script for easy serial-to-CSV data logging

---

## Hardware Requirements

- ESP32 development board
- Photodiode sensor (up to 4V output)
- Computer with Python 3 (and [pyserial](https://pypi.org/project/pyserial/))
- WiFi network

---

## Circuit

Connect the photodiode output to ESP32 analog input pin **GPIO34**.
You can connect multiple sensors to the ESP32, but you have to define the Pins in the ESP Code and change the code to send the sensordata to serial and over MQTT.
(Adjust in the code if you use another analog pin.)

---

## ESP32 Code

The firmware must:
- Connect to your WiFi and MQTT broker.
- Measure voltage from the specified analog pin every sample interval.
- Send voltage readings:
    - **Over serial** as `time_ms,voltage`
    - **Over MQTT** as JSON to topic `lab/petzvalstrasse/sensor/photodiode_malte`

To build:  
- Use Arduino IDE with the [PubSubClient](https://github.com/knolleary/pubsubclient) and [ArduinoJson](https://arduinojson.org/) libraries.
- Flash the code onto your ESP32.

---
