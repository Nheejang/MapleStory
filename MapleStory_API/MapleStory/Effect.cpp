#include"Effect.h"

CEffect::CEffect() :
	m_fActiveTime(0.f)
{
	m_eType = OT_EFFECT;
}
CEffect::CEffect(const CEffect& effect):
	CObj(effect)
{
}

CEffect::~CEffect()
{
}

bool CEffect::Init()
{
	return true;
}

int CEffect::Input(float fTime)
{
	CObj::Input(fTime);

	return 0;
}

int CEffect::Update(float fTime)
{
	CObj::Update(fTime);
	
	return 0;
}
int CEffect::LateUpdate(float fTime)
{
	CObj::LateUpdate(fTime);

	return 0;
}

void CEffect::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CEffect::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

CEffect* CEffect::Clone()
{
	return new CEffect(*this);
}