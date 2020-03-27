#pragma once

#include "Ref.h"
#include "Scene.h"
#include "Layer.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Math.h"
#include "Camera.h"
#include "PathManager.h"

class CObj :
	public CRef
{
private:
	static unordered_map<string, class CObj*>	m_mapPrototype;
	static unordered_multimap<string, class CObj*>	m_mapSceneObj;
	static list<CObj*>		m_FindList;

private:
	static CObj* FindPrototype(const string& strKey);

public:
	static CObj* CreateCloneObject(const string& strTag,
		class CLayer* pLayer = nullptr);
	static void ErasePrototype(class CScene* pScene);
	static void EraseSceneObject(class CScene* pScene);
	static void EraseSceneObject(const string& strKey, CObj* pObj);
	static void EraseFindList();
	static CObj* FindObject(const string& strKey);
	static const list<CObj*>* FindObjects(const string& strKey);

protected:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj() = 0;

protected:
	class CScene* m_pScene;
	class CLayer* m_pLayer;

public:
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetLayer(class CLayer* pLayer)
	{
		m_pLayer = pLayer;
	}

public:
	class CScene* GetScene()	const;
	class CLayer* GetLayer()	const;

protected:
	OBJECT_TYPE	m_eType;
	POSITION	m_tPos;
	_SIZE		m_tSize;
	POSITION	m_tPivot;
	POSITION	m_tOffset;
	float		m_fAngle;
	class CTexture* m_pTexture;
	float	m_fMoveSpeed;
	float	m_fRotSpeed;
	DWORD	m_dwColorKey;
	bool	m_bColorKey;

	list<class CCollider*> m_ColliderList;

	bool	m_bGravity;
	float	m_fForce;
	float	m_fForceOrigin;
	float	m_fGravityTime;
	bool	m_bCameraEnable;
	POSITION	m_tMove;

	
	class CAnimation* m_pAnimation;

public:
	bool GetCameraEnable()	const
	{
		return m_bCameraEnable;
	}

	OBJECT_TYPE GetObjType()	const
	{
		return m_eType;
	}

	const list<class CCollider*>* GetColliderList()const
	{
		return &m_ColliderList;
	}
	class CCollider* GetCollider(const string& strTag);

public:
	void SetCameraEnable(bool bEnable)
	{
		m_bCameraEnable = bEnable;
	}

	void ClearGravityTime()
	{
		m_fGravityTime = 0.f;
	}

	void SetForce(float fForce)
	{
		m_fForceOrigin = fForce;
		m_fForce = fForce;
	}

	void SetGravity(bool bGravity)
	{
		m_bGravity = bGravity;
	}

	void SetColorKey(char r, char g, char b)
	{
		m_dwColorKey = RGB(r, g, b);
		m_bColorKey = true;
	}

	void SetColorKey(DWORD dwColorKey)
	{
		m_dwColorKey = dwColorKey;
		m_bColorKey = true;
	}

	void DisableColorKey()
	{
		m_bColorKey = false;
	}

	void SetRotationSpeed(float fSpeed)
	{
		m_fRotSpeed = fSpeed;
	}

	void SetMoveSpeed(float fSpeed)
	{
		m_fMoveSpeed = fSpeed;
	}

	virtual void SetPos(float x, float y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

	virtual void SetPos(const POSITION& tPos)
	{
		m_tPos = tPos;
	}

	virtual void SetPos(const POINT& tPos)
	{
		m_tPos = tPos;
	}

	void SetSize(float x, float y)
	{
		m_tSize.x = x;
		m_tSize.y = y;
	}

	void SetSize(const _SIZE& tSize)
	{
		m_tSize = tSize;
	}

	void SetPivot(float x, float y)
	{
		m_tPivot.x = x;
		m_tPivot.y = y;
	}

	void SetPivot(const POSITION& tPivot)
	{
		m_tPivot = tPivot;
	}

	void SetAngle(float fAngle)
	{
		m_fAngle = fAngle;
	}

public:
	float GetForce()	const
	{
		return m_fForce;
	}

	float GetForceOrigin()	const
	{
		return m_fForceOrigin;
	}

	bool GetGravity()	const
	{
		return m_bGravity;
	}

	DWORD GetColorKey()	const
	{
		return m_dwColorKey;
	}

	float GetRotationSpeed()	const
	{
		return m_fRotSpeed;
	}

	float GetAngle()	const
	{
		return m_fAngle;
	}

	POSITION GetPos()	const
	{
		return m_tPos;
	}

	POSITION GetPivot()	const
	{
		return m_tPivot;
	}

	_SIZE GetSize()	const
	{
		return m_tSize;
	}

public:
	bool SetTexture(const string& strKey, const TCHAR* pFileName,
		const string& strPathKey = TEXTURE_PATH);
	bool SetTexture(const string& strKey);
	bool SetTexture(class CTexture* pTexture);

	bool AddAnimationClip(const string& strName, ANIMATION_CLIP_TYPE eType,
		ANIMATION_OPTION eOption, float fFrameWidth, float fFrameHeight,
		int iFrameCountX, int iFrameCountY, int iFrameMaxX, int iFrameMaxY,
		int iStartX, int iStartY, float fCompleteTime,
		const string& strTexKey, const TCHAR* pFileName,
		bool bColorKey = true, DWORD dwColorKey = RGB(255, 0, 255),
		const string& strPathKey = TEXTURE_PATH);
	bool LoadAnimation(const char* pFileName, const string& strPathKey = DATA_PATH);

public:
	void Move(float x, float y);
	void Move(float x, float y, float fTime);
	void Move(const POSITION& tDir);
	void Move(const POSITION& tDir, float fTime);
	void MoveByAngle(float fTime);
	void Rotation(float fTime);

public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CObj* Clone() = 0;
	void SaveFromFullPath(const char* pFileName);
	void SaveFile(const char* pFileName, const string& strPathKey = DATA_PATH);
	virtual void Save(FILE* pFile);
	void LoadFromFullPath(const char* pFileName);
	void LoadFile(const char* pFileName, const string& strPathKey = DATA_PATH);
	virtual void Load(FILE* pFile);


public:
	template <typename T>
	static T* CreatePrototype(const string& strTag,
		class CScene* pScene)
	{
		T* pPrototype = (T*)FindPrototype(strTag);

		if (pPrototype)
			return nullptr;

		pPrototype = new T;

		pPrototype->SetScene(pScene);
		pPrototype->SetTag(strTag);

		if (!pPrototype->Init())
		{
			SAFE_RELEASE(pPrototype);
			return nullptr;
		}

		pPrototype->AddRef();
		m_mapPrototype.insert(make_pair(strTag, pPrototype));

		return pPrototype;
	}

	template <typename T>
	static T* CreateObject(const string& strTag,
		class CLayer* pLayer = nullptr)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (pLayer)
			pLayer->AddObject(pObj);

		if (!pObj->Init())
		{
			if (pLayer)
				pLayer->EraseObject(pObj);
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		pObj->AddRef();
		m_mapSceneObj.insert(make_pair(strTag, pObj));

		return pObj;
	}

	
};

