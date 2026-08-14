import paho.mqtt.client as mqtt
import json

mqtt_broker = "mqtt.cetools.org"
mqtt_port = 1844
mqtt_uname = "x"
mqtt_pass = "x"

def on_connect (client, flags, rc):
    if rc == 0: 
        print("Connected to MQTT on port " + str(mqtt_port))
        
    else:
        print("failed to connect (error: " + str(rc) + ")")
        
def publish_message (broker, port, topic, message):
    published = False
    
    client = mqtt.CLient()
    client.username_pw_set(mqtt_uname, mqtt_pass)
    client.connect(mqtt_broker, mqtt_port, 60)
    client.on_connect = on_connect
    
    client.connect(broker, port)
    
    payload_json = json.dumps(message)
    
    if (client.publish(topic, payload_json)):
        published = True
        
    client.disconnect()    
    
    return published


if __name__ == "main":
    
    topic = "test/light/1/pixel"
    payload = {"pixelId": 5, "R": 26, "G": 100, "B": 128, "W": 0}
    
    publish_message(mqtt_broker, mqtt_port, topic, payload)