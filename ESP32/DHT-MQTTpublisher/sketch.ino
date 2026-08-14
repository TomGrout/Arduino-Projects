#include "arduino_secrets.h"
#include "DHTesp.h"
#include <WiFi.h>
#include <PubSubClient.h>

// set DHT
DHTesp dhtSensor;
TempAndHumidity data;
const int DHT_PIN = 15;

// set MQTT
const char* broker = "broker.emqx.io";
const int port = 1885; 
const char* topic_temp = "esp32/temperature";
const char* topic_humid = "esp32/humidity";

WiFiClient espWifiClient;
PubSubClient mqttclient(espWifiClient);


void setup() {
    Serial.begin(115200);

    dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

    // WiFi conn
    WiFi.begin(WIFI_SSID, WIFI_PASS)

    while(WiFi.status != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting...");
    }

    // mqtt conn
    mqttclient.setServer(MQTT_UNAME, MQTT_PASS);
    mqttclient.setCallback(callback);

    while (mqttclient.connected()) {
        String clientId = "esp32-client-";
        clientId += String(123);
        //clientId += String(WiFi.macAddress());

        //Serial.printf("The client %s connects to the public MQTT broker\n", clientId.c_str());

        if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public EMQX broker connected");
        }
        else {
            Serial.println("Public EMQX broker connected");
        }

    }

}

void loop() {
    data = dhtSensor.getTempAndHumidity();
    Serial.println("Humidity " + String(data.humidity, 1));
    Serial.println("Temperature " +String(data.temperature, 2));
    Serial.println("-----------");
    delay(1000);
}

void publish_data(int topic, char* message[]) {
    mqttclient.publish(topic, message);

}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}