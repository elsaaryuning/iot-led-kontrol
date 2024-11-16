# services/mqtt_service.py

import paho.mqtt.client as mqtt
from config.settings import MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASSWORD, MQTT_TOPIC_LED

# Inisialisasi client MQTT
client = mqtt.Client()
client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
client.connect(MQTT_SERVER, MQTT_PORT)

def control_led(state):
    message = "ON" if state else "OFF"
    client.publish(MQTT_TOPIC_LED, message)
    print(f"Sent message: {message} to topic: {MQTT_TOPIC_LED}")

