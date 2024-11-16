#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "AFINDO_ATAS";
const char* password = "silahkankonek";
const char* mqtt_server = "202.157.186.97";
const int ledPin = 2;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    String clientId = "ESP32_" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), "pablo", "costa")) {
      Serial.println("Connected to MQTT Broker with clientId: " + clientId);
      client.subscribe("iot/led/control");
    } else {
      delay(2000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)message[i];
  }

  Serial.print("Message arrived: ");
  Serial.println(msg);

  if (msg == "ON") {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED is ON");
  } else if (msg == "OFF") {
    digitalWrite(ledPin, LOW);
    Serial.println("LED is OFF");
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
  Serial.println("WiFi disconnected, reconnecting...");
  WiFi.begin(ssid, password);
  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void reconnect() {
  // Coba terhubung kembali ke broker MQTT
  while (!client.connected()) {
    Serial.println("Reconnecting to MQTT...");
    String clientId = "ESP32_" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), "pablo", "costa")) {
      Serial.println("Connected to MQTT Broker with clientId: " + clientId);
      client.subscribe("iot/led/control");
    } else {
      delay(2000);
    }
  }
}

