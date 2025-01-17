#pragma once

#include <string>

#pragma comment(lib,"ws2_32.lib")//Standard socket API.

class CTcpClient
{
public:
	CTcpClient(std::string strServerIp, unsigned uServerPort);
	virtual ~CTcpClient();

	//建立连接
	bool InitConnect();

	//发送数据
	bool SendMsg(const char *strMsg);

	//接收数据并打印
	bool RecvMsg();

private:
	SOCKET m_socket = INVALID_SOCKET;
	std::string m_strServerIp;//服务端监听IP地址
	unsigned int m_uServerPort = -1;//服务端监听端口
	struct addrinfo* m_servAddrInfo = NULL;//服务端地址结构链表
};


