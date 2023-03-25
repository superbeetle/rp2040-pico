from machine import Pin

# 读取板载温度
sensor=machine.ADC(4)
offset=3.3/65535

read=sensor.read_u16()*offset
temp=27-(read-0.706)/0.001721
print(temp)
