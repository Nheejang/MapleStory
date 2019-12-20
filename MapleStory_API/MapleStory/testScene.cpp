#include "testScene.h"
#include "Scene.h"
#include "Layer.h"
#include"Camera.h"
#include"Core.h"
#include "SceneManager.h"
#include"Player.h"

CtestScene::CtestScene()
{
}


CtestScene::~CtestScene()
{
}

bool CtestScene::Init()
{
	GET_SINGLE(CCamera)->SetWorldSize(1280.f, 720.f);

	CLayer* pLayer = m_pScene->FindLayer("Default");
	CLayer* pBackLayer = m_pScene->FindLayer("BackGround");
	CLayer* pUILayer = m_pScene->FindLayer("UI");

	CPlayer* pPlayer = CObj::CreateObject<CPlayer>("Player", pLayer);

	GET_SINGLE(CCamera)->SetTarget(pPlayer);

	GET_SINGLE(CCamera)->SetTargetPivot(300.f, 400.f);
	//GET_SINGLE(CCamera)->SetPos(pPlayer->GetPos());
	SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(pUILayer);
	SAFE_RELEASE(pBackLayer);
	SAFE_RELEASE(pLayer);

	return true;
}

int CtestScene::Input(float fTime)
{
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
