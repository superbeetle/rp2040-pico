#include "wifihttp.h"

HttpResponse HttpRequest(const char *method, const char *url, const char *params, const char *headers, int timeout)
{
    // 分解url
    String tempStr = ""; // 临时字符串
    String urlStr(url);
    String httpProtocol = urlStr.substring(0, 7);
    tempStr = urlStr.substring(7);
    String host = tempStr.substring(0, tempStr.indexOf("/"));
    // String uri = urlStr.substring(httpProtocol.length() + host.length(), urlStr.length());
    Serial.println(httpProtocol);
    Serial.println(host);
    // Serial.println(uri);
    Serial.println("------------Split url finished------------\r\n");
    // 连接站点
    char atCmd[100] = {0};
    sprintf(atCmd, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", host.c_str(), 80);
    String respStr = SendATCmdResp(atCmd, "CONNECT\r\n", 20000);
    HttpResponse httpResponse;
    if (respStr.indexOf("CONNECT\r\n") > -1)
    {
        // 准备指令
        char httpReqStr[500] = {0};
        sprintf(httpReqStr, "GET %s HTTP/1.1\r\nHost:%s\r\nContent-Type:application/json\r\nConnection:close\r\nUser-Agent:Mozila/4.0(compatible;MSIE5.01;Window NT5.0)\r\n\r\n", url, host.c_str());
        // sprintf(httpReqStr, "GET %s HTTP/1.1\r\nHost:%s\r\n\r\n", url, host.c_str());
        char sendCmd[100] = {0};
        sprintf(sendCmd, "AT+CIPSEND=%d\r\n", strlen(httpReqStr));
        respStr = SendATCmdResp(sendCmd);
        // 发送指令
        respStr = SendATCmdResp(httpReqStr, "CLOSED\r\n", 20000);
        // 解析response
        httpResponse.parseResponse(respStr);
        respStr = SendATCmdResp("AT+CIPCLOSE\r\n");
        Serial.println(respStr);
    }
    return httpResponse;
}

HttpResponse::HttpResponse(String body)
{
    this->parseResponse(body);
}

HttpResponse::~HttpResponse()
{
}

void HttpResponse::parseResponse(String httpResponse)
{
    std::vector<String> result = StringSplit(httpResponse, String("\r\n"));
    Serial.printf("分割http协议，共%d行", result.size());
    // for debug only
    for (int i = 0; i < result.size(); i++)
    {
        Serial.printf("Line: %d: %s\r\n", i, result[i].c_str());
    }
    // 响应状态解析
    String httpStatus = result[5];
    std::vector<String> httpStatusArr = StringSplit(httpStatus, String(" "));
    String status = httpStatusArr[1];
    Serial.printf("Line: %s,split size: %d, status: %s\r\n\r\n", httpStatus.c_str(), httpStatusArr.size(), status.c_str());
    this->status = atoi(status.c_str());
    if (this->status == HTTP_OK)
    {
        String responseBody = result[result.size() - 2];
        responseBody = responseBody.substring(responseBody.indexOf("{"), responseBody.lastIndexOf("}") + 1);
        this->body = responseBody;
    }

    Serial.printf("HttpResponse, status:%d, responseBody: %s\n", this->status, this->body.c_str());
}

int HttpResponse::getStatus()
{
    return this->status;
}

String HttpResponse::getBody()
{
    return this->body;
}

HttpResponse::HttpResponse()
{
}
