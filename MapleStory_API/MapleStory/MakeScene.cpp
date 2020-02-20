#include "MakeScene.h"
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
#include"Mouse.h"
#include"Map.h"
#include"UIButton.h"

CMakeScene::CMakeScene()
{
}


CMakeScene::~CMakeScene()
{
	SAFE_RELEASE(m_pMouse);
	SAFE_RELEASE(m_pMap);
	SAFE_RELEASE(m_pMapUI);
}

bool CMakeScene::Init()
{
	GET_SINGLE(CCamera)->SetWorldSize(3000.f, 2000.f);

	CLayer* pLayer = m_pScene->FindLayer("Default");
	CLayer* pBackLayer = m_pScene->FindLayer("BackGround");
	CLayer* pUILayer = m_pScene->FindLayer("UI");

	CPlayer* pPlayer = CObj::CreateObject<CPlayer>("Player", pLayer);
	pPlayer->SetPos(0, 0);
	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);
	//CPlayer* pPlayer = CObj::CreateObject<CPlayer>("Player", pLayer);


	//pPlayer->SetPos(1000.f, 360.f);
	/*CMonster* pMonster = CObj::CreateObject<CMonster>("Monster", pLayer);


	pMonster->SetPos(400, 300.f);*/
	//pMonster->SetTarget(pPlayer);



	CBackGround* pBack = CObj::CreateObject<CBackGround>("BackBoard", pBackLayer);

	pBack->SetTexture("tt", TEXT("Stage2.bmp"));
	pBack->SetPos(0, 0);
	pBack->SetPivot(0, 0);
	pBack->SetSize(3000, 2000);


	SAFE_RELEASE(pBack);
	//SAFE_RELEASE(pMonster);

    m_pMap = CObj::CreateObject<CMap>("Map", pBackLayer);
	m_pMap->SetMap(MT_MOVE, MO_NONE, GET_SINGLE(CCamera)->GetWorldSize(), 50, 50, POSITION(50,50));

//	SAFE_RELEASE(pMap);
	//GET_SINGLE(CCamera)->SetTarget(pPlayer);
	//GET_SINGLE(CCamera)->SetTargetPivot(0.f, 0.f);
	//
	//SAFE_RELEASE(pPlayer);

	m_pMapUI = CObj::CreateObject<CUIButton>("MapUI", pUILayer);
	m_pMapUI->SetTexture("MapTypeMove", TEXT("OptionNone.bmp"));
	SAFE_RELEASE(pUILayer);
	SAFE_RELEASE(pBackLayer);
	SAFE_RELEASE(pLayer);

	m_pMouse = GET_SINGLE(CInput)->GetMouseObj();

	return true;
}

int CMakeScene::Input(float fTime)
{
	if (KEYPUSH("MoveLeft"))
	{
		
	}

	if (KEYPUSH("MoveRight"))
	{
	
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
		//CObj* pMap = CMap::FindObject("Map");
	//	CObj::EraseSceneObject("Map", pMap);
		//	GET_SINGLE(CSceneManager)->Change();
	}
	if (KEYUP("NextImage"))
	{
		MapUITex++;
		if (MapUITex == 4)MapUITex = 0;
		switch (MapUITex)
		{
		case 0:
			m_pMapUI->SetTexture("MapTypeMove", TEXT("OptionNone.bmp"));
			break;
		case 1:
			m_pMapUI->SetTexture("MapTypeNoMove", TEXT("NoMove.bmp"));
			break;
		case 2:
			m_pMapUI->SetTexture("MapTypeNoMove2", TEXT("NoMove2.bmp"));
			break;
		case 3:
			m_pMapUI->SetTexture("MapTypeUnEven", TEXT("UnEvenUp.bmp"));
			break;
		}
		
	}
	if (KEYPUSH("LButton"))
	{
		m_pMap->SetTile(MAP_TYPE(MapUITex), m_pMouse->GetPos());
	}
	
	if (m_pMouse->GetRButton() == true)
	{

	}
	if (KEYPUSH("Save"))
	{
		OPENFILENAME OFN;

		ShowCursor(TRUE);

		TCHAR strFileName[MAX_PATH] = {};
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = WINDOWHANDLE;
		OFN.lpstrFilter = TEXT("All File(*.*)\0*.*\0Stage File\0*.stg\0");
		OFN.lpstrFile = strFileName;
		OFN.nMaxFile = MAX_PATH;
		OFN.lpstrDefExt = TEXT("txt");
		const TCHAR* pDir = GET_SINGLE(CPathManager)->FindPath(ROOT_PATH);
		OFN.lpstrInitialDir = pDir;
		if (GetSaveFileName(&OFN) != 0) {
			//wsprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
			//MessageBox(nullptr, strFileName, TEXT("파일 열기 성공"), MB_OK);
			char	strFileName2[MAX_PATH] = {};

#ifdef _UNICODE
	WideCharToMultiByte(CP_ACP, 0, strFileName, -1, strFileName2, lstrlen(strFileName), 0, 0);
#endif // _UNICODE

	m_pMap->SaveFromFullPath(strFileName2);
		}

		ShowCursor(FALSE);
	}

	if (KEYPUSH("Load"))
	{
		OPENFILENAME OFN;

		ShowCursor(TRUE);

		TCHAR strFileName[MAX_PATH] = {};
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = WINDOWHANDLE;
		OFN.lpstrFilter = TEXT("All File(*.*)\0*.*\0Stage File\0*.stg\0");
		OFN.lpstrFile = strFileName;
		OFN.nMaxFile = MAX_PATH;
		OFN.lpstrDefExt = TEXT("stg");
		const TCHAR* pDir = GET_SINGLE(CPathManager)->FindPath(ROOT_PATH);
		OFN.lpstrInitialDir = pDir;
		if (GetOpenFileName(&OFN) != 0) {
			//wsprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
			char	strFileName2[MAX_PATH] = {};

#ifdef _UNICODE
			WideCharToMultiByte(CP_ACP, 0, strFileName, -1, strFileName2, lstrlen(strFileName), 0, 0);
#endif // _UNICODE

			CLayer* pLayer = m_pScene->FindLayer("BackGround");

		//	m_pMap->SetActive(false);

		//	SAFE_RELEASE(m_pStage);
			
			pLayer->EraseObject(m_pMap);
			m_pMap->CObj::EraseSceneObject(m_pScene);
			if (m_pMap)
				SAFE_RELEASE(m_pMap);
			m_pMap = CObj::CreateObject<CMap>("Map", pLayer);

			SAFE_RELEASE(pLayer);

			m_pMap->LoadFromFullPath(strFileName2);
		}

		ShowCursor(FALSE);
	}
	return 0;
}

int CMakeScene::Update(float fTime)
{

	return 0;
}

int CMakeScene::LateUpdate(float fTime)
{
	return 0;
}

void CMakeScene::Collision(float fTime)
{
}

void CMakeScene::Render(HDC hDC, float fTime)
{
	
}
