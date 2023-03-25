from machine import Pin, PWM

pwm0 = PWM(Pin(15))      # create PWM object from a pin
pwm0.freq()             # get current frequency
pwm0.freq(1000)         # set frequency
pwm0.duty_u16()         # get current duty cycle, range 0-65535
pwm0.duty_u16(500)      # set duty cycle, range 0-65535
# pwm0.deinit()           # turn off PWM on the pin

while True:
    # 呼吸灯
    for i in range(65535):
        pwm0.duty_u16(i)
        
    for i in range(65535,-1,-1):
        pwm0.duty_u16(i)
