#include"Monster.h"
#include"Math.h"
#include"Character.h"
CMonster::CMonster() :
	m_pTarget(nullptr)
{
	m_eType = OT_MONSTER;
}

CMonster::CMonster(const CMonster& monster) :
	CCharacter(monster)
{
}

CMonster::~CMonster()
{
	SAFE_RELEASE(m_pTarget);
}

bool CMonster::Init()
{
	SetMoveSpeed(200.f);
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Mon", TEXT("Monster_Sword2_Left.bmp"));

	return true;
}

int CMonster::Input(float fTime)
{
	CCharacter::Input(fTime);
	
	return 0;
}

int CMonster::Update(float fTime)
{
	CCharacter::Update(fTime);
	
	if (m_pTarget)
	{
		POSITION tTargetPos = m_pTarget->GetPos();


		float	fDist = CMath::GetDistance(tTargetPos, m_tPos);

		m_fAngle = CMath::GetDegree(m_tPos, m_pTarget->GetPos());
		MoveByAngle(fTime);
		
	}
	else
	{
		Move(1, 0, fTime);
	}
	return 0;
}

int CMonster::LateUpdate(float fTime)
{
	CCharacter::LateUpdate(fTime);

	return 0;
}

void CMonster::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CMonster::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

CMonster* CMonster::Clone()
{
	return nullptr;
}