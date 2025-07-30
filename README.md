# IoT Temperature & Humidity Monitoring with Node-RED and ESP32

This project implements a real-time environmental monitoring system using an ESP32 microcontroller and a DHT22 sensor. Sensor data for temperature and humidity are sent over MQTT to a Node-RED server, which processes and visualizes the data on a live dashboard.

## Features

- Real-time acquisition of temperature and humidity data
- MQTT communication via HiveMQ broker
- Interactive dashboard with gauges and charts built using Node-RED Dashboard
- Clean, modular Node-RED flows for data handling and visualization

## Technologies Used

- ESP32 (Arduino framework)  
- DHT22 sensor  
- MQTT (HiveMQ)  
- Node-RED (including Dashboard nodes)  

## Getting Started

### Hardware Setup

1. Connect the DHT22 sensor data pin to GPIO 9 (or your preferred pin) on the ESP32.
2. Connect sensor power and ground pins appropriately.

### Software Setup

1. Upload the ESP32 Arduino code to your board.  
2. Update WiFi SSID and password in the code.  
3. Set the MQTT broker address (default: `broker.hivemq.com`).  
4. Run a Node-RED instance and import the provided Node-RED flow JSON file.  
5. Install required Node-RED nodes such as MQTT and Dashboard nodes.

### Running the Project

- Power on the ESP32 device.
- Connect to the same WiFi network as the MQTT broker.
- Access the Node-RED dashboard via your browser 
- Monitor live temperature and humidity data, visualized on gauges and charts.



