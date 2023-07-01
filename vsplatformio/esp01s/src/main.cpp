#include <Arduino.h>
#include "wifiat.h"

#define PIN_TX 12
#define PIN_RX 13
#define BAUD 115200
#define SSID "yoursid"
#define PASSWORD "yourpassword"

void setup()
{
  UartBegin(PIN_RX, PIN_TX, BAUD);
  Serial.begin(BAUD);
}

void loop()
{
  // at指令接口
  Serial.println("send at to uart...");
  String myString = SendATCmdResp("AT+RESTORE\r\n");
  Serial.println(myString);
  myString = SendATCmdResp("AT\r\n");
  Serial.println(myString);
  myString = SendATCmdResp("AT+CWMODE=1\r\n");
  Serial.println(myString);
  char atCmd[100];
  sprintf(atCmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWORD);
  myString = SendATCmdResp(atCmd);
  Serial.println(myString);
  delay(10);
  // 应用接口
  Serial.println("serial is ready?");
  boolean isconn = WifiIsConnected();
  Serial.println(isconn ? "connected" : "not connect");
  Serial.println("connect wifi...");
  bool isconned = ConnectWifi(SSID, PASSWORD);
  Serial.println(isconned ? "connected" : "error");
  Serial.println("check connected?");
  isconn = WifiIsConnected();
  Serial.println(isconn ? "connected" : "error");
  if (isconn)
  {
    Serial.println("disconnect wifi ...");
    bool discon = DisconnectWifi();
    Serial.println(discon ? "disconnect" : "error");
  }
}