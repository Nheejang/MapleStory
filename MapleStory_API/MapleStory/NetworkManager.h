#pragma once

#include "Game.h"

class NetworkManager
{
private:
	WSADATA wsaData; // ��������� ������ �ϱ� ���� ������ ��� ����ü.
	SOCKET sock{ 0 }; // ������ ��� ������ ����.
	SOCKADDR_IN serverAddr;
	DWORD inPacketSize { 0 };
	int savedPacketSize { 0 };
	size_t myClientID { 0 };
	bool isConnected { false };
	thread* pRecvThread { nullptr };
	WSABUF	send_wsabuf;
	WSABUF	recv_wsabuf;
	char sendBuffer[MAX_BUFF_SIZE];
	char recvBuffer[MAX_BUFF_SIZE];
	char packetBuffer[MAX_BUFF_SIZE];
	//string serverip_address;

public:
	chrono::steady_clock::time_point inputTime;
public:
	int myID;
	bool First = true;

public:
	void enableConnected(bool connected);
	void setMyClientID(size_t id);
	void connectMainServer();
public:
	//NetworkManager() {}
	//~NetworkManager() {}

public:
	bool Init();
	void shutDownServer();
	void processPacket(void* ptr);
	void readPacket(SOCKET sock);

	/// getter function
public:
	const SOCKET& getSocket();
	char* getSendBuffer();
	const char* getRecvBuffer();
	const char* getPacketBuffer();
	const DWORD getInPacketSize();
	const int getSavedPacketSize();
	const size_t getMyClientID();
	const bool getIsConnected();
	WSABUF& getSendWsaBuf();
	WSABUF& getRecvWsaBuf();
	/// setter function
	DECLARE_SINGLE(NetworkManager)
};