#include "SceneComponent.h"

CSceneComponent::CSceneComponent() :
	m_pScene(nullptr)
{
}

CSceneComponent::~CSceneComponent()
{
}

int CSceneComponent::Input(float fTime)
{
	return 0;
}

int CSceneComponent::Update(float fTime)
{
	return 0;
}

int CSceneComponent::LateUpdate(float fTime)
{
	return 0;
}

void CSceneComponent::Collision(float fTime)
{
}

void CSceneComponent::Render(HDC hDC, float fTime)
{
}

