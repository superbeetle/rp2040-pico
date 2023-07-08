#include "utils.h"

// 字符串分割函数
std::vector<String> StringSplit(String str, String pattern)
{
    std::vector<String> result;
    str += pattern; // 扩展字符串以方便操作
    int size = str.length();
    for (int i = 0; i < size; i++)
    {
        int pos = str.indexOf(pattern, i);
        // Serial.println(pos);
        if (pos < size)
        {
            String subStr = str.substring(i, pos);
            result.push_back(subStr);
            i = pos + pattern.length() - 1;
        }
    }
    return result;
}