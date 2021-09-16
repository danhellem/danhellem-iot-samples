import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library
from time import sleep # Import the sleep function from the time module

pin = 18

GPIO.setwarnings(False) # Ignore warning for now
GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
GPIO.setup(pin, GPIO.OUT, initial=GPIO.LOW) # Set pin 8 to be an output pin and set initial value to low (off)

while True: # Run forever
 GPIO.output(pin, GPIO.HIGH) # Turn on
 print('led on')
 sleep(2) # Sleep for 1 second
  
 GPIO.output(pin, GPIO.LOW) # Turn off
 print('led off')
 sleep(2) # Sleep for 1 second