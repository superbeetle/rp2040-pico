#include "log4c.h"

// 从cmsis-dap打印日志，固定8,9针脚
#define LOG4C_DEBUG

#if !defined LOG4C_DEBUG
// 从USB打印日志
#define LOG4C_FROM Serial
#else
// 从串口打印日志
#define LOG4C_FROM Serial2
// csmsis dap tx rx 日志输出接线
#define PIN_TX_DEBUG 8
#define PIN_RX_DEBUG 9
#endif

Log4C::Log4C()
{

#ifdef LOG4C_DEBUG
    Serial2.setTX(PIN_TX_DEBUG);
    Serial2.setRX(PIN_RX_DEBUG);
#endif

    LOG4C_FROM.begin(115200);
}

void Log4C::debug(String message)
{
    LOG4C_FROM.println(message);
}