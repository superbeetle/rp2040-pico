#include "wifiat.h"

void UartBegin(pin_size_t rx, pin_size_t tx, unsigned long band)
{
    Serial1.setRX(rx);
    Serial1.setTX(tx);
    // The size of the receive FIFO may also be adjusted from the default 32 bytes by using the
    // 接收串口队列数据，可以设置大点接收多点
    Serial1.setFIFOSize(256);
    // Serial1.setPollingMode(true);
    Serial1.begin(band);
    delay(500);
}

String _readStringFromUart()
{
    String res;
    int value;
    while (true)
    {
        value = Serial1.read();
        if (value < 0 || value == '\0')
        {
            // Serial.print("e");
            break;
        }
        res += static_cast<char>(value);
    }
    return res;
}

void SendATCmd(const char *atCmd)
{
    Serial.printf("<<= %s", atCmd);
    size_t s = Serial1.print(atCmd);
    delay(10);
}

String ReceiveATCmd(const char *successEndStr, int timeout)
{
    bool timeoutResp = true; // 是否超时响应
    String respStr = "";
    long deadline = millis() + timeout;
    while (millis() < deadline)
    {
        if (Serial1.available() > 0)
        {
            respStr += Serial1.readStringUntil('\0');
            // respStr += _readStringFromUart();
        }
        // 判断结束标记
        if (respStr.indexOf(successEndStr) > -1)
        {
            timeoutResp = false;
            break;
        }
        delay(10);
    }
    // 读取完毕清空串口数据
    // Serial1.flush();
    while (Serial1.read() > -1)
    {
    }
    if (timeoutResp)
    {
        Serial.printf("Response timeout. %i(ms)\r\n", timeout);
    }
    Serial.printf("=>> %s\r\n", respStr.c_str());
    return respStr;
}

String SendATCmdResp(const char *atCmd, const char *successEndStr, int timeout)
{
    // 发送
    SendATCmd(atCmd);
    // 接收
    String respStr = ReceiveATCmd(successEndStr, timeout);
    return respStr;
}

void UartWaitForReady()
{
    SendATCmd("AT\r\n");
    String respStr = ReceiveATCmd("OK\r\n");
    String uartStr = "uart is ready";
    Serial.println(uartStr.c_str());
    Serial.println(respStr);
}

void UartReset()
{
    SendATCmd("+++");
    SendATCmdResp("AT+RST\r\n", "ready\r\n", 10000);
}

void UartRestore()
{
    SendATCmd("+++");
    SendATCmdResp("AT+RESTORE\r\n", "ready\r\n", 10000);
}

bool WifiIsConnected()
{
    String respStr = SendATCmdResp("AT+CWJAP?\r\n");
    if (respStr.indexOf("CWJAP:") > -1)
    {
        return true;
    }
    return false;
}

bool ConnectWifi(const char *ssid, const char *password)
{
    // 发送指令
    String respStr = SendATCmdResp("AT+CWMODE=1\r\n");
    if (respStr.indexOf("OK\r\n") > -1)
    {
        // 准备指令
        char atCmd[100] = {0};
        sprintf(atCmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
        respStr = SendATCmdResp(atCmd, "OK\r\n", 10000);
        if (respStr.indexOf("CONNECTED\r\n") > -1)
        {
            return true;
        }
    }
    return false;
}

bool DisconnectWifi()
{
    String respStr = SendATCmdResp("AT+CWQAP\r\n", "OK\r\n", 10000);
    if (respStr.indexOf("OK\r\n") > -1)
    {
        return true;
    }
    return false;
}
