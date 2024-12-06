#include <iostream>
#include "serve.h"

int main()
{
    {
        CTcpServer tcpServer("192.168.0.106", 6005);

        if (!tcpServer.InitServer())
            getchar();

        while (1)
        {
            char buf[1028];
            if (tcpServer.RecvMsg(buf))
            {
            }
        }
    }

    return 0;
}
