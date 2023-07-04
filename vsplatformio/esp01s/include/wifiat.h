#include <Arduino.h>
#include <time.h>
#include "SerialUART.h"

/**
 * @brief 默认5秒超时
 *
 */
#define TIME_OUT_MS 5000

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
void SendATCmd(const char *atCmd);

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
@brief ============================================================================================================
 */

/**
 * @brief 判断串口是否准备好
 *
 */
void UartWaitForReady();

/**
 * @brief 重置串口
 *
 */
void UartReset();

/**
 * @brief 恢复出厂设置
 *
 */
void UartRestore();

/**
 * @brief 是否连上网络
 *
 * @return true
 * @return false
 */
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

/**
 * @brief http请求
 *
 * @param method
 * @param url
 * @param params
 * @param headers
 * @param timeout
 * @return String
 */
String HttpRequest(const char *method, const char *url, const char *params, const char *headers, int timeout = 20000);