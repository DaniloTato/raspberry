import BlynkLib
import RPi.GPIO as GPIO
from BlynkTimer import BlynkTimer

BLYNK_AUTH = 'y-83ifX1UIjZhZmyivc_EU4mzsqhDll0'

led1 = 24
led2 = 12
button = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(led1, GPIO.OUT)
GPIO.setup(led2, GPIO.OUT)
GPIO.setup(button, GPIO.IN)

rojo = GPIO.PWM(24,100)
rojo.start(100)


# Initialize Blynk
blynk = BlynkLib.Blynk(BLYNK_AUTH)

# Register virtual pin handler
@blynk.on("V0")
def v0_write_handeler(value):
	if int(value[0]) != 0:
		GPIO.output(led1,GPIO.HIGH)
		print("led_on")
	else:
		GPIO.output(led1,GPIO.LOW)
		print("led_off")



@blynk.on("V2")
def v2_write_handeler(value):
	rojo.ChangeDutyCycle(int(value[0]) % 100)


@blynk.on("connected")
def blynk_connected():
	print("connected with blynk")

while True:
	blynk.run()
	button_pressed = GPIO.input(button);

	if button_pressed == GPIO.HIGH:
		blynk.virtual_write(1,255)
	else:
		blynk.virtual_write(1,0)
