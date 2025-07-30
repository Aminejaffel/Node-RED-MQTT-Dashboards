#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

// --- Pin Definition ---
const int DHT_PIN = 9;

// --- Sensor Object ---
DHTesp dhtSensor;

// --- WiFi and MQTT Credentials ---
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

// --- MQTT Client Setup ---
WiFiClient espClient;
PubSubClient client(espClient);

// --- Timing and Data Variables ---
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
float temp = 0;
float hum = 0;
int value = 0;

// --- Function: Connect to WiFi ---
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected ✅");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// --- MQTT Message Callback ---
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Example: Control built-in LED based on received message
  if ((char)payload[0] == '1') {
    digitalWrite(2, LOW);   // Turn LED on (active low)
  } else {
    digitalWrite(2, HIGH);  // Turn LED off
  }
}

// --- MQTT Reconnection Logic ---
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      client.publish("Weather/mqtt", "iotfrontier");
      client.subscribe("Weather/mqtt");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// --- Arduino Setup Function ---
void setup() {
  pinMode(2, OUTPUT);     // Initialize the built-in LED pin as output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

// --- Main Loop Function ---
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    TempAndHumidity data = dhtSensor.getTempAndHumidity();

    String temp = String(data.temperature, 2);
    Serial.print("Temperature: ");
    Serial.println(temp);
    client.publish("Weather/Temperature", temp.c_str());
    
    String hum = String(data.humidity, 1);
    Serial.print("Humidity: ");
    Serial.println(hum);
    client.publish("Weather/Humidity", hum.c_str());
  }
}
