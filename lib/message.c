#include "./message.h"

char *getmessage()
{
    return "HTTP/1.1 200 OK\r\n\
X-Powered-By: Express\r\n\
Content-Type: application/json; charset=utf-8\r\n\
Content-Length: 17\r\n\
Date: Fri, 15 Oct 2021 23:42:36 GMT\r\n\
Connection: closed\r\n\
\r\n\
{\"status\":\"live\"}";
}
