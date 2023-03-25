import machine
import utime


led_green = machine.Pin("LED", machine.Pin.OUT)
led_green.value(0)  # 关灯

button_red = machine.Pin(15, machine.Pin.IN)   # 正常下拉电阻为低，除非按他就会拉高

def in_handler(pin):
     button_red.irq(handler=None)  # 关闭此引脚的中断
     print("Interrupt Detected!")
     led_green.value(1) 
     utime.sleep(4)  # 休眠在中断不常见，这是个示范
     led_green.value(0)
     button_red.irq(handler=in_handler)  # 重新设置程序，然后才能再次工作


# button_red.irq(trigger=machine.Pin.IRQ_RISING, handler=in_handler)
button_red.irq(in_handler,machine.Pin.IRQ_RISING)
# 修复中断请求  触发中断  我们在上升信号时触发它（低到高）  此时传入一个被称为中断处理程序的函数
# 每次按下按钮会有一个中断，就调用这个函数


# 不被中断时
while True:
      led_green.toggle()  # 切换函数 ，获取输出状态并将其反转
        # led将开或关，就反转成
      utime.sleep(2)