#pragma once

#include"Game.h"

class CAnimation
{
private:
	friend class CObj;

private:
	CAnimation();
	CAnimation(const CAnimation& anim);
	~CAnimation();

private:
	class CObj* m_pObj;
	unordered_map<string, class CAnimationClip*> m_mapClip;
	string m_strCurClip;
	string m_strDefaultClip;
	class CAnimationClip* m_pCurClip;
	class CAnimationClip* m_pDefaultClip;

public:
	int GetFrameX() const;
	int GetFrameY() const;
	_SIZE GetFrameSize() const;
	void SetObj(class CObj* pObj)
	{
		m_pObj = pObj;
	}

public:
	bool CreateAnimationClip(const string& strName, ANIMATION_CLIP_TYPE eType,
		ANIMATION_OPTION eOption, float fFrameWidth, float fFrameHeight,
		int iFrameountX, int iFrameCountY, int iFrameMaxX, int iFrameMaxY,
		int iStartX, int iStartY, float fCompleteTime,
		const string& strTexKey, const TCHAR* pFileName,
		bool bColorKey = true, DWORD dwColorKey = RGB(255, 0, 255),
		const string& strPathKey = TEXTURE_PATH);
	bool LoadAnimation(const char* pFIleName, const string& strPathKey = DATA_PATH);
	void SetDefaultClip(const string& strName);
	void SetCurrentClip(const string& strName);
	void ChangeClip(const string& strName);

private:
	class CAnimationClip* FindClip(const string& strName);

public:
	bool Init();
	void Update(float fTime);
	CAnimation* Clone()const;
};
