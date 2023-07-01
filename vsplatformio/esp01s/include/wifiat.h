#include <Arduino.h>
#include <time.h>
#include "SerialUART.h"

/**
 * @brief 20秒超时
 *
 */
#define TIME_OUT_MS 20000

/**
 * @brief 初始化wifi
 *
 * @param rx
 * @param tx
 * @param band
 */
void UartBegin(pin_size_t rx, pin_size_t tx, unsigned long band);

/**
 * @brief 发送AT指令
 *
 * @param atCmd at指令
 */
void SendATCmd(char *atCmd);

/**
 * @brief 读取串口
 *
 * @param endStr
 * @return String
 */
String ReceiveATCmd(const char *successEndStr = "OK\r\n", int timeout = TIME_OUT_MS);

/**
 * @brief 发送AT指令并返回数据
 *
 * @param atCmd at指令
 * @param timeout 延迟读取ms
 */
String SendATCmdResp(const char *atCmd, const char *successEndStr = "OK\r\n", int timeout = TIME_OUT_MS);

/*!
@brief 以下接口是二次包装接口
 */

/*判断串口是否准备好等*/
void UartWaitForReady();

/*是否连上网络*/
bool WifiIsConnected();

/**
 * @brief 链接网络
 *
 * @param ssid
 * @param password
 * @return true
 * @return false
 */
bool ConnectWifi(const char *ssid, const char *password);

/**
 * @brief 断开链接
 *
 * @return true
 * @return false
 */
bool DisconnectWifi();