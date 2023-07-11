#include "wifihttp.h"

// #define _DEBUG_AT_COMMAND
#define _DEBUG_WIFI_API
// esp8266 接线
#define PIN_TX 12
#define PIN_RX 13

#define BAUD 115200
#define SSID "360WiFi"
#define PASSWORD "fP7AyAzE8c"

#include "log4c.h"

// 定义输出日志
Log4C *Log = nullptr;
void setup()
{
  UartBegin(PIN_RX, PIN_TX, BAUD);
  Log = new Log4C();
}

void loop()
{

// at指令接口
#ifdef _DEBUG_AT_COMMAND
  Serial.println("send at to uart...");
  SendATCmd("+++");
  String myString = "";
  myString = SendATCmdResp("AT+RESTORE\r\n", "OK\r\n", 10000);
  Serial.println(myString);
  myString = SendATCmdResp("AT\r\n");
  Serial.println(myString);
  myString = SendATCmdResp("AT+CWMODE=1\r\n");
  Serial.println(myString);
  char atCmd[100] = {0};
  sprintf(atCmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWORD);
  myString = SendATCmdResp(atCmd);
  Serial.println(myString);
  delay(3000);
#endif
// 应用接口
#ifdef _DEBUG_WIFI_API
  Serial.println("Start API test...");
  UartRestore();
  UartReset();
  boolean isconn = WifiIsConnected();
  Serial.println(isconn ? "connected" : "not connect");
  Serial.println("connect wifi...");
  bool isconned = ConnectWifi(SSID, PASSWORD);
  Serial.println(isconned ? "connected" : "error");
  if (isconned)
  {
    Serial.println("check connected?");
    isconn = WifiIsConnected();
    Serial.println(isconn ? "connected" : "error");
    // 进行http请求
    if (isconn)
    {
      HttpResponse httpResponse = HttpRequest("GET", "http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp", NULL, NULL);
      Log->debug(httpResponse.getBody());

      httpResponse = HttpRequest("GET", "http://quan.suning.com/getSysTime.do", NULL, NULL);
      // Serial2.println(httpResponse.getBody());
      Log->debug(httpResponse.getBody());
    }
  }
  // 断开wifi
  if (isconn)
  {
    Serial.println("disconnect wifi ...");
    bool discon = DisconnectWifi();
    Serial.println(discon ? "disconnect" : "error");
  }

#endif
  delay(5000);
}