#pragma once

#include <string>

#pragma comment(lib,"ws2_32.lib")//Standard socket API.

class CTcpClient
{
public:
	CTcpClient(std::string strServerIp, unsigned uServerPort);
	virtual ~CTcpClient();

	//��������
	bool InitConnect();

	//��������
	bool SendMsg(const char *strMsg);

	//�������ݲ���ӡ
	bool RecvMsg();

private:
	SOCKET m_socket = INVALID_SOCKET;
	std::string m_strServerIp;//����˼���IP��ַ
	unsigned int m_uServerPort = -1;//����˼����˿�
	struct addrinfo* m_servAddrInfo = NULL;//����˵�ַ�ṹ����
};


