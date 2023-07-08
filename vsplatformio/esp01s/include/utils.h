#include <Arduino.h>

#ifndef _UTILS_H
#define _UTILS_H

#include <vector>
#include <stdlib.h>

/**
 * @brief 字符串分隔
 *
 * @param str
 * @param pattern
 * @return std::vector<std::string>
 */
std::vector<String> StringSplit(String str, String pattern);

#endif