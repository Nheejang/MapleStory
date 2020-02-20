#include "testScene.h"
#include "Scene.h"
#include "Layer.h"
#include"Camera.h"
#include"Core.h"
#include "SceneManager.h"
#include"Player.h"
#include"Monster.h"
#include"BackGround.h"
#include"Input.h"
#include"NetworkManager.h"
#include"Map.h"

CtestScene::CtestScene()
{
}


CtestScene::~CtestScene()
{
}

bool CtestScene::Init()
{
	GET_SINGLE(CCamera)->SetWorldSize(3000.f, 2000.f);

	CLayer* pLayer = m_pScene->FindLayer("Default");
	CLayer* pBackLayer = m_pScene->FindLayer("BackGround");
	CLayer* pUILayer = m_pScene->FindLayer("UI");

	//CPlayer* pPlayer = CObj::CreateObject<CPlayer>("Player", pLayer);


	//pPlayer->SetPos(1000.f, 360.f);
	CMonster* pMonster = CObj::CreateObject<CMonster>("Monster", pLayer);

	
	pMonster->SetPos(400, 300.f);
	//pMonster->SetTarget(pPlayer);



	CBackGround* pBack = CObj::CreateObject<CBackGround>("BackBoard", pBackLayer);

	pBack->SetTexture("tt", TEXT("Stage2.bmp"));
	pBack->SetPos(0,0);
	pBack->SetPivot(0, 0);
	pBack->SetSize(3000,2000);
	

	SAFE_RELEASE(pBack);
	SAFE_RELEASE(pMonster);

	CMap* pMap = CObj::CreateObject<CMap>("Map", pBackLayer);
	pMap->SetMap(MT_MOVE, MO_NONE, GET_SINGLE(CCamera)->GetWorldSize(), 50, 50, (GET_SINGLE(CCamera)->GetWorldSize()/50, GET_SINGLE(CCamera)->GetWorldSize()/50));

	SAFE_RELEASE(pMap);
	//GET_SINGLE(CCamera)->SetTarget(pPlayer);
	//GET_SINGLE(CCamera)->SetTargetPivot(0.f, 0.f);
	//
	//SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(pUILayer);
	SAFE_RELEASE(pBackLayer);
	SAFE_RELEASE(pLayer);
	
	return true;
}

int CtestScene::Input(float fTime)
{
	if (KEYPUSH("MoveLeft"))
	{
		cs_packet_up* pPacket = reinterpret_cast<cs_packet_up*>(GET_SINGLE(NetworkManager)->getSendBuffer());
		pPacket->size = sizeof(cs_packet_up);
		//GET_SINGLE(NetworkManager)->getSendWsaBuf().len = sizeof(cs_packet_up);
		DWORD iobyte;
		pPacket->type = CS_LEFT;
		GET_SINGLE(NetworkManager)->getSendWsaBuf().len = sizeof(cs_packet_up);
		int ret = WSASend(GET_SINGLE(NetworkManager)->getSocket(), &GET_SINGLE(NetworkManager)->getSendWsaBuf(), 1, &iobyte, 0, NULL, NULL);

		if (ret)
		{
			// 俊矾贸府.
			char a = 0;
		}
	}

	if (KEYPUSH("MoveRight"))
	{
		cs_packet_up* pPacket = reinterpret_cast<cs_packet_up*>(GET_SINGLE(NetworkManager)->getSendBuffer());
		pPacket->size = sizeof(cs_packet_up);
	//	GET_SINGLE(NetworkManager)->getSendWsaBuf().len = sizeof(cs_packet_up);
		DWORD iobyte;
		pPacket->type = CS_RIGHT;
		GET_SINGLE(NetworkManager)->getSendWsaBuf().len = sizeof(cs_packet_up);
		int ret = WSASend(GET_SINGLE(NetworkManager)->getSocket(), &GET_SINGLE(NetworkManager)->getSendWsaBuf(), 1, &iobyte, 0, NULL, NULL);

		if (ret)
		{
			// 俊矾贸府.
			char a = 0;
		}
	}

	if (KEYPUSH("MoveUp"))
	{
		//Move(0.f, -m_fMoveSpeed, fTime);
		//MoveByAngle(fTime);
	}

	if (KEYPUSH("MoveDown"))
	{
		//Move(0.f, m_fMoveSpeed, fTime);
		//MoveByAngle(-fTime);
	}

	if (KEYPRESS("Jump"))
	{
		//SetForce(300.f);
	}

	if (KEYPUSH("Change"))
	{
		CObj* pMap =CMap::FindObject("Map");
		CObj::EraseSceneObject("Map", pMap);
	//	GET_SINGLE(CSceneManager)->Change();
	}


	return 0;
}

int CtestScene::Update(float fTime)
{
	return 0;
}

int CtestScene::LateUpdate(float fTime)
{
	return 0;
}

void CtestScene::Collision(float fTime)
{
}

void CtestScene::Render(HDC hDC, float fTime)
{

}
