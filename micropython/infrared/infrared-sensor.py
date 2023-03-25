from machine import Pin,Timer,UART
import utime

def redmc_irq(redmc15):
    global led
    led.on()
    print(redmc15.value())
    utime.sleep_ms(500)
    led.off()


led = machine.Pin("LED", machine.Pin.OUT)
led.on()
redmc15=Pin(15,Pin.IN,Pin.PULL_DOWN) # 红外感应
redmc15.irq(redmc_irq,Pin.IRQ_RISING)


while True:
    led.toggle()
    utime.sleep(3)
    pass