#include "SceneManager.h"
#include "Scene.h"
#include"testScene.h"
#include"MakeScene.h"
DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager() :
	m_pScene(nullptr),
	m_pNextScene(nullptr)
{
}


CSceneManager::~CSceneManager()
{
	SAFE_RELEASE(m_pNextScene);
	SAFE_RELEASE(m_pScene);
}

bool CSceneManager::Init()
{
	m_pScene = CreateScene("MakeScene");

	CMakeScene* pSceneCom = m_pScene->CreateSceneComponent<CMakeScene>("MakeScene");

	SAFE_RELEASE(pSceneCom);
	return true;
}

int CSceneManager::Input(float fTime)
{
	m_pScene->Input(fTime);

	return ChangeScene();
}

int CSceneManager::Update(float fTime)
{
	m_pScene->Update(fTime);

	return ChangeScene();
}

int CSceneManager::LateUpdate(float fTime)
{
	m_pScene->LateUpdate(fTime);

	return ChangeScene();
}



void CSceneManager::Render(HDC hDC, float fTime)
{
	m_pScene->Render(hDC, fTime);
}

int CSceneManager::ChangeScene()
{
	if (m_pNextScene)
	{
		SAFE_RELEASE(m_pScene);

		m_pScene = m_pNextScene;
		m_pNextScene = nullptr;
		return 1;
	}

	return 0;
}

CScene* CSceneManager::CreateScene(const string& strTag)
{
	CScene* pScene = new CScene;

	pScene->SetTag(strTag);

	if (!pScene->Init())
	{
		SAFE_RELEASE(pScene);
		return nullptr;
	}

	return pScene;
}

void CSceneManager::Change()
{
	
	m_pNextScene = CreateScene("testScene2");
	CtestScene* pSceneCom2 = m_pNextScene->CreateSceneComponent<CtestScene>("testScene2");
	SAFE_RELEASE(pSceneCom2);
}
CScene* CSceneManager::GetCurrentScene()
{
	return m_pScene;
}