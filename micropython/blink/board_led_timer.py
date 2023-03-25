from machine import Pin,Timer
import time
led=Pin(25,Pin.OUT)
# led.off()

def blink(self):
    led.toggle()
    pass

tim=Timer()
tim.init(freq = 20, mode = Timer.PERIODIC,callback = blink)

while True:
    time.sleep_ms(300)
    pass
    
