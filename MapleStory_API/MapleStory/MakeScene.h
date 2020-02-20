#pragma once
#include "SceneComponent.h"
class CMakeScene :
	public CSceneComponent
{
	friend class CScene;

private:
	CMakeScene();
	~CMakeScene();
	class CMouse* m_pMouse;
	class CMap* m_pMap;
	class CUIButton* m_pMapUI;
public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);

public:


	//Make_Scene MAPUITexture
	int MapUITex = {};
};

