import utime
from machine import UART,Pin
from wifiat import at
import json
import time

# esp-01s实际tx,rx反接
# uart=UART(0,115200,tx=Pin(12),rx=Pin(13))
uart=UART(0,115200,tx=Pin(16),rx=Pin(17))
AT=at(uart)

# 重置模块，擦除之前的配置
AT.restart()

AT.info()
AT.netinfo()

#恢复出厂设置
# AT.restore()

# AT.restart()
# AT.netinfo()

# AT.connect("ssid","pwd")

# AT.netinfo()
AT.netstatus()

domain='SMTP.163.com'
cs='AT+CIPSTART="TCP","%s",25\r\n' % (domain,)
resp = AT.sendCMD_waitResp(cs)
print(resp)
# 开启透传模式
cs='AT+CIPMODE=1\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
cs='AT+CIPSEND\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
cs='HELO SMTP.163.com\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
cs='AUTH LOGIN\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
#发送用户名base64
cs='xxxx\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
#发送密码
cs='xxxxxxxx\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
#发送邮件
cs='MAIL FROM:<xxxxx@163.com>\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
#
cs='RCPT TO:<xxxx@qq.com>\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
# 请求发送数据
cs='DATA\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
# 发送实际数据
cs='subject:Enjoy Protocol Studing\r\n\r\nemail content\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
cs='.\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)
# 退出
cs='QUIT\r\n'
resp = AT.sendCMD_waitResp(cs)
print(resp)

# #默认执行AT指令的方法
# AT.sendCMD_waitResp("AT\r\n")
# AT.sendCMD_waitRespLine("AT\r\n")