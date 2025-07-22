# ESP32 Photodiode Data Logger with MQTT and Serial Output

This project measures the voltage from a photodiode using an ESP32, sends the readings to an MQTT broker, and outputs the data over serial. Use the included Python script to save the data as a CSV. ESP has to be connected via USB to the PC running the Python script to creat the CSV!

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
- WiFi network (only used for Grafana dashboard)

---

## Circuit

Connect the photodiode output to ESP32 analog input pin **GPIO34**.
You can connect multiple sensors to the ESP32, but you have to define the Pins in the ESP Code and change the code to send the sensordata to serial and over MQTT.
(Adjust in the code if you use another analog pin.)

---

## ESP32 Code

- Connect to your WiFi and MQTT broker.
- Measure voltage from the specified analog pin every sample interval.
- Send voltage readings:
    - **Over serial** as `time_ms,voltage`
    - **Over MQTT** as JSON to topic `lab/petzvalstrasse/sensor/photodiode_malte`

To build:  
- Use Arduino IDE with the [PubSubClient](https://github.com/knolleary/pubsubclient) and [ArduinoJson](https://arduinojson.org/) libraries.
- Flash the code onto your ESP32.

---

## Example Data

### CSV/Serial Output
```cmd
`time_ms,voltage`
`1000, 1.23`
`4000, 1.33`
...
```

### MQTT JSON Payload
`{"Voltage_Photodiode_Malte": 1.31}`
(MQTT topic: `lab/petzvalstrasse/sensor/photodiode_malte`)

---

# Serial Data Logger to CSV

This Python script reads data from a serial port, displays it in real-time, and saves it into a CSV file.

---

## Features

- Lists available serial ports for easy device selection
- Real-time data display while logging
- Saves data as CSV with headers (`time_ms,voltage`)
- Graceful termination with `Ctrl+C`

---

## Usage

### 1. Requirements
- use the .exe or install requirement when you want to run the .py. both is possible!
- Python 3.x
- [`pyserial`](https://pypi.org/project/pyserial/)
- the packages used for this script are listed in `requirements.txt`

Install requirements with:

```sh
pip install -r requirements.txt
```

### 2. Running the Script
1. Connect your microcontroller/device to your computer via USB.
2. Run the script: `python serial_logger.py` or run the .exe in dst folder.
3. Choose the correct port (e.g., COM4 on Windows or /dev/ttyUSB0 on Linux/macOS) when prompted.
4. Enter a file name for the CSV output.
5. Logging will begin. Press Ctrl+C to stop and close the log safely.

```cmd
Detected ports:
COM4 USB Serial Device
Choose Port: COM4
Name of the csv file: session1
Logging data... Press Ctrl+C to stop.
1001,1.27
4001,1.31
7034,1.34
...
Finished logging.
```