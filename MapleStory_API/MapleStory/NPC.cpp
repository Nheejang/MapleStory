#include"NPC.h"

CNPC::CNPC()
{
}

CNPC::CNPC(const CNPC* npc)
{
}

CNPC::~CNPC()
{
}

bool CNPC::Init()
{
	return true;
}

int CNPC::Input(float fTime)
{
	CObj::Input(fTime);
	return 0;
}

int CNPC::Update(float fTime)
{
	CObj::Update(fTime);
	return 0;
}

int CNPC::LateUpdate(float fTime)
{
	CObj::LateUpdate(fTime);
	return 0;
}

void CNPC::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CNPC::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

CNPC* CNPC::Clone()
{
	return nullptr;
}
