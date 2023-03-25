from machine import Pin
import utime

def key_irq(self):
    print('电平',keypin.value())
    if(keypin.value() == 0):
        # 双重判断，防抖动
        utime.sleep_ms(500)
        if(keypin.value() == 0):
            print("push down")
            led.on()
        else :
            print("push up")
            led.off()

keypin = Pin(16,Pin.IN,Pin.PULL_UP)
# 按下时触发中断
keypin.irq(key_irq,Pin.IRQ_FALLING)
# keypin.irq(key_irq,Pin.IRQ_RISING)

led = Pin(15,Pin.OUT)

# while True:
#     pass

# # 闪烁n次后退出
# count=0
# #while count<10:
# while True:
#     ledpin.value(1)
#     utime.sleep(0.5)
#     ledpin.value(0)
#     utime.sleep(0.5)
#     count = count+1
  