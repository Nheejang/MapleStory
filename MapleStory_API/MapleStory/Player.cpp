#include"Player.h"
#include"Input.h"
#include"Math.h"
#include"Camera.h"


CPlayer::CPlayer()
{
	SetTag("Player");
	m_eType = OT_PLAYER;
}

CPlayer::CPlayer(const CPlayer& player)
	:CCharacter(player)
{

}
CPlayer::~CPlayer()
{

}

bool CPlayer::Init()
{
	SetMoveSpeed(300.f);
	SetTexture("Teemo", TEXT("Teemo.bmp"));

	SetPos(200.f, 200.f);
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	//SetGravity(true);
	return true;
}


int CPlayer::Input(float fTime)
{
	if (KEYPUSH("MoveLeft"))
	{
		//Rotation(fTime);
		Move(-m_fMoveSpeed, 0.f, fTime);
	}

	if (KEYPUSH("MoveRight"))
	{
		//Rotation(-fTime);
		Move(m_fMoveSpeed, 0.f, fTime);
	}

	if (KEYPUSH("MoveUp"))
	{
		Move(0.f, -m_fMoveSpeed, fTime);
		//MoveByAngle(fTime);
	}

	if (KEYPUSH("MoveDown"))
	{
		Move(0.f, m_fMoveSpeed, fTime);
		//MoveByAngle(-fTime);
	}

	if (KEYPRESS("Jump"))
	{
		SetForce(300.f);
	}

	return 0;
}


int CPlayer::Update(float fTime)
{
	CCharacter::Update(fTime);

	// 이전에 위치해 있던 곳과 현재 위치를 비교하여준다.
	// 이전 위치를 구해준다.
	POSITION	tPrevPos = m_tPos - m_tMove;


	return 0;
}

int CPlayer::LateUpdate(float fTime)
{
	CCharacter::LateUpdate(fTime);

	return 0;
}

void CPlayer::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CPlayer::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);

	POSITION	tCameraPos = GET_SINGLE(CCamera)->GetPos();

	POSITION	tCenter = m_tPos - tCameraPos;


	// 방향을 표시할 선을 그려준다.
	MoveToEx(hDC, tCenter.x, tCenter.y, nullptr);

	POSITION	tLineEnd;
	tLineEnd.x = tCenter.x + cosf(CMath::DegreeToRadian(m_fAngle)) * 80.f;
	tLineEnd.y = tCenter.y + sinf(CMath::DegreeToRadian(m_fAngle)) * 80.f;

	LineTo(hDC, tLineEnd.x, tLineEnd.y);

	//POSITION	tLT = m_tPos - m_tSize * m_tPivot;
	//Rectangle(hDC, tLT.x, tLT.y, tLT.x + m_tSize.x, tLT.y + m_tSize.y);
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}
