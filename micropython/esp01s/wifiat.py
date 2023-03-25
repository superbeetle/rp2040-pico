import utime

# timeout 2000 (20秒)
class at(object):
    def __init__(self,uart):
        self.uart=uart
    def sendCMD_waitResp(self,cmd, timeout=2000):
        print("CMD: " + cmd)
        self.uart.write(cmd.encode('utf-8'))
        return self.waitResp(timeout)
    def waitResp(self,timeout=2000):
        prvMills = utime.ticks_ms()
        resp = b""
        while (utime.ticks_ms()-prvMills)<timeout:
#             print('这里卡住',utime.ticks_ms()-prvMills,timeout)
            if self.uart.any():
                resp = b"".join([resp, self.uart.read(1)])
        print(resp)
        return resp
    def sendCMD_waitRespLine(self,cmd, timeout=2000):
        print("CMD: " + cmd)
        self.uart.write(cmd.encode('utf-8'))
        return self.waitRespLine(timeout)
    def waitRespLine(self,timeout=2000):
        # 这里要持续读20秒
        cl = bytes()
        prvMills = utime.ticks_ms()
        while (utime.ticks_ms()-prvMills)<timeout:
#             print(utime.ticks_ms()-prvMills)
            if self.uart.any():
                cl += self.uart.readline()
        return cl
    def restart(self):
        self.sendCMD_waitResp('+++')
        return self.sendCMD_waitResp("AT+RST\r\n")
    def connect(self,name,password):
        self.sendCMD_waitResp('AT+CWMODE=1\r\n')
        cmd='AT+CWJAP="%s","%s"\r\n' % (name,password)
        return self.sendCMD_waitResp(cmd)
    def netstatus(self):
        return self.sendCMD_waitResp('AT+CIPSTATUS\r\n',timeout=2000)
    def isconnect(self):
        cl = self.netstatus()
        cl = cl.decode('utf-8')
        return cl.find('WIFI CONNECTED') or cl.find('OK') > 0
    def waitConnect(self,timeout=2000):
        isOK = self.isconnect()
        while isOK == False:
            isOK = self.isconnect()
            utime.sleep(2)
        print('已成功连接wifi')
    def netinfo(self):
        return self.sendCMD_waitResp("AT+CIFSR\r\n")
    def info(self):
        return self.sendCMD_waitResp("AT+GMR\r\n")
    def restore(self):
        return self.sendCMD_waitResp("AT+RESTORE\r\n")
    def ping(self,doip):
        return self.sendCMD_waitResp('AT+PING="%s"\r\n' % (doip,))
    def disconnect(self):
        return self.sendCMD_waitResp("AT+CWQAP\r\n")
    def http(self,url,method="GET",ua=1,content=1,data='',timeout=2000,encode='utf-8'):
        self.sendCMD_waitResp("+++")
        typ,edx,domain,rel=url.split("/",3)
        if "HTTP" == typ[0:-1].upper():
            cs='AT+CIPSTART="TCP","%s",80\r\n' % (domain,)
        else:
            self.sendCMD_waitResp("AT+CIPSSLSIZE=4096\r\n")
            cs='AT+CIPSTART="SSL","%s",443\r\n' % (domain,)
        sendResp=self.sendCMD_waitResp(cs)
        # 判断已经连上服务器
        connNum=1
        respStr=sendResp.decode(encode)
        isconn = False
        while isconn == False and connNum<10:
            isconn = respStr.find('CONNECTED') > 0 or respStr.find('ALREADY CONNECTED') > 0 or respStr.find('OK') > 0
            # 连接错
            if respStr.find('WIFI GOT IP') > 0:
                isconn = False
            if isconn == True:
                break;
            else:
                print('连接服务器失败，重连{}次',connNum)
                connNum = connNum + 1
                sendResp=self.sendCMD_waitResp(cs)
                respStr = sendResp.decode(encode)
        print('连接服务器成功')
        self.sendCMD_waitResp('AT+CIPMODE=1\r\n')
        utime.sleep(2)
        sendResp=self.sendCMD_waitResp('AT+CIPSEND\r\n')
        
        if ua==1:
            ua="Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/14.0.835.163 Safari/535.1"
        elif ua==2:
            ua="Mozilla/5.0 (Windows NT 6.1; WOW64; rv:6.0) Gecko/20100101 Firefox/6.0"
        elif ua==3:
            ua="Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.111 Safari/537.36"
        elif ua==4:
            ua="Mozilla/5.0 (iPhone; CPU iPhone OS 13_2_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.3 Mobile/15E148 Safari/604.1"
        if content==1:
            content="text/html;charset=utf-8"
        elif content==2:
            content="text/xml"
        elif content==3:
            content="application/json"
        elif content==4:
            content="multipart/form-data"
        elif content==5:
            content="application/x-www-form-urlencoded"
        if len(data) > 0:
            c="%s %s HTTP/1.1\r\nHOST:%s \r\nContent-Type: %s\r\nConnection:Keep-Alive\r\nUser-Agent:%s \r\n  \n %s \r\n\r\n " % (method,url,domain,content,ua,data)
        else:
            c="%s %s HTTP/1.1\r\nHOST:%s \r\nContent-Type: %s\r\nConnection:Keep-Alive\r\nUser-Agent:%s\r\n\r\n" % (method,url,domain,content,ua)
        # 响应
        responseText = self.sendCMD_waitRespLine(c,timeout).decode(encode)
        # 退出透传模式
#         self.sendCMD_waitResp('+++')
#         self.sendCMD_waitResp('AT+CIPMODE=0\r\n')
        print('原始响应：=======================================>')
        print(responseText)
        if len(responseText) == 0:
            response = {"status_code":500,"header":{},"response":{}}
            return
        response = {"status_code":200,"header":{},"response":{}}
        responseArr = responseText.split('\r\n')
        # 解释请求头
        line=0
        for rsp in responseArr:
            if line == 0:
                print('协议第一行',rsp)
                status = rsp.split(" ")
                response["status_code"] = int(status[1].strip())
            if response["status_code"] != 200:
                return response
            # 读取到空行
            if len(rsp) == 0:
                line+=1
                break
            # 解释头
            if line > 0 and len(rsp)>0 and rsp !="be8":
                print("分析",rsp)
                headerArr = rsp.split(":")
                response["header"][headerArr[0]]=headerArr[1]
            line+=1
        # 解释body
        print('共有（行）：',len(responseArr),'响应体共（行）：',len(responseArr)-line)
        if content=='application/json':
            # json 响应分析
            # 这里的响应有些奇怪，有些json在第2行，有些json直接就1行，作下兼容处理
            if len(responseArr)-line > 1:
                # 2行以上，取多第2行
                print('JSON 行：',line+1,responseArr[line+1])
                response["response"] = responseArr[line+1]
            else:
                print('JSON 行：',line,responseArr[line])
                response["response"] = responseArr[line]
        else:
            response["response"] = responseArr[line]
#         print('响应报文：',response)
        return response