# wifi
from machine import UART,Pin
import utime

uart=UART(0,115200,tx=Pin(16),rx=Pin(17))

def readUART():
    utime.sleep_ms(3000)
    global uart
    while True:
        buffer_size = uart.any()
#         print(buffer_size)
        if buffer_size:
#             print("收到",str(buffer_size),"个:  ")
            data = uart.readline()
            #将接受到的数据进行分割处理并打印出来
#             data = data[:-2]
            print(data.decode('utf-8'))
        else:
            break
        
uart.write("help('modules')\r\n")
readUART()
# uart.write("import os\r\n")
# read()
# uart.write("os.listdir()\r\n")
# read()
uart.write("import network\r\n")
readUART()
uart.write("wifi=network.WLAN(network.STA_IF)\r\n")
readUART()
uart.write("wifi.active(True)\r\n")
readUART()
uart.write("wifi.scan()\r\n")
readUART()
uart.write("wifi.connect('ssid','pwd')\r\n")
readUART()
uart.write("wifi.isconnected()\r\n")
readUART()
# 导入urequests模块，会出现未安装模块
uart.write("import urequests\r\n")
readUART()
# # 安装urequests模块
# #uart.write("import upip\r\n")
# #uart. write("upip.install('micropython-urequests')\r\n")
# read()
# # 下载一个网页试试
# #uart.write("c=urequests.get('http://micropython.org/ks/test.html')\r\n")
readUART()
# # 编码不生效，需要在固件usb下才正常
uart.write("c.encoding=\"utf-8\"\r\n")
readUART()
uart.write("c.text\r\n")
readUART()

# while True:
#     pass
