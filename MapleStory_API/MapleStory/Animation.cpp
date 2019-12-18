#include"Animation.h"
#include"AnimationClip.h"
#include"ResourceManager.h"
#include"Texture.h"
#include"Obj.h"
#include"PathManager.h"

CAnimation::CAnimation()
{
	m_pCurClip = nullptr;
	m_pDefaultClip = nullptr;
}

CAnimation::CAnimation(const CAnimation& anim)
{
	*this = anim;

	m_mapClip.clear();
	m_pCurClip = nullptr;
	m_pDefaultClip = nullptr;

	unordered_map<string, CAnimationClip*>::const_iterator iter;
	unordered_map<string, CAnimationClip*>::const_iterator iterEnd = anim.m_mapClip.end();

	for (iter = anim.m_mapClip.begin(); iter != iterEnd;++iter)
	{
		CAnimationClip* pClip = iter->second->Clone();

		m_mapClip.insert(make_pair(iter->first, pClip));
	}

	SetDefaultClip(m_strDefaultClip);
	SetCurrentClip(m_strCurClip);
}

CAnimation::~CAnimation()
{
	Safe_Delete_Map(m_mapClip);
}

int CAnimation::GetFrameX() const
{
	return m_pCurClip->m_iFrameX;
}
int CAnimation::GetFrameY() const
{
	return m_pCurClip->m_iFrameY;
}

_SIZE CAnimation::GetFrameSize() const
{
	return m_pCurClip->m_tSize;
}
bool CAnimation::CreateAnimationClip(const string& strName, ANIMATION_CLIP_TYPE eType,
	ANIMATION_OPTION eOption, float fFrameWidth, float fFrameHeight, int iFrameCountX,
	int iFrameCountY, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
	float fCompleteTime,
	const string& strTexKey, const TCHAR* pFileName,
	bool bColorKey, DWORD dwColorKey, const string& strPathKey)
{
	CAnimationClip* pClip = FindClip(strName);

	if (pClip)
		return false;
	pClip = new CAnimationClip;
	pClip->m_strName = strName;
	pClip->m_eType = eType;
	pClip->m_eOption = eOption;
	pClip->m_tSize.x = fFrameWidth;
	pClip->m_tSize.y = fFrameHeight;
	pClip->m_iFrameCountX = iFrameCountX;
	pClip->m_iFrameCount = iFrameCountY;
	pClip->m_iFrameMaxX = iFrameMaxX;
	pClip->m_iFrameMaxY = iFrameMaxY;
	pClip->m_iStartX = iStartX;
	pClip->m_iStartY = iStartY;
	pClip->m_iFrameX = iStartX;
	pClip->m_iFrameY = iStartY;
	pClip->m_fCompleteTime = fCompleteTime;
	pClip->m_fAnimationTime = 0.f;
	pClip->m_iFrameCount = iFrameCountX * iFrameCountY;
	pClip->m_bColorKey = bColorKey;
	pClip->m_dwColorKey = dwColorKey;

	pClip->m_pTexture = GET_SINGLE(CResourceManager)->LoadTexture(strTexKey,
		pFileName, strPathKey);

	m_mapClip.insert(make_pair(strName, pClip));

	if (m_mapClip.size() == 1)
	{
		SetDefaultClip(strName);
		SetCurrentClip(strName);
	}

	return true;
}

bool CAnimation::LoadAnimation(const char* pFileName,
	const string& strPathKey)
{
	CAnimationClip* pClip = new CAnimationClip;

	const char* pPath = GET_SINGLE(CPathManager)->FindPathFromMultibyte(strPathKey);

	string strFullPath;

	if (pPath)
		strFullPath += pPath;

	strFullPath += pFileName;

	if (!pClip->Load(strFullPath.c_str()))
	{
		SAFE_DELETE(pClip);
		return false;
	}

	if (FindClip(pClip->m_strName))
	{
		SAFE_DELETE(pClip)
			return false;
	}

	m_mapClip.insert(make_pair(pClip->m_strName, pClip));

	if (m_mapClip.size() == 1)
	{
		SetDefaultClip(pClip->m_strName);
		SetCurrentClip(pClip->m_strName);
	}

	return true;
}

void CAnimation::SetDefaultClip(const string& strName)
{
	m_strDefaultClip = strName;
	m_pDefaultClip = FindClip(strName);
}

void CAnimation::SetCurrentClip(const string& strName)
{
	m_strCurClip = strName;
	m_pCurClip = FindClip(strName);

	m_pCurClip->m_iFrameX = m_pCurClip->m_iStartX;
	m_pCurClip->m_iFrameY = m_pCurClip->m_iStartY;
	m_pCurClip->m_fAnimationTime = 0.f;

	m_pObj->SetTexture(m_pCurClip->m_pTexture);

	if (m_pCurClip->m_bColorKey)
		m_pObj->SetColorKey(m_pCurClip->m_dwColorKey);
	else
		m_pObj->DisableColorKey();
}

void CAnimation::ChangeClip(const string& strName)
{
	if (m_strCurClip == strName)
		return;

	SetCurrentClip(strName);
}

CAnimationClip* CAnimation::FindClip(const string& strName)
{
	unordered_map<string, CAnimationClip*>::iterator iter = m_mapClip.find(strName);

	if (iter == m_mapClip.end())
		return nullptr;

	return iter->second;
}

bool CAnimation::Init()
{
	return true;
}

void CAnimation::Update(float fTime)
{
	m_pCurClip->m_fAnimationTime += fTime;
	float fCompleteTime = m_pCurClip->m_fCompleteTime / m_pCurClip->m_iFrameCount;

	while (m_pCurClip->m_fAnimationTime >= fCompleteTime)
	{
		m_pCurClip->m_fAnimationTime -= fCompleteTime;

		++m_pCurClip->m_iFrameX;

		if (m_pCurClip->m_iFrameX >= m_pCurClip->m_iStartX + m_pCurClip->m_iFrameCountX)
		{
			m_pCurClip->m_iFrameX = m_pCurClip->m_iStartX;

			++m_pCurClip->m_iFrameY;

			if (m_pCurClip->m_iFrameY >= m_pCurClip->m_iStartY + m_pCurClip->m_iFrameCountY)
			{
				m_pCurClip->m_iFrameY = m_pCurClip->m_iStartY;

				switch (m_pCurClip->m_eOption)
				{
				case AO_ONCE_RETURN:
					ChangeClip(m_strDefaultClip);
					break;
				case AO_ONCE_DESTROY:
					m_pObj->SetActive(false);
					break;
				}
			}
		}
	}
}

CAnimation* CAnimation::Clone() const
{
	return new CAnimation(*this);
}