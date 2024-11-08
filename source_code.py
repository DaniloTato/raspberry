#Importing Dependables 
import paho.mqtt.client as mqtt
import RPi.GPIO as GPIO

#Define GPIO and set up their modes
GPIO.setwarnings(False)

GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.OUT)
GPIO.setup(12, GPIO.OUT)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(15, GPIO.OUT)
GPIO.setup(16, GPIO.OUT)

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    topic = input("topic: ")
    client.subscribe(topic) #"x/y/z" replace this with your topic name of your choice in the given order.
    print("subscribed to: " + topic)

#You can define as many GPIO as you wish to control your switches.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload.decode("utf-8")))
    payload = msg.payload.decode("utf-8")
    if "green_on" in payload:
        GPIO.output(11, True)
    elif "green_off" in payload:
          GPIO.output(11, False)
    if "yellow_on" in payload:
        GPIO.output(12,True)
    elif "yellow_off" in payload:
        GPIO.output(12, False)
    if "blue_on" in payload:
        GPIO.output(15, True)
    elif "blue_off" in payload:
        GPIO.output(15, False)
    if "aron_on" in payload:
        GPIO.output(16,True)
    elif "aron_off" in payload:
        GPIO.output(16, False)

#function call
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("test.mosquitto.org", 1883, 60) #mqtt broker any of choice

client.loop_forever() # handles reconnecting.
