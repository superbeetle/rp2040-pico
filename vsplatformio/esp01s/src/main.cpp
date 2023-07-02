#include <Arduino.h>
#include "wifiat.h"

#define PIN_TX 12
#define PIN_RX 13
#define BAUD 115200
#define SSID "360WiFi"
#define PASSWORD "fP7AyAzE8c"

void setup()
{
  UartBegin(PIN_RX, PIN_TX, BAUD);
  Serial.begin(BAUD);
}

void loop()
{
  // at指令接口
  Serial.println("send at to uart...");
  SendATCmd("+++");
  String myString = SendATCmdResp("AT+RESTORE\r\n", "OK\r\n", 10000);
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
  // 应用接口
  Serial.println("Start API test...");
  UartRestore();
  UartReset();
  boolean isconn = WifiIsConnected();
  Serial.println(isconn ? "connected" : "not connect");
  Serial.println("connect wifi...");
  bool isconned = ConnectWifi(SSID, PASSWORD);
  Serial.println(isconned ? "connected" : "error");
  Serial.println("check connected?");
  isconn = WifiIsConnected();
  Serial.println(isconn ? "connected" : "error");

  // 进行http请求
  if (isconn)
  {
    String responBody = HttpRequest("GET", "http://taobao.com", "", "");
    Serial.println(responBody);
  }

  // 断开wifi
  if (isconn)
  {
    Serial.println("disconnect wifi ...");
    bool discon = DisconnectWifi();
    Serial.println(discon ? "disconnect" : "error");
  }
  delay(5000);
}