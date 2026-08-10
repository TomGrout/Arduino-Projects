#!python3

import paho.mqtt.client as mqtt 
import time

broker = "test.mosquitto.org"
port = 1883

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        client.connected_flag = True
        print("Connected to MQTT Broker!")
        
    else:
        print("Failed to connect, return code %d\n", rc)
        
        
mqtt.Client.connected_flag = False
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2, "PythonClient")
client.on_connect = on_connect
client.loop_start()
print ("Connecting to broker ", broker)
client.connect(broker, port)

while client.connected_flag:
    print("In wait loop")
    time.sleep(1)
    
print ("In main loop")
client.loop_stop()
client.disconnect()    