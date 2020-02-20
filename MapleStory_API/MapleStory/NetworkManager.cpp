#include "NetworkManager.h"
#include "Core.h"
#include "Player.h"
#include"SceneManager.h"
DEFINITION_SINGLE(NetworkManager)

NetworkManager::NetworkManager()
{
}
NetworkManager::~NetworkManager()
{
}

bool NetworkManager::Init()
{
	//serverip_address = "127.0.0.1";

	inPacketSize = 0;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	const char* serverip_address = "127.0.0.1";
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, serverip_address , &serverAddr.sin_addr);
	serverAddr.sin_port = htons(SERVER_PORT);

	int retval = WSAConnect(sock, (sockaddr *)&serverAddr, sizeof(serverAddr), NULL, NULL, NULL, NULL);

	WSAAsyncSelect(sock, GET_SINGLE(CCore)->GetWindowHandle(), WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);

	send_wsabuf.buf = sendBuffer;
	send_wsabuf.len = MAX_BUFF_SIZE;
	recv_wsabuf.buf = recvBuffer;
	recv_wsabuf.len = MAX_BUFF_SIZE;

	if (retval == SOCKET_ERROR)
		MessageBox(NULL, L"서버와의 연결에 실패하였습니다.", L"서버에러", MB_OK);

	return true;
}

void NetworkManager::shutDownServer()
{
	closesocket(sock);
	WSACleanup();
}

void NetworkManager::processPacket(void * packet)
{
	unsigned char packet_type = reinterpret_cast<unsigned char*>(packet)[2];

	switch (packet_type)
	{
	case SC_POS:
	{
		sc_packet_pos* pos_packet = reinterpret_cast<sc_packet_pos*>(packet);
		
		auto t = CObj::FindObjects("Player");

		for (auto& object : *t)
		{
			if (((CPlayer*)object)->id == pos_packet->id)
			{
				((CPlayer*)object)->SetPos(pos_packet->x, pos_packet->y);
			}
		}
				//_cprintf("x : %f, y: %f\n", player->GetPos().x, player->GetPos().y);
	}
		break;
	case SC_PUT_PLAYER:
	{

		CPlayer* Put_Player = CObj::CreateObject<CPlayer>("Player");
		sc_packet_put_player* put_packet = reinterpret_cast<sc_packet_put_player*>(packet);


		//임시 이거 삭제할것.
		if (First)
		{
			myClientID = put_packet->id;  First = false;
		}
		
		
		Put_Player->id = put_packet->id;
		CLayer* pLayer = GET_SINGLE(CSceneManager)->GetCurrentScene()->FindLayer("Default");
		pLayer->AddObject(Put_Player);
		Put_Player->SetPos(put_packet->x, put_packet->y);
		GET_SINGLE(CCamera)->SetTarget(Put_Player);

		SAFE_RELEASE(pLayer);
		SAFE_RELEASE(Put_Player);
		
	}
		break;
	case SC_REMOVE_PLAYER:
	{

	}
	break;
	default:
		break;
	}


}

void NetworkManager::readPacket(SOCKET sock)
{
	DWORD iobyte, ioflag = 0;

	int ret = WSARecv(sock, &recv_wsabuf, 1, &iobyte, &ioflag, NULL, NULL);
	BYTE* ptr = reinterpret_cast<BYTE*>(recvBuffer);

	while (0 != iobyte)
	{
		if (0 == inPacketSize)
			inPacketSize = ((unsigned short*)ptr)[0];
		if (iobyte + savedPacketSize >= inPacketSize)
		{
			memcpy(packetBuffer + savedPacketSize, ptr, inPacketSize - savedPacketSize);

			processPacket(packetBuffer);

			ptr += inPacketSize - savedPacketSize;
			iobyte -= inPacketSize - savedPacketSize;

			inPacketSize = 0;
			savedPacketSize = 0;
		}
		else
		{
			memcpy(packetBuffer + savedPacketSize, ptr, iobyte);
			savedPacketSize += iobyte;
			iobyte = 0;
		}
	}
}

void NetworkManager::connectMainServer()
{
	///// < mainserver로의 접속요청을 한다. >
	//cs_packet_connect* pPacket = reinterpret_cast<cs_packet_connect*>(getSendBuffer());
	//pPacket->size = sizeof(cs_packet_connect);
	//pPacket->type = CS_PACKET_MAINSERVER_CONNECT;

	//getSendWsaBuf().len = sizeof(cs_packet_connect);
	//DWORD iobyte;
	//int ret = WSASend(getSocket(), &getSendWsaBuf(), 1, &iobyte, 0, NULL, NULL);
}

#pragma region Getter&Setter
const SOCKET & NetworkManager::getSocket() { return sock; }
char * NetworkManager::getSendBuffer() { return sendBuffer; }
const char * NetworkManager::getRecvBuffer() { return recvBuffer; }
const char * NetworkManager::getPacketBuffer() { return packetBuffer; }
const DWORD NetworkManager::getInPacketSize() { return inPacketSize; }
const int NetworkManager::getSavedPacketSize() { return savedPacketSize; }
const size_t NetworkManager::getMyClientID() { return myClientID; }
const bool NetworkManager::getIsConnected() { return isConnected; }
WSABUF & NetworkManager::getSendWsaBuf() { return this->send_wsabuf; }
WSABUF & NetworkManager::getRecvWsaBuf() { return this->recv_wsabuf; }
void NetworkManager::enableConnected(bool connected) { this->isConnected = connected; }
void NetworkManager::setMyClientID(size_t id) { this->myClientID = id; }
#pragma endregion