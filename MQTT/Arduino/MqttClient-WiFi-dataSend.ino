#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

char* ssid[] = SECRET_SSID;
char* pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttCLient(wifiClient);

const char broker[] = "test.mosquitto.org";
const char topic1[] = "sensors/1/temp";
const char topic2[] = "sensors/1/humid";
const char topic3[] = "";
int port = 1883;

const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ;
    }

    Serial.print("Attempting to connect to WPA SSID ")
    Serial.println(ssid)

    while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
        Serial.print(".");
        delay(5000);
    }

    Serial.println("You're connected to the network");
    Serial.println();

    Serial.print("Attempting to connect to the MQTT broker: ");
    Serial.println(broker);

    if (!mqtt.Client.connect(broker, port)) {
        Serial.print("MQTT conn failed with error: ");
        Serial.println(mqttClient.connectError());

        while(1);
    }

    Serial.println("Connected to mqtt broker");
    Serial.println();
}

void loop() {
    mqttClient.poll();

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        int Rvalue = analogRead(A0);
    
        Serial.println(topic1);
        Serial.println(Rvalue);

        mqttClient.beginMessage(topic1);
        mqttClient.print(Rvalue);
        mqttClient.endMessage();

        Serial.println();
    }

}


