// CTcpServer.h
#pragma once

#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Standard socket API.

class CTcpServer
{
public:
    CTcpServer(std::string strIp, unsigned int uPort);
    virtual ~CTcpServer();

    // ��ʼ����������
    bool InitServer();

    // ��������
    bool SendMsg(const std::string &strMsg);

    // �������ݲ���ӡ
    bool RecvMsg(char *buf);

private:
    unsigned int m_uPort; // �����˿�
    std::string m_strIp;  // ���ڼ�������ָ��IP��ַ

    SOCKET m_listenSocket = NULL; // �����׽���
    SOCKET m_clientSocket = NULL; // �ͻ����׽���
};
