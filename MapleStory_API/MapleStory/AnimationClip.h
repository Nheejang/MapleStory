#pragma once

#include"Game.h"

class CAnimationClip
{
private:
	friend class CAnimation;

private:
	CAnimationClip();
	CAnimationClip(const CAnimationClip& clip);

public:
	~CAnimationClip();

private:
	string m_strName;
	ANIMATION_CLIP_TYPE m_eType;
	ANIMATION_OPTION m_eOption;
	class CTexture* m_pTexture;
	_SIZE m_tSize;
	int m_iFrameX;
	int m_iFrameY;
	int m_iFrameCountX;
	int m_iFrameCountY;
	int m_iFrameMaxX;
	int m_iFrameMaxY;
	int m_iStartX;
	int m_iStartY;
	int m_iFrameCount;
	float m_fAnimationTime;
	float m_fCompleteTime;
	bool m_bColorKey;
	DWORD m_dwColorKey;

public:
	CAnimationClip* Clone()const;
	bool Load(const char* pFullPath);
};