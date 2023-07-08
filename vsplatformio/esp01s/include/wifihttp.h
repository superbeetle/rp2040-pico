#ifndef _WIFI_HTTP_H
#define _WIFI_HTTP_H

#include "wifiat.h"
#include <time.h>

class HttpResponse
{
private:
    int status;
    String body;

public:
    void parseResponse(String httpResponse);
    int getStatus();
    String getBody();
    HttpResponse();
    HttpResponse(String body);
    ~HttpResponse();
};

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
HttpResponse HttpRequest(const char *method, const char *url, const char *params, const char *headers, int timeout = 20000);

#endif