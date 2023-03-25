import machine
import utime

led = machine.Pin("LED", machine.Pin.OUT)
while True:
    led.on()
    utime.sleep(1)
    led.off()
    utime.sleep(1)
