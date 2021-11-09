import time
import machine

pin = machine.Pin(2, machine.Pin.OUT)

time.sleep(2)

while True:
    pin.on()
    time.sleep(1)
    pin.off()
    time.sleep(1)
    
