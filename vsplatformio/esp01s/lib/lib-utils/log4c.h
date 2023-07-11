#ifndef _LOG4C_H
#define _LOG4C_H
#include <Arduino.h>
#include "utils.h"

class Log4C
{
public:
    Log4C();
    void debug(String message);
};

#endif
