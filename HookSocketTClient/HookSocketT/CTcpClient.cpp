//CTcpClient.cpp

#include <sstream>
#include <iostream>
#include <Ws2tcpip.h>
#include <Windows.h>
#include <WinSock2.h>
#include "CTcpClient.h"
#define _WIN32_WINNT 0x501

CTcpClient::CTcpClient(std::string strServerIp, unsigned uServerPort) :
	m_strServerIp(strServerIp),
	m_uServerPort(uServerPort)
{
}

CTcpClient::~CTcpClient()
{
	if (m_socket != INVALID_SOCKET)
		closesocket(m_socket);

	WSACleanup();
	freeaddrinfo(m_servAddrInfo);
}

bool CTcpClient::InitConnect()
{
	WSADATA	wsaData;

	//1. ��ʼ������
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Init Windows Socket Failed!\n";
		return false;
	}

	addrinfo hints = { 0, };//Э���޹�(IPV4 or IPV6)

	hints.ai_flags = AI_NUMERICHOST;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	std::stringstream ssPort;

	ssPort << m_uServerPort;

	//��ȡ����˵�ַ�ṹ
	if (getaddrinfo(m_strServerIp.c_str(), ssPort.str().c_str(), &hints, &m_servAddrInfo) != 0)
	{
		std::cout << "Get server addrInfo failed!\n";
		return false;
	}

	if (m_socket != INVALID_SOCKET)
		closesocket(m_socket);

	m_socket = INVALID_SOCKET;

	//2. ����һ���µ��׽���
	if ((m_socket = socket(m_servAddrInfo->ai_family, m_servAddrInfo->ai_socktype, m_servAddrInfo->ai_protocol)) == SOCKET_ERROR)
		return false;

	//3. ��������
	int iResult = connect(m_socket, m_servAddrInfo->ai_addr, (int)m_servAddrInfo->ai_addrlen);

	if (iResult == SOCKET_ERROR)
	{
		iResult = WSAGetLastError();

		if (iResult != WSAEWOULDBLOCK)
		{
			std::cout << "Connect server failed!\n";
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
			return false;
		}
	}

	std::cout << "Connect Server succeed!\n";
	return true;
}

bool CTcpClient::SendMsg(const char* strMsg)
{
	if (!m_socket) return false;

	if (send(m_socket, strMsg, sizeof(strMsg)/sizeof(strMsg[0]) - 1, 0) != INVALID_SOCKET)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CTcpClient::RecvMsg()
{
	if (!m_socket) return false;

	const int iBufSize = 1024;
	char recvBuf[iBufSize] = { 0, };
	auto iRecvSize = recv(m_socket, recvBuf, iBufSize, 0);//����֧��C++11�����ϣ�auto��Ϊint

	if (iRecvSize <= 0)
	{
		std::cout << "����ʧ��!\n";
		return false;
	}
	else
	{
		std::cout << "���ճɹ�:" << recvBuf << "\n";
		return true;
	}
}

