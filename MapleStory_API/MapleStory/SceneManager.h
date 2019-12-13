#pragma once

#include "Game.h"

class CSceneManager
{
private:
	class CScene* m_pScene;
	class CScene* m_pNextScene;

public:
	bool Init();
	int Input(float fTime);
	int Update(float fTime);
	int LateUpdate(float fTime);
	void Render(HDC hDC, float fTime);

private:
	int ChangeScene();

public:
	class CScene* CreateScene(const string& strTag);
	//template <typename T>
	//void CreateNextScene(const string& strTag)
	//{
	//	SAFE_RELEASE(m_pNextScene);
	//	m_pNextScene = CreateScene(strTag);

	//	T* pSceneCom = m_pNextScene->CreateSceneComponent<T>("strTag");

	//	SAFE_RELEASE(pSceneCom);
	//}

	DECLARE_SINGLE(CSceneManager)
};

