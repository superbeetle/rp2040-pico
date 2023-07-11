#ifndef _LOG4C_H
#define _LOG4C_H
#include <Arduino.h>
#include "utils.h"
// 从cmsis-dap打印日志，固定8,9针脚
#define LOG4C_DEBUG

class Log4C
{
public:
    Log4C();
    void debug(String message);
};

#endif
